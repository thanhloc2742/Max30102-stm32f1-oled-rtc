# Max30102-stm32f1-oled-rtc

HB and spo2 Measurement 

There are totally three major modes:
1. Display HB and spo2 value, draw pleth graph
2. Display the highest and lowest heart beat per second
3. RTC (real time clock)

Change mode by pressing button PB0
Pressing button PB1 to shutdown or restart MAX30102 and OLED

When starting system, use button PB0 and PB1 to change hour and minute value (if you want to set). After that, pressing button PB3 to store those values for RTC.
If you dont want to set time, just pressing PB3 without setting hour and minute, RTC will automatically count old values.

This system will do with 500 samples before displaying HB and spo2



