#ifndef CLI_PARSER
#define CLI_PARSER

#include <string>
#include <filesystem>
#include "../lib/CLI11.hpp"

namespace fs = std::filesystem;

class CLIParser{
    public:
        CLIParser();
        int parse(int argc, char* argv[]);
        
        struct values{
            fs::path filepath; // the resulting filename after command
            fs::path sfinderFile;
            fs::path fieldFile;
            fs::path patternsFile;
            std::string command;
            unsigned int hold;
            std::string tetfu;
            std::string patterns;
            std::string additionalSfinderOptions;
        };

        CLI::App app;
        values args; // options
        
    private:
        void setupParser();
        
};

#endif