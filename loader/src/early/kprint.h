#pragma once

// simple formatting print function:
// %[size][format]
//
// special cases:
// %% - % literal
// %s - null terminated string
//
// sizes:
// q - 64 bit
// d - 32 bit
// w - 16 bit
// b - 8  bit
// p - pointer
//
// formats:
// u - unsinged int
// x - unsigned hex int (without 0x prefix)
// i - signed int
void kprint(const char *format, ...);
