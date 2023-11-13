#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <filesystem> 
#include <iostream>
#include <iomanip>

#include "CreateFile.hpp"
#include "SfinderFile.hpp"
#include "HoldGenerator.hpp"

namespace fs = std::filesystem;

CreateFile::CreateFile(CLIParser::values args) : args(args), sfinderFile(args.filepath.string(), args.command), workedCount(0), totalCount(0), tetrisSortOrder() {}

void CreateFile::createFile(){
    std::string commandStr = generateCommand();

    if(!args.manualPermutate){
        applyHoldPermutationOnPatternsFile();
    }

    std::system(commandStr.c_str());

    sfinderFile.parseFile();

    if(args.command == "path"){
        readdPieceSuffixes();
        sfinderFile.createMap();
    }

    applyHoldOnSfinderFile();
    sfinderFile.writeFile();
}

void CreateFile::printData(){
    double percentage = static_cast<double>(workedCount) / totalCount * 100;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Percent: " << percentage << "% (" << workedCount << "/" << totalCount << ")" << std::endl;
}

std::string CreateFile::generateCommand(){
    std::string commandStr = "java -jar " + args.sfinderFile.string() + " " + args.command + " -H avoid";

    if(args.command == "path"){
        commandStr += " -k pattern -f csv";
    }

    if(!args.tetfu.empty()){
        commandStr += " -t ";
        #ifdef _WIN32
        commandStr += "\"" + args.tetfu + "\"";
        #else
        commandStr += args.tetfu;
        #endif
    } else {
        commandStr += " -fp " + args.fieldFile.string();
    }
    if(!args.patterns.empty()){        
        // create the directories to that file
        fs::path parentPatterns = args.patternsFile.parent_path();
        if(!fs::is_directory(parentPatterns) || !fs::exists(parentPatterns)){
            fs::create_directories(parentPatterns);
        }

        std::string osPatterns = args.patterns;
        #ifdef _WIN32
        osPatterns = "\"" + osPatterns + "\"";
        #endif

        std::system(("java -jar " + args.sfinderFile.string() + " util seq -p " + osPatterns + " > " + args.patternsFile.string()).c_str());
    }
    if(!args.additionalSfinderOptions.empty()){
        commandStr += " " + args.additionalSfinderOptions;
    }
    
    commandStr += " -pp " + args.patternsPermutateFile.string();
    commandStr += " -o " + args.filepath.string();

    // suppress output
    #ifdef _WIN32
    commandStr += " > NUL";
    #else
    commandStr += " > /dev/null";
    #endif

    return commandStr;
}

void CreateFile::applyHoldPermutationOnPatternsFile(){
    HoldGenerator queuesGen("", args.hold, args.cyclePermutate);
    std::ifstream inPatternsStream(args.patternsFile.string());
    std::unordered_set<std::string> holdPermutationQueues{};
    std::string queue;

    if(!inPatternsStream.is_open()){
        throw new std::runtime_error(args.patternsFile.string() + " does not exist!");
        return;
    }

    while(inPatternsStream >> queue){
        queuesGen.setQueue(queue);
        queuesGen.generatePermutations();
        holdPermutationQueues.merge(queuesGen.getPermutations());
    }

    inPatternsStream.close();
    std::ofstream outPatternsPermutateStream(args.patternsPermutateFile.string());

    for(std::string queue: holdPermutationQueues){
        outPatternsPermutateStream << queue << std::endl;
    }

    outPatternsPermutateStream.close();
}

void CreateFile::readdPieceSuffixes(){
    SUFFIX_MAP suffixesMap;
    unsigned int neededPieces = 0;

    // determine neededPieces
    neededPieces = sfinderFile.fileData.at(0).queue.size();

    suffixesMap = getQueueSuffixes(neededPieces);

    // if there's no suffixes just return
    if(suffixesMap.empty()){
        return;
    }
    
    for(SfinderFile::columns& line: sfinderFile.fileData) {
        std::vector<std::string>& suffixes = suffixesMap.at(line.queue);
        std::string thisSuffix = suffixes.back();
        line.queue += thisSuffix;

        if(args.command == "path"){
            // add to saves if there is a solve
            if(line.worked){
                std::sort(thisSuffix.begin(), thisSuffix.end(), tetrisSortOrder);
                line.piecesSaved = thisSuffix;
            }
        }

        suffixes.pop_back();
    }
}

SUFFIX_MAP CreateFile::getQueueSuffixes(unsigned int neededPieces){
    SUFFIX_MAP suffixesMap;
    std::ifstream inPatternsPermutateStream(args.patternsPermutateFile.string());
    std::string queue;

    if(!inPatternsPermutateStream.is_open()){
        throw new std::runtime_error("Unable to open necessary files for readdPieceSuffixes");
    }

    inPatternsPermutateStream >> queue;
    // check if there's going to be any suffixes
    if(queue.size() == neededPieces){
        return suffixesMap;
    }

    do{
        // if the prefix already within the map
        std::string prefix = queue.substr(0, neededPieces);
        std::string suffix = queue.substr(neededPieces);
        
        if(suffixesMap.find(prefix) != suffixesMap.end()){
            suffixesMap.at(prefix).push_back(suffix);
        } else {
            std::vector<std::string> suffixesVector = {suffix};
            suffixesMap.insert({prefix, suffixesVector});
        }
    } while(inPatternsPermutateStream >> queue);

    inPatternsPermutateStream.close();

    return suffixesMap;
}

void CreateFile::applyHoldOnSfinderFile(){
    std::ifstream inPatternsStream(args.patternsFile.string());
    std::vector<SfinderFile::columns> filteredFileData;
    HoldGenerator holdGen("", args.hold, args.cyclePermutate);
    SfinderFile::columns columnData;
    std::string queue;
    
    if(!inPatternsStream.is_open()){
        throw new std::runtime_error(args.patternsFile.string() + " does not exist!");
        return;
    }

    while(inPatternsStream >> queue){
        holdGen.setQueue(queue);
        holdGen.generatePermutations();
        columnData = sfinderFile.fileMap.at(queue);
        
        for(std::string permutation: holdGen.getPermutations()){
            SfinderFile::columns permCols = sfinderFile.fileMap.at(permutation);

            if(addDataFromPermCols(columnData, permCols)){
                break;
            }
        }
        if(columnData.worked){
            workedCount++;
        }
        totalCount++;

        filteredFileData.push_back(columnData);
    }

    sfinderFile.fileData = filteredFileData;
}

bool CreateFile::addDataFromPermCols(SfinderFile::columns& columnData, SfinderFile::columns permCols){
    if(permCols.worked){
        if(args.command == "path"){
            // determine if any new unique solutions
            unsigned int uniqueSolCount = 0;
            char delimiter = ';';

            std::istringstream inSS;
            
            inSS.clear();
            inSS.str(permCols.piecesUsed);

            std::string used;
            while(getline(inSS, used, delimiter)){
                bool unique = columnData.piecesUsed.find(used) == std::string::npos;
                if(unique){
                    if(!columnData.piecesUsed.empty())
                        columnData.piecesUsed += delimiter;
                    columnData.piecesUsed += used;
                }
            }
            
            inSS.clear();
            inSS.str(permCols.piecesSaved);

            std::string save;
            while(getline(inSS, save, delimiter)){
                bool unique = columnData.piecesSaved.find(save) == std::string::npos;
                if(unique){
                    if(!columnData.piecesSaved.empty())
                        columnData.piecesSaved += delimiter;
                    columnData.piecesSaved += save;
                }
            }
            
            inSS.clear();
            inSS.str(permCols.solveFumens);

            std::string fumen;
            while(getline(inSS, fumen, delimiter)){
                bool unique = columnData.solveFumens.find(fumen) == std::string::npos;
                if(unique){
                    if(!columnData.solveFumens.empty())
                        columnData.solveFumens += delimiter;
                    columnData.solveFumens += fumen;
                    uniqueSolCount++;
                }
            }

            columnData.numSolves += uniqueSolCount;
            columnData.worked = true;

        } else if(args.command == "cover"){
            columnData.worked = true;
            return true;
        }
    }
    return false;

}