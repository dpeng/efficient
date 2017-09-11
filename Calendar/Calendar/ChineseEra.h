#ifndef _CHINESE_ERA_H_
#define _CHINESE_ERA_H_
/*

�������ƣ�int GetChineseEra(int year,int flag)

��������: ����ĳ���Ӧ����ɺ͵�֧��

flag = 0 ������� flag = 1 ���� ��֧��

����������year Ҫ��ѯ���ꣻ�磺1984�꣬

��ɣ�GetChineseEra(1984,0) 

��֧��GetChineseEra(1984,1)

*/

int GetLunarYear(int year,int month,int day)

{

	int Spring_NY,Sun_NY;


	//Spring_NY ��¼�����뵱��Ԫ����������

	//Sun_NY ��¼�������뵱��Ԫ����������

	if( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)



		Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;

	else

		Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;



	Sun_NY = MonthAdd[month-1] + day - 1;



	if( (!(year % 4)) && (month > 2))



		Sun_NY++;



	if(Sun_NY >= Spring_NY)

		return year;

	else

		return year - 1;

}

int GetChineseEra(int year,int flag)

{

	if(flag == 0)

		return ((year - 4) % 60) % 10;

	else

		return ((year - 4) % 60) % 12;

}


#endif