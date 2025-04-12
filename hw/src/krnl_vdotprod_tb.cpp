#include <iostream>
#include "krnl_vdotprod.h"
using namespace std;

bool check_value(uint32_t val) {
    
    if (EXPCTD != val) {
        cout << endl << "[ERROR] Not expected result!" << endl;
        return false;
    } else return true;

}

int main(int argc, const char **argv) {

    return !check_value(krnl_vdotprod());

}