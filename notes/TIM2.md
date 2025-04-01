# General purpose timer TIM2

To use the internal clock to trigger it (CK_INT):
- Slave mode disabled (SMS=000 in TIM2_SMCR)
- Set CEN, DIR in TIM2_CR1
- Set UG in TIM2_EGR

"As soon the CEN bit is written to1, the prescaler is clocked by the internal clock CK_INT"
