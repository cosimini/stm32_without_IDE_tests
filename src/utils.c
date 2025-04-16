#include "utils.h"

/*
 * Util function implementation
 */

// Set a single bit, addittional checks are performed
bool setbit32(uint32_t* target, int index, int value) {
  if(index < 0 || index > 31) return false;
  if(!(value == 0 || value == 1)) return false;
  *target = (*target & ~(0b1 << index)) | value << index;
  return true;
}
bool setbit16(uint16_t* target, int index, int value) {
  if(index < 0 || index > 16) return false;
  if(!(value == 0 || value == 1)) return false;
  *target = (*target & ~(0b1 << index)) | value << index;
  return true;
}
bool setbit8(uint8_t* target, int index, int value) {
  if(index < 0 || index > 8) return false;
  if(!(value == 0 || value == 1)) return false;
  *target = (*target & ~(0b1 << index)) | value << index;
  return true;
}

// Use the regConf structure defined in header
bool setConf(regConf* conf, int index, int value) {
  if(index < 0 || index > 31) return false;
  if(!(value == 0 || value == 1)) return false;
  conf->idx = conf->idx | (0b1 << index);
  conf->val = conf->val | (value << index);
  return true;
}

void applyConf(regConf* conf) {
  *conf->reg = (uint32_t) (*conf->reg & ~conf->idx) | conf->val;
  conf->reg = 0;
  conf->val = 0;
}

// TODO: A function to set a chunk of adiacent bits
