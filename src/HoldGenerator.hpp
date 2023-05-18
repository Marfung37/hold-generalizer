#ifndef GEN_HOLD_PERMUTATION
#define GEN_HOLD_PERMUTATION
#include <vector>
#include <string>
#include <unordered_set>

class HoldGenerator{
    public:
        HoldGenerator() : queue(""), hold(0), permutations{} {}
        HoldGenerator(std::string queue, unsigned int hold) : queue(queue), hold(hold), permutations{} {}
        
        void generatePermutations();
        void generateInversePermutations();
        bool permutationContains(std::string givenQueue);
        bool inversePermutationContains(std::string givenQueue);
        bool contains(std::string givenQueue);

        std::unordered_set<std::string> getPermutations() const {return permutations;}
        void clearPermutations() {permutations.clear();}

        void setQueue(std::string queue) {this->queue = queue;}
        void setHold(unsigned int hold) {this->hold = hold;}

    private:
        void permutationHelper(std::string queue, std::string prefix="", bool reverse=false);
        bool permutationContainsHelper(std::string queue, std::string givenQueue);

        std::string queue;
        unsigned int hold;
        std::unordered_set<std::string> permutations;

};

#endif