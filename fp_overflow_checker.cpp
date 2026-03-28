// Author: Jason Strouphauer



// Note: 
// 1: get IEE representation. 2: Find OF. 3.: OF threshold
//memcpy or bitcast - try memcpy
//bitset
// float = 4 bytes = 32 bits
// OF when 

#include <iostream>
#include <bitset>
//#include <bit>
#include <cstring>
#include <iomanip>
#include <string> //for stof (string to float)
using namespace std;


class bitsetFP {
private:
    uint32_t bits;

public:
    bitsetFP(float f) {
        memcpy(&bits, &f, sizeof(float));
    }

    bitset<23> mantissa() {
        return bitset<23>(bits & 0x7FFFFF);
    }

    bitset<1> sign() {
        return bitset<1>((bits >> 31) & 0x1);
    }

    bitset<8> exponent() {
        return bitset<8>((bits >> 23) & 0xFF);
    }

    int expInt() {
        return (bits >> 23) & 0xFF;
    }

    void print() {
        cout << sign() << " " << exponent() << " " << mantissa() << endl;
    }

    //***Need this to retrieve flaot from bits***
    float toFloat() {
        float f;
        memcpy(&f, &bits, sizeof(float));
        return f;
    }
}; 


void findOverflow(float a, float b) {
    uint32_t bitFloat1;
    uint32_t bitFloat2;

    memcpy(&bitFloat1, &a, sizeof(float));
    memcpy(&bitFloat2, &b, sizeof(float));

    int exp1 = (bitFloat1 >> 23) & 0xFF;
    int exp2 = (bitFloat2 >> 23) & 0xFF;

    //Find threshold
    uint32_t thresholdExp = exp2 + 23;
    uint32_t threshBits = (thresholdExp << 23);

    float threshold;
    memcpy(&threshold, &threshBits, sizeof(float));
    

    if ((exp1 - exp2) > 23) {
        bitsetFP t(threshold);

        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold: " << endl;
        cout << "     " << threshold << endl;
        cout << "     ";
        t.print();
    }
    else {
        cout << "No overflow!" << endl;
    }
}


void calcFP(float a, float b) { //Add error for 3 arguments 
    bitsetFP x(a); //Loop 
    bitsetFP y(b); //Increment value of loop counter

    cout << "Loop bound:   "; 
    x.print();
    cout << "Loop counter: ";
    y.print();
    cout << endl;

    //need float conversion
    //findOverflow(x, y);
    findOverflow(x.toFloat(), y.toFloat());
 
    
}

int main(int argc, char* argv[]) {
    //3 arguments not 2 - program name, 2 inputs
    if (argc != 3) {
        cout << "Usage:" << argv[0] << " loop_bound loop_counter" << endl;
        cout << "loop_bound is a positive floating-point value" << endl;
        cout << "loop_counter is a positive floating-point value" << endl;
        return 1;
    }

    float loop_bound = stof(argv[1]);
    float loop_counter = stof(argv[2]);
    
    //cin >> a; //Don't need any prompt
    //cin >> b;
    calcFP(loop_bound, loop_counter);

    return 0;
}


