#ifndef GEN_HOLD_PERMUTATION
#define GEN_HOLD_PERMUTATION
#include <vector>
#include <string>

class HoldGenerator{
    public:
        HoldGenerator(std::string queue, unsigned int hold) : queue(queue), hold(hold) {}
        
        void generatePermutations();
        void generateInversePermutations();
        bool contains(std::string queue);

        std::vector<std::string> getPermutations() const {return permutations;}
        void clearPermutations() {permutations.clear();}

        void setQueue(std::string queue) {this->queue = queue;}
        void setHold(unsigned int hold) {this->hold = hold;}

    private:
        void permutationHelper(std::string queue, std::string prefix="");

        std::vector<std::string> permutations;
        std::string queue;
        unsigned int hold;

};

#endif