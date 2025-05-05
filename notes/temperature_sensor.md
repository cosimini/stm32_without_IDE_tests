1. Select ADC Vin[12] input channel
2. Select a sampling time > than Ts_temp = 5us
3. Set the TSEN bit in ADC_CCR reg to enable the temperature sensor
4. Wait t_start for stabilization (70 to 120 us)
5. Start the ADC by setting the ADSTART in ADC_CR
6. Read Vsense in ADC_DR
7. The temperature is given at page 376

T = 30 + (TS_DATA - TS_CAL1) * (100 / (TS_CAL2 - TS_CAL1))

From the datasheet:
- Avg_slope = 2.3, 2.5, 2.7  mV/C
- V30       = 0.742, 0.746, 0.785 V
- Ts_temp   = 5 ,- ,- us

From page 24:

Those values are located in the engineering bytes, in read only mode, and written by the manufacturer during tests.

TS_CAL1:  30C -> 0x1fff75a8 - 0x1fff75a9
TS_CAL2: 130C -> 0x1fff75ca - 0x1fff75cb


## TODOs

[ ] Write init for temperature sensor
[X] Write init for the associated ADC
[X] Enable clock for the associated ADC
[X] Write the getTemperature function
