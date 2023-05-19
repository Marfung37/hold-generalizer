# hold-generalizer

Handle the creation of n-hold files from no hold

## Command Format

Windows `multihold.exe [options]`
Mac/Linux `./multihold [options]`

## Options

  `-h,--help`                   Print this help message and exit  
  `--sf,--sfinder-file` TEXT:FILE [sfinder.jar]  REQUIRED  
                              File path to a sfinder.jar file  
  `-c,--command` TEXT REQUIRED  command to run sfinder with (path or cover)  
  `--hold` UINT:INT in [0 - 10] REQUIRED  
                              number of hold  
  `--fp,--field-path` TEXT:FILE [input/field.txt]  
                              file path to field file  
  `--pp,--patterns-path` TEXT:FILE [input/patterns.txt]  
                              file path to patterns file  
  `--ppp,--patterms-permutated-path` TEXT:FILE [input/patternsPermutated.txt]  
                              file path to patterns permutated file  
  `-t,--tetfu` TEXT             fumen(s) for sfinder command  
  `-p,--patterns` TEXT          pieces for sfinder command  
  `--mp,--manual-permutate`     permutated patterns has been already created  
  `--of,--output-file` TEXT [output/multihold_{command}.csv]  
                              output filepath of command  
  `-a,--additional` TEXT        other sfinder options to include in command  
