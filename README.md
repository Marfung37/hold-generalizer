# hold-generalizer

Handle the creation of n-hold files from no hold

## Command Format

Windows `multihold.exe [options]`  
Mac/Linux `./multihold [options]`

## Options

  `-h,--help` - Print this help message and exit  
  `--sf,--sfinder-file` REQUIRED  - File path to a sfinder.jar file  
  `-c,--command` REQUIRED  command to run sfinder with (path or cover)  
  `--hold` REQUIRED - number of hold  
  `--fp,--field-path` [input/field.txt] - file path to field file  
  `--pp,--patterns-path` [input/patterns.txt] - file path to patterns file  
  `--ppp,--patterms-permutated-path` [input/patternsPermutated.txt] - file path to patterns permutated file  
  `-t,--tetfu`              - fumen(s) for sfinder command  
  `-p,--patterns`           - pieces for sfinder command  
  `--mp,--manual-permutate`     - permutated patterns has been already created  
  `--of,--output-file`  [output/multihold_{command}.csv] - output filepath of command  
  `-a,--additional`         - other sfinder options to include in command  
