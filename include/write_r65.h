#ifndef WRITE_R65_H
#define WRITE_R65_H

extern const WRITE_SUCCESS = 0;
extern const FAILED_WRITE = -1;

int write_rom(uint8_t* bytes); // write rom to output file

#endif