#pragma once

class CLunar
{
public:
	CLunar(void);
	~CLunar(void);


	void LunarCalendar(COleDateTime tmMeas);//����ũ�����ڡ�

public:
	//ũ��
	int m_lYear; //��Ԫ��4λ����
	int m_lMonth; //ũ��������
	int m_lDay; //ũ��������
	CString m_cYearName; //��ż����ʾ
	CString m_cWordDay; //���ֱ�ʾ����
	CString m_cWordMonth;//���ֱ�ʾ����
	CString m_cMonthSB; //�´�(30) С(29)��
	BOOL m_isLeap; //�Ƿ�Ϊũ������?

	//����
	CString m_cYear; //����, 2������
	CString m_cMonth; //����, 2������
	CString m_cDay; //����, 2������
	CString m_cAnimal; //�������� 

	//����
	CString m_lunarFestival; //ũ������
	CString m_solarFestival; //��������
	CString m_solarTerms; //����

	BOOL m_bStrong; //ǿ���Ľ��� �ż���

private:	
	static int getYearDays(int y);//����ũ�� y���������	
	static int getLeapDays(int y);//����ũ�� y�����µ�����	
	static int getLeapMonth(int y);//����ũ�� y�����ĸ��� 1-12 , û�򷵻� 0	
	static int getMonthDays(int y,int m);//����ũ�� y��m�µ�������	
	static int getSTerm(int y,int n);//ĳ��ĵ�n������Ϊ����(��0С������)	
	static CString getWordDay(int d);//�õ�ũ���������	
	static CString getYearName(int y);//�õ���ż��� ����	
	static CString getGZ(LONGLONG num);//�õ���֧����	
	static void parseFtv(CString strInfo,int& nFirst,int& nLast,CString& strDesc,BOOL& bStrong);//�ӽ����ַ�����������֣�������*
	static int getWeekOfMonth(int y,int m,int d);//�õ�����Ϊ���µĵڼ���	
	static LONGLONG getUTC(int nYear, int nMonth, int nDay, int nHour=0, int nMin=0, int nSec=0);//����ָ������� UTCʱ������ 100ns ��
	void Init();//

	//�����������ڣ��������ڼ�(1=Sun, 2=Mon, ..., 7=Sa)
	//int getDayOfWeek(myDATETIME DayWk);


public:	
	static int getWeeksOfMonth(int y,int m);//�õ������м���	
	static int getSunMonthDays(int y,int m);//�õ�����������

	static CString getWordMonth(int m)//�õ�����������
	{
		ASSERT(m>0 && m<=12);
		return m_nStr1[m];
	};

	static CString getEnWordMonth(int m)//�õ�Ӣ��������
	{
		ASSERT(m>0 && m<=12);
		return m_monthName[m-1];
	};

private:
	/************************************************************************/
	/*                      ũ[��]����ʹ�õ�ȫ�ֳ���                        */
	/************************************************************************/
	// ��������
	static const int m_lunarInfo[]; //ũ������
	static const CString m_TIANGAN[]; //���
	static const CString m_DIZHI[]; //��֧
	static const CString m_Animals[]; //��Ф
	static const CString m_nStr1[]; //���ֵ���������
	static const CString m_nStr2[]; //���ֵ���������
	//	static const CString m_cMonName[];//���ֵ���������(��)

	//ũ������
	static const CString m_lFtv[];

	/************************************************************************/
	/*                         ��[��]����ʹ�õ�ȫ�ֳ���                     */
	/************************************************************************/ 
	static const int m_solarMonth[]; //�µ�����
	static const CString m_solarTerm[]; //��������������
	static const int m_sTermInfo[]; //������������Ϣ
	static const CString m_monthName[]; //�µ�Ӣ������

	//�������� *��ʾ�ż���
	static const CString m_sFtv[];
	//ĳ�µĵڼ������ڼ��� 5,6,7,8 ��ʾ������ 1,2,3,4 �����ڼ�
	static const CString m_wFtv[];

	//���ʱ��
	COleDateTime m_tmMeas; //�������
};
