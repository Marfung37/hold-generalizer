#include <filesystem>
#include "../lib/CLI11.hpp"
#include "CLIParser.hpp"
#include "HoldGenerator.hpp"

namespace fs = std::filesystem;

CLIParser::CLIParser() : app{"Create n-hold files from no hold file"}, args{}{
    args.filepath = "";
    args.sfinderFile = "";
    args.fieldFile = fs::path("input") / "field.txt";
    args.patternsFile = fs::path("input") / "patterns.txt";
    args.patternsPermutateFile = fs::path("input") / "patternsPermutated.txt";

    args.command = "";
    args.hold = 0;
    args.tetfu = "";
    args.patterns = "";
    args.manualPermutate = false;
    args.additionalSfinderOptions = "";

    setupParser();
    
}

void CLIParser::afterParse(){
    args.filepath = fs::path("output") / ("multihold_" + args.command + ".csv");
}

void CLIParser::setupParser(){
    app.add_option("--sf, --sfinder-file", args.sfinderFile, "File path to a sfinder.jar file")
        ->check(CLI::ExistingFile)
        ->required();
    app.add_option("-c, --command", args.command, "command to run sfinder with (path or cover)")
        ->required();
    app.add_option("--hold", args.hold, "number of hold")
        ->required()
        ->check(CLI::Range(0, 10));
    app.add_option("--fp, --field-path", args.fieldFile, "file path to field file")
        ->check(CLI::ExistingFile)
        ->default_str(args.fieldFile.string());
    app.add_option("--pp, --patterns-path", args.patternsFile, "file path to patterns file")
        ->check(CLI::ExistingFile)
        ->default_str(args.patternsFile.string());
    app.add_option("--ppp, --patterms-permutated-path", args.patternsPermutateFile, "file path to patterns permutated file")
        ->check(CLI::ExistingFile)
        ->default_str(args.patternsPermutateFile.string());
    app.add_option("-t, --tetfu", args.tetfu, "fumen(s) for sfinder command");
    app.add_option("-p, --patterns", args.patterns, "pieces for sfinder command");
    app.add_flag("--mp, --manual-permutate", args.manualPermutate, "permutated patterns has been already created");
    app.add_option("--of, --output-file", args.filepath, "output filepath of command")
        ->default_str((fs::path("output") / "multihold_{command}.csv").string());
    app.add_option("-a, --additional", args.additionalSfinderOptions, "other sfinder options to include in command");
}

