#include "xil_io.h"
#include <stdbool.h>
#include "xkrnl_vdotprod_hw.h"

#define Xkrnl_BASE                  __peripheral_HLS_Accelerator_Control_start
#define Xkrnl_Control               (Xkrnl_BASE + XKRNL_VDOTPROD_CONTROL_ADDR_AP_CTRL)
#define Xkrnl_GIE                   (Xkrnl_BASE + XKRNL_VDOTPROD_CONTROL_ADDR_GIE)
#define Xkrnl_IER                   (Xkrnl_BASE + XKRNL_VDOTPROD_CONTROL_ADDR_IER)
#define Xkrnl_ISR                   (Xkrnl_BASE + XKRNL_VDOTPROD_CONTROL_ADDR_ISR)
#define Xkrnl_AXI_ADDR              (Xkrnl_BASE + XKRNL_VDOTPROD_CONTROL_ADDR_AXI_MM_DATA)

#define AP_START                    (0x00000001)
#define AP_DONE                     (0x00000002)
#define AP_IDLE                     (0x00000004)
#define AP_READY                    (0x00000008)
#define AP_CONTINUE                 (0x00000010)
#define AP_INTERRUPT                (0x00000020)

#define DATA_SIZE 4
#define EXPCTD DATA_SIZE

#define A_OFFSET 0
#define B_OFFSET DATA_SIZE
#define out_OFFSET 2*DATA_SIZE
#define SIZE_MM 2*DATA_SIZE + 1

void initialize_data(uint32_t *axi_mm) {

    for (int i = 0; i < SIZE_MM; i++) {
        axi_mm[i + A_OFFSET] = 1;
        axi_mm[i + B_OFFSET] = 1;
    }

    axi_mm[out_OFFSET] = 0;

}

// Starts kernel execution
void start_kernel(uint32_t *axi_mm) {

    // Writing input/output addresses
    Xil_Out64(Xkrnl_AXI_ADDR, (uint64_t)axi_mm);

    // Raising ap_start to start the kernel
    Xil_Out32(Xkrnl_Control, AP_START);

    // Waiting for the kernel to finish (polling the ap_done control bit)
    while ( (Xil_In32(Xkrnl_Control) && AP_DONE) != AP_DONE ) {}
}

// Checks the idle status of the kernel
bool is_kernel_idle() {
    return ( (Xil_In32(Xkrnl_Control) && AP_IDLE) == AP_IDLE );
}

// Checks the ready status of the kernel
bool is_kernel_ready() {
    return ( (Xil_In32(Xkrnl_Control) && AP_READY) == AP_READY );
}

bool check_results(uint32_t *axi_mm) {
    return (axi_mm[out_OFFSET] == EXPCTD);
}

int main() {

    uint32_t axi_mm[SIZE_MM];

    // Initializing input/output data
    initialize_data(axi_mm);

    // Starting the kernel
    start_kernel(axi_mm);

    // Checking results
    // if (check_results(out))
    //     return 0;
    // else return 1;
    while(1);

    return 0;

}
