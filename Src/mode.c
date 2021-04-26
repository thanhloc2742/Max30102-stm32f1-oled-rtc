#include "main.h"
#include "math.h"
#include "MAX30102.h"
#include "algorithm.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "mode.h"

void change_page(uint8_t page)
{
		if(page == 1)
		{
			ssd1306_Fill(Black);
			ssd1306_Line(0,30,35,30,White);

			ssd1306_SetCursor(34,8);
			ssd1306_WriteString("bpm",Font_6x8, White);
			ssd1306_SetCursor(97,8);
			ssd1306_WriteString("%spo2",Font_6x8, White);
			ssd1306_UpdateScreen();
			//dumping the first 10 sets of samples in the memory and shift the last 40 sets of samples to the top

			for (i = 100; i < 500; i++)
			{
				aun_red_buffer[i - 100] = aun_red_buffer[i];
				aun_ir_buffer[i - 100] = aun_ir_buffer[i];
			}
			//take 10 sets of samples before calculating the heart rate
			for (i = 400; i < 500; i++)
			{
				while (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12) == 1);
				max30102_ReadFifo((aun_ir_buffer + i), (aun_red_buffer + i)); //read from MAX30102 FIFO
			}

			rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer,
					&n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl);

			if (ch_hr_valid && ch_spo2_valid )
			{
					if(n_heart_rate > highest_hb){	highest_hb = n_heart_rate;	}

					if(n_heart_rate < lowest_hb && n_heart_rate > 50){	lowest_hb = n_heart_rate;	}

					//Display heartbeat per minute
					ssd1306_SetCursor(1,0);
					ssd1306_WriteNum(n_heart_rate, Font_11x18, White);

					//Display spo2
					ssd1306_SetCursor(64,0);
					ssd1306_WriteNum(n_spo2, Font_11x18, White);
					ssd1306_UpdateScreen();

					//Draw chart
					if(n_heart_rate < 30){
						draw_one_chart(2);
					}

					if(n_heart_rate > 31 && n_heart_rate < 60){
						draw_one_chart(2);
						draw_one_chart(29);
					}
					if(n_heart_rate > 61 && n_heart_rate < 90){
						draw_one_chart(2);
						draw_one_chart(29);
						draw_one_chart(56);
					}

					if(n_heart_rate > 91 && n_heart_rate < 120){
						draw_one_chart(2);
						draw_one_chart(29);
						draw_one_chart(56);
						draw_one_chart(83);
					}

					if(n_heart_rate > 121){
						draw_one_chart(2);
						draw_one_chart(29);
						draw_one_chart(56);
						draw_one_chart(83);
						draw_one_chart(110);
					}
					//-----------END draw chart---------------

			}//end if: valid

		}

		//-------------------------------END PAGE 1: HB & SPO2 CACULATION-------------------------------

		if(page == 2)
		{
			ssd1306_Fill(Black);
			ssd1306_Line(45,30,80,30,White);

			ssd1306_SetCursor(2,10);
			ssd1306_WriteString("MAX      BPM      MIN",Font_6x8,White);
			ssd1306_SetCursor(2,40);
			ssd1306_WriteNum(highest_hb,Font_11x18,White);
			ssd1306_SetCursor(100,40);
			ssd1306_WriteNum(lowest_hb,Font_11x18,White);

			ssd1306_UpdateScreen();
		}
		//-------------------------------END PAGE 2: MAX AND MIN HB-------------------------------------

		if(page == 3)
		{
			rtc_timer();
			ssd1306_Fill(Black);
			ssd1306_Line(90,30,130,30,White);

			//ssd1306_SetCursor(50,10);
			//ssd1306_WriteString("TIMER",Font_6x8,White);
			ssd1306_SetCursor(20,10);
			ssd1306_WriteNum(date,Font_7x10,White);
			ssd1306_SetCursor(35,10);
			ssd1306_WriteString(" / ",Font_7x10,White);
			ssd1306_SetCursor(50,10);
			ssd1306_WriteNum(month,Font_7x10,White);
			ssd1306_SetCursor(65,10);
			ssd1306_WriteString(" / ",Font_7x10,White);
			ssd1306_SetCursor(80,10);
			ssd1306_WriteNum(20,Font_7x10 ,White);
			ssd1306_SetCursor(95,10);
			ssd1306_WriteNum(year,Font_7x10 ,White);


			ssd1306_SetCursor(35,40);
			ssd1306_WriteNum(hour,Font_11x18,White);
			ssd1306_SetCursor(60,40);
			ssd1306_WriteString(":",Font_11x18,White);
			ssd1306_SetCursor(75,40);
			ssd1306_WriteNum(minute,Font_11x18,White);

			ssd1306_SetCursor(100,50);
			ssd1306_WriteNum(sec,Font_7x10,White);

			ssd1306_UpdateScreen();
		}
		//----------------------------------END PAGE 3: CLOCK--------------------------------------------
}

void rtc_timer(){
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &datetoupdate,RTC_FORMAT_BIN);

	sec = sTime.Seconds;
	hour = sTime.Hours;
	minute = sTime.Minutes;
	date = datetoupdate.Date;
	month = datetoupdate.Month;
	year = datetoupdate.Year;
}


void draw_one_chart(uint8_t one_x)
{
			ssd1306_DrawPixel(one_x,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,59,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,58,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,57,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,56,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,55,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,54,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,53,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x,52,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 1,52,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 1,51,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 1,50,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 1,49,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 2,48,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 2,47,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 2,46,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 2,45,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 2,44,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 3,43,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 3,42,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 3,43,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 4,41,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 5,41,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 6,42,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 7,43,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 7,44,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 7,45,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 7,46,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 8,47,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 8,48,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 8,49,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 9,50,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 9,51,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 9,52,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 10,52,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 11,51,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 12,50,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 13,50,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 14,51,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 15,52,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 15,53,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 15,54,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 16,55,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 16,56,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 16,57,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 17,58,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 18,59,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 18,60,White);
			ssd1306_UpdateScreen();


			ssd1306_DrawPixel(one_x + 19,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 20,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 21,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 22,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 23,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 24,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 25,60,White);
			ssd1306_UpdateScreen();

			ssd1306_DrawPixel(one_x + 26,60,White);
			ssd1306_UpdateScreen();
}
