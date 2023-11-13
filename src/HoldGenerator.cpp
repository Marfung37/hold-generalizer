#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "HoldGenerator.hpp"

void HoldGenerator::generatePermutations(){
    std::string currQueue = this->queue;
    permutations.clear();

    if(!currQueue.empty()){
        permutationHelper(currQueue);
    }
}

void HoldGenerator::generateInversePermutations(){
    std::string currQueue = this->queue;
    std::reverse(currQueue.begin(), currQueue.end());
    permutations.clear();

    if(!currQueue.empty()){
        permutationHelper(currQueue, "", true);
    }
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
    if(givenQueue.empty())
        return true;
    return permutations.find(givenQueue) != permutations.end();
}

std::vector<std::string> HoldGenerator::permutationHelper(std::string queue, std::string prefix, bool reverse){
    std::vector<std::string> suffixes;

    // base case
    if(queue.empty()){
        if(reverse){
            std::reverse(prefix.begin(), prefix.end());
        }
        permutations.insert(prefix);

        suffixes = std::vector<std::string>();
        suffixes.push_back(queue);
        return suffixes;
    }


    // if in memoization
    if(memoization.find(queue) != memoization.end()){
        // add all the suffixes
        suffixes = memoization.at(queue);
        for(auto it = suffixes.begin(); it != suffixes.end(); it++){
            std::string fullQueue = prefix + *it;
            if(reverse){
                std::reverse(fullQueue.begin(), fullQueue.end());
            }
            permutations.insert(fullQueue);
        }

        return suffixes;
    }

    // determine the valid number of hold
    unsigned int shiftedHold = this->hold + 1;
    if(shiftedHold > queue.length()){
        shiftedHold = queue.length();
    }

    suffixes = std::vector<std::string>();
    for(unsigned int offset = 0; offset < shiftedHold; offset++){
        char piece = queue.at(offset);
        std::string newQueue = queue.substr(0, offset) + queue.substr(offset + 1);

        std::vector<std::string> permutatedSuffixes = permutationHelper(newQueue, prefix + piece, reverse);

        // prepend the piece for all permutatedSuffixes
        for(auto it = permutatedSuffixes.begin(); it != permutatedSuffixes.end(); it++){
            suffixes.push_back(piece + *it);
        }

        if(offset == cycle - 1){
            offset = this->hold - 1;
        }

    }
    
    // add to memoization
    memoization.insert(std::make_pair(queue, suffixes));

    return suffixes;
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
        if(offset == cycle - 1){
            offset = this->hold - 1;
        }
    }

    return foundMatch;
}
