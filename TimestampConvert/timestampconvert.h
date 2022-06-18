#ifndef __TIMESTAMPCONVERT__TMJ__2022_3_1
#define __TIMESTAMPCONVERT__TMJ__2022_3_1

#define FALSE 0
#define TRUE 1

typedef enum ConvertType
{
	ENUM_TIMESTAMP_TO_DATE = 0,
	ENUM_DATE_TO_TIMESTAMP
}ConvertType;

typedef struct Date
{
	unsigned short nYear;		//年
	unsigned short nMonth;		//月
	unsigned short nDay;		//日
	unsigned short nHour;		//时
	unsigned short nMinute;		//分
	unsigned short nSec;		//秒
	unsigned short nMSec;		//毫秒
}Date;

typedef struct TimestampInfo
{
	unsigned long long nTimestampMSec;	//时间戳
	unsigned short nTimeZone;			//时区
	Date date;							//日期信息
}TimestampInfo;

//判断是否是闰年
//输入:nYear 年份
//输出:无
//返回:_Bool 0表示假, 1表示真
inline _Bool isLeapYear(unsigned nYear);

//获取某一年的天数
//输入:nYear 年份
//输出:无
//返回:unsigned 天数
inline unsigned yearToDay(unsigned nYear);

//时间戳转换成总天数
//输入:nTimestampMSec 时间戳 毫秒
//输出:无
//返回:unsigned long long 天数
inline unsigned long long timestampMSecToTotalDay(unsigned long long nTimestampMSec);

//时间戳转换成当天毫秒
//输入:nTimestampMSec 时间戳 毫秒
//输出:无
//返回 unsigned long 毫秒
inline unsigned long timestampMsecToLocalMSec(unsigned long long nTimestampMSec);

//毫秒转本地小时
//输入:nMSec 当前经过的毫秒数
//输出:无
//返回:unsigned short 小时
inline unsigned short mSecToLocalHour(unsigned nMSec);

//毫秒转本地分
//输入:nMSec 当前经过的毫秒数
//输出:无
//返回:unsigned short 小时
inline unsigned short mSecToLocalMinute(unsigned nMSec);

//毫秒转本地秒
//输入:nMSec 当前经过的毫秒数
//输出:无
//返回:unsigned short 小时
inline unsigned short mSecToLocalSec(unsigned nMSec);

//毫秒转本地毫秒
//输入:nMSec 当前经过的毫秒数
//输出:无
//返回:unsigned short 小时
inline unsigned short mSecToLocalMSec(unsigned nMSec);

//时间戳转换成日期
//输入:nTimestampMSec 时间戳 毫秒
//输出:pYear 年, pMonth 月, pDay 日, pHour 小时, pMinute 分, pSec 秒, pMSec 毫秒
//返回:void
void timestampMSecToDate(unsigned long long nTimestampMSec, unsigned short* pYear, unsigned short* pMonth, unsigned short* pDay, unsigned short* pHour, unsigned short* pMinute, unsigned short* pSec, unsigned short* pMSec);

//日期转时间戳
//输入:pDate 日期
//输出:无
//返回:unsigned long long 时间戳 毫秒
unsigned long long dateToTimestampMSec(Date* pDate);

//时间戳转换成日期信息
//输入;Timestamp, type 转换类型
//输出:Timestamp
//返回:void
void convertTimestamp(TimestampInfo *pTimestamp, ConvertType type);

#endif
