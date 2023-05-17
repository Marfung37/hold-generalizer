#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iostream>
#include "SfinderFile.hpp"

SfinderFile::SfinderFile(std::string filename, std::string sfinderFiletype) : filename(filename), sfinderFiletype(sfinderFiletype), inFS(filename), queues(), queueBools() {
    if(!inFS.is_open()){
        std::cout << filename << std::endl;
        throw new std::invalid_argument(filename + " couldn't be opened!");
    }
    
    if(sfinderFiletype == "path"){
        parsePathFile();
    } else if(sfinderFiletype == "cover"){
        parseCoverFile();
    } else {
        throw new std::invalid_argument(sfinderFiletype + " is an unknown type of sfinder file");
    }
}

SfinderFile::~SfinderFile(){
    inFS.close();
}

void SfinderFile::parsePathFile(){
    std::istringstream inSS;
    std::string line;
    std::string queue, numSolves;

    std::getline(inFS, line); // header line

    while(std::getline(inFS, line)){
        inSS.clear();
        inSS.str(line);

        if(!(std::getline(inSS, queue, ','))) break; // line is empty
        queues.push_back(queue);

        std::getline(inSS, numSolves, ',');
        queueBools.push_back(numSolves != "0");
    }
}

void SfinderFile::parseCoverFile(){
    std::istringstream inSS;
    std::string line;
    std::string queue, cell;

    std::getline(inFS, line); // header line

    while(std::getline(inFS, line)){
        inSS.clear();
        inSS.str(line);

        if(!(std::getline(inSS, queue, ','))) break; // line is empty
        queues.push_back(queue);

        bool success = false;
        while(std::getline(inSS, cell, ',')) {
            if(cell == "O"){
                success = true;
                break;
            }
        };
        queueBools.push_back(success);
    }
}