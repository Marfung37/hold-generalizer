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

bool HoldGenerator::permutationContains(std::string givenQueue){
    std::string startQueue = this->queue;
    
    return permutationContainsHelper(startQueue, givenQueue);
}

bool HoldGenerator::inversePermutationContains(std::string givenQueue){
    std::string startQueue = this->queue;

    // reverse both queues
    std::reverse(startQueue.begin(), startQueue.end());
    std::reverse(givenQueue.begin(), givenQueue.end());

    return permutationContainsHelper(startQueue, givenQueue);
}

bool HoldGenerator::contains(std::string givenQueue){
    return permutations.find(givenQueue) != permutations.end();
}

void HoldGenerator::permutationHelper(std::string queue, std::string prefix, bool reverse){
    if(queue.empty()){
        if(reverse){
            std::reverse(prefix.begin(), prefix.end());
        }
        permutations.insert(prefix);
        return;
    }

    unsigned int shiftedHold = this->hold + 1;
    if(shiftedHold > queue.length()){
        shiftedHold = queue.length();
    }

    for(unsigned int offset = 0; offset < shiftedHold; offset++){
        permutationHelper(queue.substr(0, offset) + queue.substr(offset + 1), prefix + queue.at(offset), reverse);
    }
}

bool HoldGenerator::permutationContainsHelper(std::string queue, std::string givenQueue){
    if(queue == givenQueue){
        return true;
    }
    bool foundMatch = false;

    unsigned int shiftedHold = this->hold + 1;
    if(shiftedHold > queue.length()){
        shiftedHold = queue.length();
    }

    for(unsigned int offset = 0; offset < shiftedHold; offset++){
        if(queue.at(offset) == givenQueue.front()){
            // swap the characters
            char tmpChar = queue.at(0);
            queue.at(0) = queue.at(offset);
            queue.at(offset) = tmpChar;

            if(permutationContainsHelper(queue.substr(1), givenQueue.substr(1))){
                foundMatch = true;
                break;
            }
        }
    }

    return foundMatch;
}