#ifndef __KRNL_VDOTPROD_H__
#define __KRNL_VDOTPROD_H__

#include <stdint.h>
#include <hls_stream.h>

#define DATA_SIZE 32
#define EXPCTD DATA_SIZE

#define A_OFFSET 0
#define B_OFFSET DATA_SIZE
#define out_OFFSET 2*DATA_SIZE
#define SIZE_MM 2*DATA_SIZE + 1

void krnl_vdotprod(uint32_t *);

#endif