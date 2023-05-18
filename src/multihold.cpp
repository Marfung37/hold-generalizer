#include <iostream>
#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "CreateFile.hpp"

// apply the hold generator on patterns.txt file
// run the sfinder command
// determine corresponding bitstring from the created file

int main(int argc, char* argv[]){
    CLIParser cli;
    int errorCode = cli.parse(argc, argv);
    if(errorCode){
        return errorCode;
    }

    CreateFile fileCreater(cli.args);

    fileCreater.runSfinderCommand();

    return 0;
}