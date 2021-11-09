#ifndef FIBLFSR_H
#define FIBLFSR_H

#include <vector>
#include <iostream>
using namespace std;

class FibLFSR {
public:
    FibLFSR(string seed);
    friend ostream& operator<<(ostream& out, const FibLFSR& right);
    int step();
    int generate(int k);
private:
    string seed;
    int numBit;
    vector<int> taps{2, 3, 5};
};

#endif /* FIBLFSR_H */