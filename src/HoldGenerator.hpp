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
        bool contains(std::string queue);

        std::unordered_set<std::string> getPermutations() const {return permutations;}
        void clearPermutations() {permutations.clear();}

        void setQueue(std::string queue) {this->queue = queue;}
        void setHold(unsigned int hold) {this->hold = hold;}

    private:
        void permutationHelper(std::string queue, std::string prefix="", bool reverse=false);

        std::string queue;
        unsigned int hold;
        std::unordered_set<std::string> permutations;

};

#endif