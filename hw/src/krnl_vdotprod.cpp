#include "krnl_vdotprod.h"

static void load_input( uint32_t *in,
                        hls::stream<uint32_t> &inStream,
                        const uint32_t offset) {

    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        inStream << in[offset + i];
    
    }

}

static void store_output(   uint32_t *out, 
                            hls::stream<uint32_t> &outStream,
                            const uint32_t offset) {

    out[offset] = outStream.read();
    
}

static uint32_t execute(uint32_t *A, uint32_t *B) {

    uint32_t outsum = 0;
    for (int i=0; i<DATA_SIZE; i++) {

        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE
        outsum += A[i] * B[i];
    
    }

    return outsum;

}

int krnl_vdotprod() {

    uint32_t A[DATA_SIZE];
    uint32_t B[DATA_SIZE];

    for (int i=0; i<DATA_SIZE; i++) {
        A[i] = DATA;
        B[i] = DATA;
    }
    
    return execute(A, B); 

}