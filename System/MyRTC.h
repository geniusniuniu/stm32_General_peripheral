#ifndef __MyRTC_H
#define __MyRTC_H

typedef struct 
{
	uint16_t Year;
	uint8_t  Month;
	uint8_t  Day;
	uint8_t  Hour;
	uint8_t  Minute;
	uint8_t  Second;
		
}MyRTC_TimeStructTypeDef;

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);


#endif
