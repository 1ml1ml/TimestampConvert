#include <stdio.h>
#include <time.h>

#include "timestampconvert.h"

#define LEAP_YEAR_DAY (366)			//���������
#define COMMON_YEAR_DAY (365)		//ƽ�������

#define START_YEAR (1970)			//ʱ����Ŀ�ʼ���

#define DAY_MSEC (86400000)			//ÿ��ĺ�����
#define HOUR_MSEC (3600000)			//ÿСʱ�ĺ�����
#define MINUTE_MSEC (60000)			//ÿ���ӵĺ�����
#define SEC_MSEC (1000)				//ÿ��ĺ�����

const static unsigned short arrCommonYearMonthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const static unsigned short arrLeapYearMonthDay[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

inline _Bool isLeapYear(unsigned nYear)
{
	return ((nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0 && nYear % 3200 != 0) || nYear % 172800 == 0) ? TRUE : FALSE;
}

inline unsigned yearToDay(unsigned nYear)
{
	return TRUE == isLeapYear(nYear) ? LEAP_YEAR_DAY : COMMON_YEAR_DAY;
}

inline unsigned long long timestampMSecToTotalDay(unsigned long long nTimestampMSec)
{
	return nTimestampMSec / DAY_MSEC + 1;
}

inline unsigned long timestampMsecToLocalMSec(unsigned long long nTimestampMSec)
{
	return nTimestampMSec % DAY_MSEC;
}

unsigned short mSecToLocalHour(unsigned nMSec)
{
	return nMSec / HOUR_MSEC;
}

inline unsigned short mSecToLocalMinute(unsigned nMSec)
{
	return nMSec % HOUR_MSEC / MINUTE_MSEC;
}

inline unsigned short mSecToLocalSec(unsigned nMSec)
{
	return nMSec % MINUTE_MSEC / SEC_MSEC;
}

inline unsigned short mSecToLocalMSec(unsigned nMSec)
{
	return nMSec % SEC_MSEC;
}

void timestampMSecToDate(unsigned long long nTimestampMSec, unsigned short* pYear, unsigned short* pMonth, unsigned short* pDay, unsigned short* pHour, unsigned short* pMinute, unsigned short* pSec, unsigned short* pMSec)
{
	long long nTotalDay = timestampMSecToTotalDay(nTimestampMSec); //��ʱ����ܵ�����

	//��ȡ���
	unsigned short nYear = START_YEAR;
	for (nTotalDay; nTotalDay > 0; nTotalDay -= yearToDay(nYear++));

	//��ݶ������һ��
	nTotalDay += yearToDay(--nYear);

	//��ȡ�·�
	unsigned short nMonth = 0;
	const unsigned short* pArr = (TRUE == isLeapYear(nYear) ? arrLeapYearMonthDay : arrCommonYearMonthDay);
	for (nMonth; nMonth < 12 && nTotalDay > 0; nTotalDay -= pArr[nMonth++]);
	
	//��ȡ����
	unsigned short nDay = nTotalDay + pArr[nMonth - 1];

	if (NULL != pYear) { *pYear = nYear; };
	if (NULL != pMonth) { *pMonth = nMonth; };
	if (NULL != pDay) { *pDay = nDay; };

	//��ȡ����ʱ��
	unsigned long nMsec = timestampMsecToLocalMSec(nTimestampMSec);		//�����Ѿ���ȥ�ĺ�����
	if (NULL != pHour){ *pHour = mSecToLocalHour(nMsec); }
	if (NULL != pMinute) { *pMinute = mSecToLocalMinute(nMsec); }
	if (NULL != pSec) { *pSec = mSecToLocalSec(nMsec); }
	if (NULL != pMSec) { *pMSec = mSecToLocalMSec(nMsec); }
}

unsigned long long dateToTimestampMSec(DateTime* pDate)
{
	if (NULL != pDate)
	{
		//��ȡ������
		unsigned long long nTotalDay = pDate->nDay - 1;
		for (unsigned short nYear = pDate->nYear - 1; nYear >= START_YEAR; nTotalDay += yearToDay(nYear--));
		const unsigned short* pArr = (TRUE == isLeapYear(pDate->nYear) ? arrLeapYearMonthDay : arrCommonYearMonthDay);
		for (unsigned short nMonth = 0; nMonth < pDate->nMonth - 1; nTotalDay += pArr[nMonth++]);

		return nTotalDay * DAY_MSEC + (unsigned long long)pDate->nHour * HOUR_MSEC + (unsigned long long)pDate->nMinute * MINUTE_MSEC + (unsigned long long)pDate->nSec * SEC_MSEC + pDate->nMSec;
	}
	return 0;
}

void convertTimestamp(TimestampInfo* pTimestamp, ConvertType type)
{
	if (NULL != pTimestamp )
	{
		//����ʱ������ʱ���
		unsigned long long nCorrectTimeMSec = (unsigned long long)pTimestamp->nTimeZone * HOUR_MSEC;
		switch (type)
		{
		case ENUM_TIMESTAMP_TO_DATE:
			timestampMSecToDate(pTimestamp->nTimestampMSec + nCorrectTimeMSec, &pTimestamp->dateTime.nYear, &pTimestamp->dateTime.nMonth, &pTimestamp->dateTime.nDay, &pTimestamp->dateTime.nHour, &pTimestamp->dateTime.nMinute, &pTimestamp->dateTime.nSec, &pTimestamp->dateTime.nMSec);
			break;
		case ENUM_DATE_TO_TIMESTAMP:
			pTimestamp->nTimestampMSec = dateToTimestampMSec(&pTimestamp->dateTime) - nCorrectTimeMSec;
			break;
		}
	}
}
