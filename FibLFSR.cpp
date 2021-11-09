#include "FibLFSR.h"
#include <math.h>

/**
 * Constructor for FibLFSR.
 * 
 * @param: valid binary string
 * @return: FibLFSR object
 */
FibLFSR::FibLFSR(string seed) {
    FibLFSR::seed = seed;
    FibLFSR::numBit = seed.length();
}

/**
 * Overloaded << for use with FibLFSR class
 * 
 * @param: ostream& and valid FibLFSR class
 * @return: ostream
 */
ostream& operator<<(ostream& out, const FibLFSR& right) {
    out << right.seed;

    return out;
}

/**
 * Initiates a 'step' with the current seed stored in the class. Step will left shift all bits
 * except the rightmost which will be created based on predefined XOR gates
 * 
 * @param: Valid FibLFSR instance
 * @return: Class is updated with new seed after the above logic and 0, 1 is returned based on XOR gates
 */
int FibLFSR::step() {
    string temp;
    char output = seed[0];
    for (int i = 0; i < (int)(seed.length() - 1); i++) {
        temp.push_back(seed[i+1]);
    }

    for (int j = 0; j < (int)(taps.size()); j++) {
        output = (output == seed[taps[j]]) ? '0' : '1';
    }

    temp.push_back(output);
    
    seed = temp;
    
    return (int)(output - '0');
}

/**
 * Calls step() k times with the output being the base10 representation of the k binary numbers 
 * 
 * @param: Instance of class has valid seed
 * @return: Class is updated with seed as step() is called and the base10 value is returned.
 */
int FibLFSR::generate(int k) {
    int value = 0;
    int temp;

    for (int i = 0; i < k; i++) {
        step();
    }

    for (int i = 0; i < k; i++) {
        temp = seed[(numBit - 1) - i] - '0';
        if (temp == 1) {
            value += pow(2, i);
        }
    }

    return value;
}