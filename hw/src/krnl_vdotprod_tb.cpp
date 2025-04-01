#include <iostream>
#include "krnl_vdotprod.h"
using namespace std;

bool check_value(uint32_t *axi_mm) {
    
    uint32_t outsum = axi_mm[out_OFFSET];

    if (EXPCTD!=outsum) {
        cout << endl << "[ERROR] Not expected result!" << endl;
        return false;
    } else return true;
}

int main(int argc, const char **argv) {

    uint32_t axi_mm[SIZE_MM];
    const int size = DATA_SIZE;

    for (int i=0; i<SIZE_MM - 1; i++) {
        axi_mm[i] = 1;
    }
    axi_mm[SIZE_MM - 1] = 0;

    krnl_vdotprod(axi_mm);

    return !check_value(axi_mm);
}