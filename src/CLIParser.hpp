#pragma once

#include <string>
#include <filesystem>
#include "../lib/CLI11.hpp"

namespace fs = std::filesystem;

class CLIParser{
    public:
        CLIParser();
        void afterParse();
        
        struct values{
            fs::path filepath; // the resulting filename after command
            fs::path sfinderFile;
            fs::path fieldFile;
            fs::path patternsFile;
            fs::path patternsPermutateFile;
            std::string command;
            unsigned int hold;
            std::string tetfu;
            std::string patterns;
            bool manualPermutate;
            std::string additionalSfinderOptions;
        };

        CLI::App app;
        values args; // options
        
    private:
        void setupParser();
        
};
