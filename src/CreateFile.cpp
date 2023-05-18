#include <string>
#include <fstream>
#include <unordered_set>
#include <filesystem>

#include "CreateFile.hpp"
#include "SfinderFile.hpp"
#include "HoldGenerator.hpp"

namespace fs = std::filesystem;

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
    commandStr += " > " + (fs::path("output") / "last_output.txt").string();

    applyHoldPermutationOnPatternsFile();

    std::system(commandStr.c_str());
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

}