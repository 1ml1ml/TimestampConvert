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
	unsigned short nYear;		//��
	unsigned short nMonth;		//��
	unsigned short nDay;		//��
	unsigned short nHour;		//ʱ
	unsigned short nMinute;		//��
	unsigned short nSec;		//��
	unsigned short nMSec;		//����
}Date;

typedef struct TimestampInfo
{
	unsigned long long nTimestampMSec;	//ʱ���
	unsigned short nTimeZone;			//ʱ��
	Date date;							//������Ϣ
}TimestampInfo;

//�ж��Ƿ�������
//����:nYear ���
//���:��
//����:_Bool 0��ʾ��, 1��ʾ��
inline _Bool isLeapYear(unsigned nYear);

//��ȡĳһ�������
//����:nYear ���
//���:��
//����:unsigned ����
inline unsigned yearToDay(unsigned nYear);

//ʱ���ת����������
//����:nTimestampMSec ʱ��� ����
//���:��
//����:unsigned long long ����
inline unsigned long long timestampMSecToTotalDay(unsigned long long nTimestampMSec);

//ʱ���ת���ɵ������
//����:nTimestampMSec ʱ��� ����
//���:��
//���� unsigned long ����
inline unsigned long timestampMsecToLocalMSec(unsigned long long nTimestampMSec);

//����ת����Сʱ
//����:nMSec ��ǰ�����ĺ�����
//���:��
//����:unsigned short Сʱ
inline unsigned short mSecToLocalHour(unsigned nMSec);

//����ת���ط�
//����:nMSec ��ǰ�����ĺ�����
//���:��
//����:unsigned short Сʱ
inline unsigned short mSecToLocalMinute(unsigned nMSec);

//����ת������
//����:nMSec ��ǰ�����ĺ�����
//���:��
//����:unsigned short Сʱ
inline unsigned short mSecToLocalSec(unsigned nMSec);

//����ת���غ���
//����:nMSec ��ǰ�����ĺ�����
//���:��
//����:unsigned short Сʱ
inline unsigned short mSecToLocalMSec(unsigned nMSec);

//ʱ���ת��������
//����:nTimestampMSec ʱ��� ����
//���:pYear ��, pMonth ��, pDay ��, pHour Сʱ, pMinute ��, pSec ��, pMSec ����
//����:void
void timestampMSecToDate(unsigned long long nTimestampMSec, unsigned short* pYear, unsigned short* pMonth, unsigned short* pDay, unsigned short* pHour, unsigned short* pMinute, unsigned short* pSec, unsigned short* pMSec);

//����תʱ���
//����:pDate ����
//���:��
//����:unsigned long long ʱ��� ����
unsigned long long dateToTimestampMSec(Date* pDate);

//ʱ���ת����������Ϣ
//����;Timestamp, type ת������
//���:Timestamp
//����:void
void convertTimestamp(TimestampInfo *pTimestamp, ConvertType type);

#endif
