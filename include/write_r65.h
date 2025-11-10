#ifndef WRITE_R65_H
#define WRITE_R65_H
#include <stdint.h>

extern const int WRITE_SUCCESS;
extern const int FAILED_WRITE;

int write_rom(uint8_t* bytes); // write rom to output file

#endif