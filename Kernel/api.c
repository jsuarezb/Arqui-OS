#include <stdint.h>
#include "include/keyboard.h"
#define SECONDS 	0x00      
#define MINUTES 	0x02
#define HOURS 		0x04
#define DAY 		0x07
#define MONTH 		0x08
#define YEAR 		0x09

typedef struct date {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
   	uint8_t minute;
   	uint8_t second;
} date;

/*
 * Reads from `fd`, `count` amount of chars and
 * stores it into `buf`
 */
signed int read(unsigned int fd, char * buf, int count)
{
	signed int bytes = 0;

	if (fd == STDIN) {
		int i;
		for (i = 0; i < count && !isBufferEmpty(); i++) {
			buf[i] = getKey();
			bytes++;
		}
	}

	return bytes;
}

/*
 * Writes `count` amount of bytes from `buf` into `fd`
 */
signed int write(unsigned int fd, const char * buf, int count)
{
	signed int bytes = 0;

	if (fd == STDOUT) {
		while (count) {
			_vWrite(buf[bytes]);
			bytes++;
			count--;
		}
	}

	return bytes;
}

void getRTC(date * current_date)
{
	current_date->second = get_date(SECOND);
	current_date->minute = get_date(MINUTE);
	current_date->hour = get_date(HOUR);
	current_date->day = get_date(DAY);
	current_date->month = get_date(MONTH);
	current_date->year = get_date(YEAR);
	BCDtoBinary(current_date);
}

void setRTC(date * set_time)
{
	setDate(SECOND, set_time->second)
	setDate(MINUTE, set_time->minute)
	setDate(HOUR, set_time->hour)
	setDate(DAY, set_time->day)
	setDate(MONTH, set_time->month)
	setDate(YEAR, set_time->year)
}

void BCDtoBinary(date * date) {
 date->day = (date->day & 0x0F) + ((date->day / 16) * 10);
 date->month = (date->month & 0x0F) + ((date->month / 16) * 10);
 date->year = (date->year & 0x0F) + ((date->year / 16) * 10);
 date->second = (date->second & 0x0F) + ((date->second / 16) * 10);
 date->minute = (date->minute & 0x0F) + ((date->minute / 16) * 10);
 date->hour = (date->hour & 0x0F) + ((date->hour / 16) * 10);
}

