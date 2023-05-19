#ifndef SFINDER_FILE
#define SFINDER_FILE

#include <fstream>
#include <string>
#include <vector>

class SfinderFile{
    public:
        SfinderFile(std::string filename, std::string sfinderFiletype);

        void parseFile();
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

    private:
        void parsePathFile();
        void parseCoverFile();
        void writePathFile();
        void writeCoverFile();

        std::string filename;
        std::string sfinderFiletype;
        std::string headerLine;
};

#endif