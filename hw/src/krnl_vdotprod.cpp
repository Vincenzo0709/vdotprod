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

static void execute(hls::stream<uint32_t> &inStream_A,
                    hls::stream<uint32_t> &inStream_B,
                    hls::stream<uint32_t> &outStream) {

    uint32_t outsum = 0;
    for (int i=0; i<DATA_SIZE; i++) {

        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE
        outsum += inStream_A.read() * inStream_B.read();
    
    }

    outStream << outsum;

}

void krnl_vdotprod(uint32_t *axi_mm) {
    
    #pragma HLS INTERFACE m_axi port = axi_mm depth = DATA_SIZE bundle = gmem0
    
    static hls::stream<uint32_t> inStream_A("input_stream1");
    static hls::stream<uint32_t> inStream_B("input_stream2");
    static hls::stream<uint32_t> outStream("output_stream");

    //#pragma HLS DATAFLOW
    load_input(axi_mm, inStream_A, A_OFFSET);
    load_input(axi_mm, inStream_B, B_OFFSET);
    execute(inStream_A, inStream_B, outStream);
    store_output(axi_mm, outStream, out_OFFSET);

}