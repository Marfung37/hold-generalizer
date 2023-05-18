#include <iostream>
#include <string>
#include "../lib/CLI11.hpp"
#include "../src/CLIParser.hpp"

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }
using std::cout, std::endl;

int main(int argc, char* argv[]){
    CLIParser cli;

    int errorCode = cli.parse(argc, argv);
    if(errorCode){
        return errorCode;
    }

    CLIParser::values args = cli.args;

    cout << "filepath: "        << args.filepath << endl;
    cout << "sfinder file: "    << args.sfinderFile << endl;
    cout << "field file: "      << args.fieldFile << endl;
    cout << "patterns file: "   << args.patternsFile << endl;
    cout << "command: "         << args.command << endl;
    cout << "hold: "            << args.hold << endl;
    cout << "fumen(s): "        << args.tetfu << endl;
    cout << "patterns: "        << args.patterns << endl;
    cout << "additional args: " << args.additionalSfinderOptions << endl;

    return 0;
}