#include <iostream>
#include <string>
#include "../src/HoldGenerator.hpp"

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

void print(std::unordered_set<std::string> const &s)
{
    for(auto const &i: s){
        std::cout << i << ", ";
    }
}

int main(){
    HoldGenerator queues("", 0);

    queues.generatePermutations();
    IS_TRUE(queues.contains(""));

    queues.setHold(1);
    queues.generatePermutations();
    IS_TRUE(queues.contains(""));

    queues.setQueue("ABCD");
    queues.setHold(0);

    queues.generatePermutations();
    IS_TRUE(queues.getPermutations().size() == 1);
    IS_TRUE(queues.contains("ABCD"));
    queues.generateInversePermutations();
    IS_TRUE(queues.getPermutations().size() == 1);
    IS_TRUE(queues.contains("ABCD"));
    
    queues.setHold(1);

    queues.generatePermutations();
    std::string knownPermutations0[8] = {"ACBD", "ACDB", "ABCD", "BCAD", "BCDA", "ABDC", "BADC", "BACD"};

    IS_TRUE(queues.getPermutations().size() == 8);
    for(std::string permutation: knownPermutations0){
        IS_TRUE(queues.contains(permutation));
    }

    queues.generateInversePermutations();
    std::string knownPermutations1[8] = {"CABD", "BACD", "ABDC", "DABC", "BADC", "ABCD", "ACBD", "ADBC"};

    IS_TRUE(queues.getPermutations().size() == 8);
    for(std::string permutation: knownPermutations1){
        IS_TRUE(queues.contains(permutation));
    }

    queues.setHold(2);

    queues.generatePermutations();
    std::string knownPermutations2[18] = {"CDAB", "CBAD", "BADC", "CBDA", "ADCB", "BCAD", "ACBD", "ABCD", "BDCA", "ADBC", "ABDC", "BACD", "CABD", "BCDA", "CADB", "ACDB", "CDBA", "BDAC"};

    IS_TRUE(queues.getPermutations().size() == 18);
    for(std::string permutation: knownPermutations2){
        IS_TRUE(queues.contains(permutation));
    }

    queues.generateInversePermutations();
    std::string knownPermutations3[18] = {"ADCB", "BDAC", "ACBD", "CABD", "BCAD", "CBAD", "CDAB", "ABDC", "ABCD", "DABC", "ADBC", "CADB", "DACB", "BACD", "DCAB", "BADC", "DBAC", "ACDB"};

    IS_TRUE(queues.getPermutations().size() == 18);
    for(std::string permutation: knownPermutations3){
        IS_TRUE(queues.contains(permutation));
    }

    queues.setHold(3);

    queues.generatePermutations();
    std::string knownPermutations4[24] = {"BCDA", "CADB", "DACB", "ABCD", "ADCB", "BACD", "CDBA", "BCAD", "ACBD", "DABC", "BADC", "ABDC", "DBAC", "ACDB", "CABD", "CBAD", "DBCA", "BDAC", "CDAB", "DCAB", "BDCA", "ADBC", "DCBA", "CBDA"};

    IS_TRUE(queues.getPermutations().size() == 24);
    for(std::string permutation: knownPermutations4){
        IS_TRUE(queues.contains(permutation));
    }

    // testing contains
    queues.setQueue("JIITS");
    queues.setHold(1);
    IS_TRUE(queues.permutationContains("IJTSI"));
    IS_TRUE(!queues.permutationContains("ITIJS"));
    IS_TRUE(queues.permutationContains("IITSJ"));
    IS_TRUE(queues.permutationContains("JIITS"));

    queues.setHold(2);
    IS_TRUE(queues.permutationContains("IJTSI"));
    IS_TRUE(queues.permutationContains("ITIJS"));
    IS_TRUE(queues.permutationContains("IITSJ"));
    IS_TRUE(queues.permutationContains("JIITS"));
    IS_TRUE(queues.permutationContains("ITJSI"));
    IS_TRUE(queues.permutationContains("ITSJI"));
    IS_TRUE(queues.permutationContains("JISIT"));
    IS_TRUE(!queues.permutationContains("TIIJS"));

    queues.setQueue("JLITI");
    queues.setHold(1);
    IS_TRUE(queues.inversePermutationContains("IJLTI"));
    IS_TRUE(queues.inversePermutationContains("JLITI"));
    IS_TRUE(queues.inversePermutationContains("JLITI"));
    IS_TRUE(!queues.inversePermutationContains("ITJLI"));
    IS_TRUE(!queues.inversePermutationContains("IJITL"));

    queues.setHold(2);
    IS_TRUE(queues.inversePermutationContains("IJLTI"));
    IS_TRUE(queues.inversePermutationContains("JLITI"));
    IS_TRUE(queues.inversePermutationContains("JLITI"));
    IS_TRUE(queues.inversePermutationContains("ITJLI"));
    IS_TRUE(!queues.inversePermutationContains("IJITL"));
    IS_TRUE(!queues.inversePermutationContains("TIIJL"));
    IS_TRUE(queues.inversePermutationContains("LIJIT"));
}
