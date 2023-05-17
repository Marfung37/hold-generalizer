#include <algorithm>
#include <string>
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

    permutationHelper(currQueue);

    for(unsigned int i = 0; i < permutations.size(); i++){
        std::reverse(permutations.at(i).begin(), permutations.at(i).end());
    }
}

bool HoldGenerator::contains(std::string queue){
    return std::find(permutations.begin(), permutations.end(), queue) != permutations.end();
}

void HoldGenerator::permutationHelper(std::string queue, std::string prefix){
    if(queue.empty()){
        permutations.push_back(prefix);
    } else {
        unsigned int shiftedHold = this->hold + 1;
        if(shiftedHold > queue.length()){
            shiftedHold = queue.length();
        }

        for(unsigned int offset = 0; offset < shiftedHold; offset++){
            permutationHelper(queue.substr(0, offset) + queue.substr(offset + 1), prefix + queue.at(offset));
        }
    }
}