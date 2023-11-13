#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

class SfinderFile{
    public:
        SfinderFile(std::string filename, std::string sfinderFiletype);

        void parseFile();
        void createMap();
        void writeFile();

        struct columns{
            columns() : queue(), numSolves(0), piecesUsed(), piecesSaved(), solveFumens(), worked(false) {}

            std::string queue;
            unsigned int numSolves;
            std::string piecesUsed;
            std::string piecesSaved;
            std::string solveFumens;
            bool worked;
        };

        std::vector<columns> fileData;
        std::unordered_map<std::string, columns> fileMap;

    private:
        void parsePathFile();
        void parseCoverFile();
        void writePathFile();
        void writeCoverFile();

        std::string filename;
        std::string sfinderFiletype;
        std::string headerLine;
};

