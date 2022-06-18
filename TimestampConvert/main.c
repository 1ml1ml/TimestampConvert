#include <stdio.h>
#include <time.h>

#include "timestampconvert.h"

int main(void)
{
	TimestampInfo timestampInfo = { 0 };
	timestampInfo.nTimestampMSec = time(0) * 1000;
	timestampInfo.nTimeZone = 8;

	//时间戳转日期
	convertTimestamp(&timestampInfo, ENUM_TIMESTAMP_TO_DATE);
	printf("%llu->%4d-%02d-%02d %02d:%02d:%02d:%03d->", timestampInfo.nTimestampMSec, timestampInfo.date.nYear, timestampInfo.date.nMonth, timestampInfo.date.nDay, timestampInfo.date.nHour, timestampInfo.date.nMinute, timestampInfo.date.nSec, timestampInfo.date.nMSec);

	//日期转时间戳
	timestampInfo.nTimestampMSec = 0;
	convertTimestamp(&timestampInfo, ENUM_DATE_TO_TIMESTAMP);
	printf("%llu", timestampInfo.nTimestampMSec);

	getchar();
	return 0;
}