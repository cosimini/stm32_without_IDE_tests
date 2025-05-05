/*
 * Set up the temperature sensor
 */

#include <stdint.h>

#define TS_CAL1_TEMP 30
#define TS_CAL1_LSB  0x1fff75a8
#define TS_CAL1_MSB  0x1fff75a9
#define TS_CAL2_TEMP 130
#define TS_CAL2_LSB  0x1fff75ca
#define TS_CAL2_MSB  0x1fff75cb

float getDataADC(void);

float getTemperature(void) {
  uint32_t TS_DATA = getDataADC();
  uint16_t TS_CAL1 = (*(uint16_t*) TS_CAL1_LSB);
  uint16_t TS_CAL2 = (*(uint16_t*) TS_CAL2_LSB);
  return (((TS_CAL2_TEMP - TS_CAL1_TEMP) / (TS_CAL2 - TS_CAL1)) * (TS_DATA - TS_CAL1)) + TS_CAL1_TEMP;
}
