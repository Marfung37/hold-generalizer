#ifndef CREATE_FILE
#define CREATE_FILE

#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"

class CreateFile{
    public:
        CreateFile(CLIParser::values args) : args(args) {}
    
        void runSfinderCommand();
    private:
        void applyHoldPermutationOnPatternsFile();
        void readdPieceSuffixes();

        CLIParser::values args;
};

#endif