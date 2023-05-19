#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>

#include "CreateFile.hpp"
#include "SfinderFile.hpp"
#include "HoldGenerator.hpp"

namespace fs = std::filesystem;

CreateFile::CreateFile(CLIParser::values args) : args(args), sfinderFile(args.filepath.string(), args.command){}

void CreateFile::runSfinderCommand(){
    std::string commandStr = "java -jar " + args.sfinderFile.string() + " " + args.command + " -H avoid";

    if(args.command == "path"){
        commandStr += " -k pattern -f csv";
    }

    if(!args.tetfu.empty()){
        commandStr += " -t " + args.tetfu;
    } else {
        commandStr += " -fp " + args.fieldFile.string();
    }
    if(!args.patterns.empty()){        
        // create the directories to that file
        fs::path parentPatterns = args.patternsFile.parent_path();
        if(!fs::is_directory(parentPatterns) || !fs::exists(parentPatterns)){
            fs::create_directories(parentPatterns);
        }

        std::system(("java -jar " + args.sfinderFile.string() + " util seq -p " + args.patterns + " > " + args.patternsFile.string()).c_str());
    }
    if(!args.additionalSfinderOptions.empty()){
        commandStr += " " + args.additionalSfinderOptions;
    }
    
    commandStr += " -pp " + args.patternsFile.string();
    commandStr += " -o " + args.filepath.string();

    // suppress output
    commandStr += " > " + logPath.string();

    applyHoldPermutationOnPatternsFile();

    std::system(commandStr.c_str());

    sfinderFile.parseFile();

    if(args.command == "path"){
        readdPieceSuffixes();
    }

    sfinderFile.writeFile(); // DEBUG
}

void CreateFile::applyHoldPermutationOnPatternsFile(){
    HoldGenerator queuesGen("", args.hold);
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
    std::ofstream outPatternsStream(args.patternsFile.string());

    for(auto it = holdPermutationQueues.begin(); it != holdPermutationQueues.end(); it++){
        outPatternsStream << *it << std::endl;
    }

    outPatternsStream.close();
}

void CreateFile::readdPieceSuffixes(){
    SUFFIX_MAP suffixesMap;
    std::vector<std::string> suffixes;
    unsigned int neededPieces = 0;

    // determine neededPieces
    neededPieces = sfinderFile.fileData.at(0).queue.size();

    suffixesMap = getQueueSuffixes(neededPieces);

    // if there's no suffixes just return
    if(suffixesMap.empty()){
        return;
    }
    
    for(SfinderFile::columns& line: sfinderFile.fileData) {
        suffixes = suffixesMap.at(line.queue);
        line.queue += suffixes.back();

        if(args.command == "path"){
            // add to saves if there is a solve
            if(line.worked){
                line.piecesSaved += suffixes.back();
            }
        }

        suffixes.pop_back();
    }
}

SUFFIX_MAP CreateFile::getQueueSuffixes(unsigned int neededPieces){
    SUFFIX_MAP suffixesMap;
    std::ifstream inPatternsStream(args.patternsFile.string());
    std::string queue;

    if(!inPatternsStream.is_open()){
        throw new std::runtime_error("Unable to open necessary files for readdPieceSuffixes");
    }

    inPatternsStream >> queue;
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
    } while(inPatternsStream >> queue);

    inPatternsStream.close();

    return suffixesMap;
}

