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
using namespace std;


/*class bitsetFP {
private:
    uint32_t bits:

public:
    bitsetFP(float f) {
        memcpy(&bits, &f, sizeof(float));
    }
}; */

// 1 bit sign ---- 8 bit exponent ---- 23 bit mantissa -- Use 
void printIEE(float f) {
    uint32_t bits; //copy bytes from argument
    memcpy(&bits, &f, sizeof(float)); // transform to bits

    // <<print bitset<x> bits with >> x SR and mask
    cout << bitset<1>((bits >> 31) & 0x1) << " " <<
        bitset<8>((bits >> 23) & 0xFF) << " " <<
        bitset<23>(bits & 0x7FFFFF) << endl;
}



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
        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold: " << endl;
        cout << "     " << threshold << endl;
        cout << "     ";
        printIEE(threshold);
    }
    else {
        cout << "No overflow!" << endl;
    }
}


void calcFP(float a, float b) { //Add error for 3 arguments 
    float x = a; //Loop bound 
    float y = b; //Increment value of loop counter

    cout << "Loop bound:   "; 
    printIEE(x);
    cout << "Loop counter: ";
    printIEE(y);
    cout << endl;

    findOverflow(x, y);

 
    
}

int main(){
    float a;
    float b;
    
    cin >> a; //Don't need any prompt
    cin >> b;
    calcFP(a, b);

    return 0;
};


