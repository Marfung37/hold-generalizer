#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <unordered_map>
#include "SfinderFile.hpp"

SfinderFile::SfinderFile(std::string filename, std::string sfinderFiletype) : fileData{}, fileMap{}, filename(filename), sfinderFiletype(sfinderFiletype), headerLine() {}

void SfinderFile::parseFile(){
    if(sfinderFiletype == "path"){
        parsePathFile();
    } else if(sfinderFiletype == "cover"){
        parseCoverFile();
    } else {
        throw new std::invalid_argument(sfinderFiletype + " is an unknown type of sfinder file");
    }
}

void SfinderFile::writeFile(){
    if(sfinderFiletype == "path"){
        writePathFile();
    } else if(sfinderFiletype == "cover"){
        writeCoverFile();
    } else {
        throw new std::invalid_argument(sfinderFiletype + " is an unknown type of sfinder file");
    }

}

void SfinderFile::parsePathFile(){
    std::istringstream inColsSS;
    std::istringstream inCurrColSS;
    std::string line;
    std::ifstream inFS(filename);
    
    if(!inFS.is_open()){
        throw new std::invalid_argument(filename + " couldn't be opened!");
    }

    std::getline(inFS, line); // header line
    headerLine = line;

    while(std::getline(inFS, line)){
        inColsSS.clear();
        inColsSS.str(line);

        columns data;

        if(!(std::getline(inColsSS, data.queue, ','))) break; // line is empty

        std::string numSolvesStr;
        std::getline(inColsSS, numSolvesStr, ',');
        data.numSolves = atoi(numSolvesStr.c_str());
        data.worked = data.numSolves != 0;

        std::getline(inColsSS, data.piecesUsed, ',');
        std::getline(inColsSS, data.piecesSaved, ',');
        std::getline(inColsSS, data.solveFumens, ',');

        fileData.push_back(data);
    }
    inFS.close();
}

void SfinderFile::parseCoverFile(){
    std::istringstream inSS;
    std::string line;
    std::string queue, cell;
    std::ifstream inFS(filename);
    
    if(!inFS.is_open()){
        throw new std::invalid_argument(filename + " couldn't be opened!");
    }

    std::getline(inFS, line); // header line
    headerLine = line;
    
    // change header line to turn all commas after first one to semi-colons
    int firstCommaIndex = headerLine.find(',') + 1;
    size_t nextCommaIndex;
    while((nextCommaIndex = headerLine.find(',', firstCommaIndex)) != std::string::npos){
        headerLine.at(nextCommaIndex) = ';';
    }

    while(std::getline(inFS, line)){
        inSS.clear();
        inSS.str(line);

        columns data;

        if(!(std::getline(inSS, data.queue, ','))) break; // line is empty

        bool success = false;
        while(std::getline(inSS, cell, ',')) {
            if(cell == "O"){
                success = true;
                break;
            }
        };
        data.worked = success;

        fileData.push_back(data);
        fileMap.insert({data.queue, data});
    }
    inFS.close();
}

void SfinderFile::createMap(){
    for(columns& data: fileData){
        fileMap.insert({data.queue, data});
    }
}

void SfinderFile::writePathFile(){
    std::ofstream outFS(filename);

    outFS << headerLine << std::endl;
    
    for(SfinderFile::columns& line: fileData){
        std::string lineStr = "";
        
        lineStr += line.queue + ",";
        lineStr += std::to_string(line.numSolves) + ",";
        lineStr += line.piecesUsed + ",";
        lineStr += line.piecesSaved + ",";
        lineStr += line.solveFumens;

        outFS << lineStr << std::endl;
    }
    outFS.close();
}

void SfinderFile::writeCoverFile(){
    std::ofstream outFS(filename);

    outFS << headerLine << std::endl;

    for(SfinderFile::columns& line: fileData){
        std::string lineStr = "";

        lineStr += line.queue + ",";
        lineStr += (line.worked) ? "O" : "X";

        outFS << lineStr << std::endl;
    }
    outFS.close();
}