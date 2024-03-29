#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class HoldGenerator{
    public:
        HoldGenerator() : queue(""), hold(0), cycle(-1), permutations{}, memoization{} {}
        HoldGenerator(std::string queue, unsigned int hold) : queue(queue), hold(hold), cycle(-1), permutations{}, memoization{} {}
        HoldGenerator(std::string queue, unsigned int hold, unsigned int cycle) : queue(queue), 
                                                                                  hold(hold), 
                                                                                  cycle(cycle), 
                                                                                  permutations{}, 
                                                                                  memoization{} {}
        
        void generatePermutations();
        void generateInversePermutations();
        bool permutationContains(std::string givenQueue);
        bool inversePermutationContains(std::string givenQueue);
        bool contains(std::string givenQueue);

        std::unordered_set<std::string> getPermutations() const {return permutations;}
        void clearPermutations() {permutations.clear();}

        void setQueue(std::string queue) {this->queue = queue;}
        void setHold(unsigned int hold) {
            if(this->hold != hold){
                this->hold = hold;
                memoization.clear();
            }
        }

    private:
        std::vector<std::string> permutationHelper(std::string queue, std::string prefix="", bool reverse=false);
        bool permutationContainsHelper(std::string queue, std::string givenQueue);

        std::string queue;
        unsigned int hold;
        unsigned int cycle;
        std::unordered_set<std::string> permutations;
        std::unordered_map<std::string, std::vector<std::string>> memoization;
        
};
