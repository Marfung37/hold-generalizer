#include <filesystem>
#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "HoldGenerator.hpp"

namespace fs = std::filesystem;

CLIParser::CLIParser() : app{"Create n-hold files from no hold file"}, args{}{
    args.filepath = "";
    args.sfinderFile = "sfinder.jar";
    args.fieldFile = fs::path("input") / "field.txt";
    args.patternsFile = fs::path("input") / "patterns.txt";

    args.command = "";
    args.hold = 0;
    args.tetfu = "";
    args.patterns = "";
    args.additionalSfinderOptions = "";

    setupParser();
    
}

int CLIParser::parse(int argc, char* argv[]){
    CLI11_PARSE(app, argc, argv);

    args.filepath = fs::path("output") / ("nohold_" + args.command + ".csv");

    return 0;
}

void CLIParser::setupParser(){
    app.add_option("--sf, --sfinder-file", args.sfinderFile, "File path to a sfinder.jar file")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("-c, --command", args.command, "command to run sfinder with (path or cover)")
        ->required();
    app.add_option("--hold", args.hold, "number of hold")
        ->required();
    app.add_option("--fp, --field-path", args.fieldFile, "file path to field file")
        ->check(CLI::ExistingFile)
        ->default_str(args.fieldFile.string());
    app.add_option("--pp, --patterns-path", args.patternsFile, "file path to patterns file")
        ->check(CLI::ExistingFile)
        ->default_str(args.patternsFile.string());
    app.add_option("-t, --tetfu", args.tetfu, "fumen(s) for sfinder command");
    app.add_option("-p, --patterns", args.patterns, "pieces for sfinder command");
    app.add_option("--of, --output-file", args.filepath, "output filepath of command");
    app.add_option("-a, --additional", args.additionalSfinderOptions, "other sfinder options to include in command");
}

