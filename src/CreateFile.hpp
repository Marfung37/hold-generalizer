#ifndef CREATE_FILE
#define CREATE_FILE

#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "SfinderFile.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>

#define SUFFIX_MAP std::unordered_map<std::string, std::vector<std::string>>
namespace fs = std::filesystem;

class CreateFile{
    public:
        CreateFile(CLIParser::values args);
    
        void runSfinderCommand();
    private:
        void applyHoldPermutationOnPatternsFile();
        void readdPieceSuffixes();
        SUFFIX_MAP getQueueSuffixes(unsigned int neededPieces);

        CLIParser::values args;
        SfinderFile sfinderFile;
        const fs::path logPath = fs::path("output") / "last_output.txt";

};

#endif