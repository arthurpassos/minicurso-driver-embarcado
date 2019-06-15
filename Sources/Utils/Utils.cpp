/*
 * Utils.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: PC
 */

#include "Utils.h"
#include "FreeRTOS.h"
//#include "task.h"
//#include "projdefs.h"
#include "UTIL1.h"
#include "semphr.h"

void Utils::delay(uint32_t ms)
{
	vTaskDelay(pdMS_TO_TICKS(ms));
}

unsigned short int Utils::calculate_crc16(unsigned char *Buffer, int Cont)
{
	int i;
	unsigned char j;
	unsigned char NewChar;
	short int Test;
	short int CRCWord;
	CRCWord = 0xFFFF;

	for(i = 0; i < Cont; i++)
	{
		NewChar = Buffer[i];
		for(j = 0; j < 8; j++)
		{
			Test = (short int) (NewChar & 0x00FF);
			Test = (short int) (Test << (j + 8));
			Test = Test ^ CRCWord;
			Test = (short int) (Test & 0x8000);
			if(Test)
			{
				CRCWord = (short int) (CRCWord << 1);
				CRCWord = (short int) (CRCWord ^ 0x1021);
			}
			else
			{
				CRCWord = (short int) (CRCWord << 1);
			}
		}
	}

	return CRCWord;

}

void Utils::calcCRCInc16(uint8_t byte, uint16_t &prevCrc)
{
	short int Test;

	for(uint8_t j = 0; j < 8; j++)
	{
		Test = (short int) (byte & 0x00FF);
		Test = (short int) (Test << (j + 8));
		Test = Test ^ prevCrc;
		Test = (short int) (Test & 0x8000);
		if(Test)
		{
			prevCrc = (short int) (prevCrc << 1);
			prevCrc = (short int) (prevCrc ^ 0x1021);
		}
		else
		{
			prevCrc = (short int) (prevCrc << 1);
		}
	}
}

void Utils::crc32Inc(uint8_t byte, uint32_t& prevCrc)
{
	unsigned int mask;

	prevCrc = prevCrc ^ byte;
	for (int j = 7; j >= 0; j--) {    // Do eight times.
		mask = -(prevCrc & 1);
		prevCrc = (prevCrc >> 1) ^ (0xEDB88320 & mask);
	}
}

uint16_t Utils::crc16_lsb(uint8_t* pData, uint16_t length)
{
	uint8_t i;
	uint16_t data, crc;
	crc = 0xFFFF;
	if (length == 0)
		return 0;
	do
	{
		data = (uint16_t)0x00FF & *pData++;
		crc = crc ^ data;
		for (i = 8; i > 0; i--)
		{
			if (crc & 0x0001)
				crc = (crc >> 1) ^ 0x8408;
			else
				crc >>= 1;
		}
	}
	while (--length);
	crc = ~crc;
	return (crc);
}

//uint8_t Utils::scan32unumber(const unsigned char *str, uint32_t& val)
//{
//  const unsigned char *p = str;
//
//  while(*p==' ') { /* skip leading spaces */
//    p++;
//  }
//  val = 0;
//  while(*p>='0' && *p<='9') {
//    val = (uint32_t)((val)*10 + *p-'0');
//    p++;
//  } /* while */
//  return ERR_OK;
//}
//
//uint8_t Utils::scan32snumber(const unsigned char *str, int32_t& val)
//{
//  const unsigned char *p = str;
//  bool isNeg;
//  uint32_t val32u;
//  uint8_t res;
//
//  while(*p==' ') { /* skip leading spaces */
//    p++;
//  }
//  val = 0;
//  if (*p=='-') {
//    isNeg = TRUE;
//    p++; /* skip minus */
//  } else {
//    isNeg = FALSE;
//  }
//  res = Utils::scan32unumber(p, val32u);
//  if (res != ERR_OK) {
//    return res;
//  }
//  if (isNeg) {
//
//    val = (int32_t)(-(int32_t)val32u);
//  } else {
//    val = (int32_t)val32u;
//  }
//  return ERR_OK;
//}
