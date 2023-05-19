#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "CreateFile.hpp"

#include <iostream>

int main(int argc, char* argv[]){
    CLIParser cli;
    CLI11_PARSE(cli.app, argc, argv);
    cli.afterParse();

    CreateFile fileCreater(cli.args);
    fileCreater.createFile();
    fileCreater.printData();

    return 0;
}