#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<��ͷ.h>
int NumOfManager;
int NumOfUser;
int NumOfBook;
FILE* fp1;//Manager.txt
FILE* fp2;//User.txt
FILE* fp3;//NumOfManager.txt
FILE* fp4;//NumOfUser.txt
FILE* fp5;//Book.txt
FILE* fp6;//NumOfBook.txt
FILE* fp7;
int main()
{
	system("cls");
	printf("��ѡ������Ҫ�ķ���\n");
	printf("***********************\n");
	printf("***   1.�û���¼    ***\n");
	printf("***   2.����Ա��¼  ***\n");
	printf("***    ��esc�˳�    ***\n");
	printf("***********************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:UserLog(); break;
	case 50:ManagerLog(); break;
	case 27:exit(0);
	}
}