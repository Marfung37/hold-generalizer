#include <algorithm>
#include <string>
#include <unordered_set>
#include "HoldGenerator.hpp"

void HoldGenerator::generatePermutations(){
    std::string currQueue = this->queue;
    permutations.clear();

    permutationHelper(currQueue);
}

void HoldGenerator::generateInversePermutations(){
    std::string currQueue = this->queue;
    std::reverse(currQueue.begin(), currQueue.end());
    permutations.clear();

    permutationHelper(currQueue, "", true);
}

bool HoldGenerator::contains(std::string queue){
    return permutations.find(queue) != permutations.end();
}

void HoldGenerator::permutationHelper(std::string queue, std::string prefix, bool reverse){
    if(queue.empty()){
        if(reverse){
            std::reverse(prefix.begin(), prefix.end());
        }
        permutations.insert(prefix);
    } else {
        unsigned int shiftedHold = this->hold + 1;
        if(shiftedHold > queue.length()){
            shiftedHold = queue.length();
        }

        for(unsigned int offset = 0; offset < shiftedHold; offset++){
            permutationHelper(queue.substr(0, offset) + queue.substr(offset + 1), prefix + queue.at(offset), reverse);
        }
    }
}