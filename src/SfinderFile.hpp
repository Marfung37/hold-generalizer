#ifndef SFINDER_FILE
#define SFINDER_FILE

#include <fstream>
#include <string>
#include <vector>

class SfinderFile{
    public:
        SfinderFile(std::string filename, std::string sfinderFiletype);
        ~SfinderFile();

        std::vector<std::string> getQueues() {return queues;}
        std::vector<bool> getBools() {return queueBools;}

    private:
        void parsePathFile();
        void parseCoverFile();

        std::string filename;
        std::string sfinderFiletype;
        std::ifstream inFS;

        std::vector<std::string> queues;
        std::vector<bool> queueBools;
};

#endif