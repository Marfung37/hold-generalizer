#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "CreateFile.hpp"

int main(int argc, char* argv[]){
    CLIParser cli;
    int errorCode = cli.parse(argc, argv);
    if(errorCode){
        return errorCode;
    }

    CreateFile fileCreater(cli.args);

    fileCreater.createFile();
    fileCreater.printData();

    return 0;
}