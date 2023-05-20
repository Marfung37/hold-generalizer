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
    
        void createFile();
        void printData();
    private:
        std::string generateCommand();
        void applyHoldPermutationOnPatternsFile();
        void readdPieceSuffixes();
        SUFFIX_MAP getQueueSuffixes(unsigned int neededPieces);
        void applyHoldOnSfinderFile();
        bool addDataFromPermCols(SfinderFile::columns& columnData, SfinderFile::columns permCol);

        CLIParser::values args;
        SfinderFile sfinderFile;
        const fs::path logPath = fs::path("output") / "last_output.txt";
        unsigned int workedCount;
        unsigned int totalCount;

        struct
        {
            bool operator()(char a, char b) const { 
                std::string BAG = "TILJSZO";
                for(char& piece: BAG){
                    if(a == piece){
                        return true;
                    } else if(b == piece){
                        return false;
                    }
                }
                // bad input
                return false;
            }
        } tetrisSortOrder;
};

#endif