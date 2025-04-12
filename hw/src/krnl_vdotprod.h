#ifndef __KRNL_VDOTPROD_H__
#define __KRNL_VDOTPROD_H__

#include <stdint.h>
#include <hls_stream.h>

#define DATA_SIZE 32
#define DATA 1
#define EXPCTD DATA_SIZE

int krnl_vdotprod();

#endif