#ifndef MODE_H
#define MODE_H

RTC_HandleTypeDef hrtc;

RTC_TimeTypeDef sTime;
RTC_DateTypeDef datetoupdate;

uint8_t date, month;
int32_t year;

uint8_t sec;
int32_t hour, minute;
int32_t highest_hb, lowest_hb;

uint32_t aun_ir_buffer[500]; //infrared LED sensor data
uint32_t aun_red_buffer[500]; //red LED sensor data

float n_spo2, ratio, correl; //SPO2 value
int32_t n_heart_rate; //heart rate value
int8_t ch_spo2_valid, ch_hr_valid;
int32_t i;


void delay_ms(uint8_t ms);
void rtc_timer();
void draw_one_chart(uint8_t one_x);
void change_page(uint8_t page);

#endif
