// MyClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "MyProperty.h"
#include "MyTemplate.h"
#include "MyStack.h"
void TestStack();
int _tmain(int argc, _TCHAR* argv[])
{
	//CMyProperty m_test;
	//cout<<"����ǰ��"<<m_test.__getpara()<<endl;
	//cout<<"������һ�����õĲ�����"<<endl;
	//int tmpPara = 0;
	//cin>>tmpPara;
	//m_test.__putpara(tmpPara);
	//cout<<"���ú�"<<m_test.__getpara()<<endl;


	//double adb = MAX(4.0, 4.00999);
	TestStack();
	system("pause");
	return 0;
}

void TestStack()
{
	SqStack TmStack;
	CMyStack Stack;
	Stack.InitStack(TmStack);
	int Nr_10 = 0;
	printf("������һ��ʮ����������");
	scanf("%d", &Nr_10);

	//ʮ����ת�ɰ˽���
	int tmp = Nr_10;
	while(tmp)
	{
		Stack.Push(TmStack, tmp%8);
		tmp = tmp/8;
	}
	int Des = 0;
	printf("\n�˽�����Ϊ��");
	while(!Stack.StackEmpty(TmStack))
	{
		Stack.Pop(TmStack, Des);
		printf("%d", Des);
	}

	//ת���ɶ�����
	tmp = Nr_10;
	while(tmp)
	{
		Stack.Push(TmStack, tmp%2);
		tmp = tmp/2;
	}
	Des = 0;
	printf("\n��������Ϊ��");
	while(!Stack.StackEmpty(TmStack))
	{
		Stack.Pop(TmStack, Des);
		printf("%d", Des);
	}


	//ת����16����
	tmp = Nr_10;
	while(tmp)
	{
		Stack.Push(TmStack, tmp%16);
		tmp = tmp/16;
	}
	Des = 0;
	printf("\n16������Ϊ��");
	while(!Stack.StackEmpty(TmStack))
	{
		Stack.Pop(TmStack, Des);
		printf("%x", Des);
	}
}