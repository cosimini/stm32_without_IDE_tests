#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

// This macro is intended to be used for fast bit setting/toggling
#define SET_BIT_32(REG, IDX, BIT) (*REG = (*REG & ~((uint32_t) 0b01 << IDX)) | ((uint32_t) BIT << IDX))

typedef struct regConfStruct{
  uint32_t* reg;
  uint32_t  idx;
  uint32_t  val;
} regConf;

// Set a single bit of a 32, 16 or 8 bits register, alternative to the macro
bool setbit32(uint32_t* target, int index, int value);
bool setbit16(uint16_t* target, int index, int value);
bool setbit8(uint8_t* target, int index, int value);

// Given a regConf structure type, set the configuration
bool setConf(regConf* conf, int index, int value);
void applyConf(regConf* conf);

void resetInterrupt(int idx);

#endif // UTILS_H
