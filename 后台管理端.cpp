#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6054)
#pragma warning(disable:28182)
#pragma warning(disable:6011)
#pragma warning(disable:6308)
#pragma warning(disable:28183)
#pragma warning(disable:6387)
#pragma warning(disable:26451)
#pragma warning(disable:6386)
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<��ͷ.h>
extern FILE* fp1;
extern FILE* fp2;
extern FILE* fp3;
extern FILE* fp4;
extern FILE* fp5;//Book.txt
extern FILE* fp6;//NumOfBook.txt
extern int NumOfManager;
extern int NumOfUser;
extern int NumOfBook;
void ManagerLog()//Ա����¼ע�����
{
	system("cls");
	printf("     ��ӭʹ�ú�̨����\n");
	printf("**************************\n");
	printf("***    1.��¼�����˻�  ***\n");
	printf("***    2.ע�����˻�    ***\n");
	printf("***    3.������һ��    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:login(); break;
	case 50:logon(); break;
	case 51:main();
	}
}
void BackStage()//��̨�������
{
	system("cls");
	printf(" ��ѡ������Ҫ�ķ���\n");
	printf("************************\n");
	printf("***   1.ͼ�����     ***\n");
	printf("***   2.������     ***\n");
	printf("***   3.������һ��   ***\n");
	printf("***   ��esc�˳�����  ***\n");
	printf("************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:BookOpreation(); break;
	case 50:ModifyNum(); break;
	case 51:ManagerLog();  break;
	case 27:exit(0);
	}
}
void logon()//����Ա�˻�ע��
{
	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp3);//����ļ�����
	fseek(fp3, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ��Ա�������˺�
	{
		char key[20];//���ڴ洢�ٴ����������
		system("cls");
		struct manager* manager = (struct manager*)malloc(sizeof(struct manager));
		printf("�봴��һ���˺�\n");
		scanf("%s", &manager[0].id);
		printf("��������������\n");
		scanf("%s", &manager[0].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(manager[0].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &manager[0].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(manager[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");//����NumOfManager.txt
		fprintf(fp3, "%d", NumOfManager);//��������Ա����д���ļ���
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//��������Ա�ṹ��д���ļ�
		fclose(fp1);
		free(manager);
		system("cls");
		printf("�����˻��ɹ�\n����������ص�¼����");
		_getch();
		ManagerLog();
	}
	else//����Ա�������˺�
	{
		system("cls");
		fp3 = fopen("NumOfManager.txt", "r");
		fscanf(fp3, "%d", &NumOfManager);//���ļ���ȡ������Ա����
		fclose(fp3);

		struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
		fp1 = fopen("Manager.txt", "rb");
		fread(manager, sizeof(struct manager), NumOfManager, fp1);//���ļ��ж�ȡ������Ա�ṹ��
		fclose(fp1);

		manager = (struct manager*)realloc(manager, sizeof(struct manager) * (NumOfManager + 1));
		//������Ա�ṹ������һ����λ

		char key[20];//���ڴ洢�ٴ����������
		printf("�봴��һ���˺�\n");
		scanf("%s", &manager[NumOfManager].id);
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(manager[NumOfManager].id, manager[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("�����˺ţ�����������");
					scanf("%s", &manager[NumOfManager].id);
					for (int n = 0; n < NumOfManager; n++)
					{
						if (strcmp(manager[NumOfManager].id, manager[n].id) == 0)
							break;
						if (n == NumOfManager - 1)
							flag = 0;
					}
				}
				break;
			}
		}
		printf("��������������\n");
		scanf("%s", &manager[NumOfManager].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(manager[NumOfManager].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &manager[NumOfManager].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(manager[NumOfManager].password, key) == 0)
					flag = 0;
			}
		}
		printf("�����˻��ɹ�\n����������ص�¼����");
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");
		fprintf(fp3, "%d", NumOfManager);//��������Ա����д���ļ���
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//��������Ա����д���ļ���
		fclose(fp1);
		free(manager);
		_getch();
		system("cls");
		ManagerLog();
	}
}

void login()//�˻���¼
{
	char id[20];
	char password[20];
	system("cls");
	printf("�������˺�\n");
	scanf("%s", &id);
	printf("����������\n");
	scanf("%s", &password);

	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp3);//����ļ�����
	fseek(fp3, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)
	{
		system("cls");
		printf("��������˺Ż����������������������,ESC����");
		int esc = _getch();
		if (esc == 27)
		{
			ManagerLog();
		}
		else
		{
			login();
		}
	}

	fp3 = fopen("NumOfManager.txt", "r");
	fscanf(fp3, "%d", &NumOfManager);//���ļ���ȡ������Ա����
	fclose(fp3);

	struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
	fp1 = fopen("Manager.txt", "rb");
	fread(manager, sizeof(struct manager), NumOfManager, fp1);//���ļ��ж�ȡ������Ա�ṹ��
	fclose(fp1);
	int flag = 1;
	while (flag)
	{
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(id, manager[i].id) == 0)
			{
				for (int m = 0; m < NumOfManager; m++)
				{
					if (strcmp(password, manager[m].password) == 0)
					{
						flag = 0;
						break;
					}
				}
				break;
			}
		}
		if (flag == 1)
		{
			system("cls");
			printf("��������˺Ż���������\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				ManagerLog();
			system("cls");
			printf("�������˺�\n");
			scanf("%s", &id);
			printf("����������\n");
			scanf("%s", &password);
		}
	}
	BackStage();
}

void BookOpreation()
{
	system("cls");
	printf(" ��ѡ������Ҫ�Ĳ���\n");
	printf("************************\n");
	printf("***   1.�鿴ͼ��     ***\n");
	printf("***   2.���ͼ��     ***\n");
	printf("***   3.�޸�ͼ��     ***\n");
	printf("***   4.ɾ��ͼ��     ***\n");
	printf("***   5.������һ��   ***\n");
	printf("***   ��esc�˳�����  ***\n");
	printf("************************\n");
	int key = _getch();
	switch (key)
	{
	case 49:view(); break;
	case 50:AddBook(); break;
	case 51:modify(); break;
	case 52:delet(); break;
	case 53:BackStage(); break;
	}
}

void AddBook()
{
	if ((fp6 = fopen("NumOfBook.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfBook.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfBook.txt", "rb");
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ�����ͼ��
	{
		NumOfBook = 1;
		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		book[0].no = NumOfBook;
		system("cls");
		printf("������ͼ����\n");
		scanf("%s", &book[NumOfBook - 1].BookName);
		printf("����������\n");
		scanf("%s", &book[NumOfBook - 1].writer);
		printf("�����������\n");
		scanf("%s", &book[NumOfBook - 1].press);
		printf("������ISBN\n");
		scanf("%s", &book[NumOfBook - 1].ISBN);
		printf("������۸�\n");
		scanf("%s", &book[NumOfBook - 1].price);
		printf("������ͼ�鱾��\n");
		scanf("%d", &book[NumOfBook - 1].RestOfBook);
		fp6 = fopen("NumOfBook.txt", "w");
		fprintf(fp6, "%d", NumOfBook);//��ͼ����д���ļ���
		fclose(fp6);
		fp5 = fopen("Book.txt", "wb");
		fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
		fclose(fp5);
		free(book);
		printf("�����ɣ������������\n");
		_getch();
		BookOpreation();
	}
	else//�������ͼ��
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		NumOfBook++;
		fclose(fp6);
		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);
		system("cls");
		book[NumOfBook - 1].no = NumOfBook;
		printf("������ͼ����\n");
		scanf("%s", &book[NumOfBook - 1].BookName);
		printf("����������\n");
		scanf("%s", &book[NumOfBook - 1].writer);
		printf("�����������\n");
		scanf("%s", &book[NumOfBook - 1].press);
		printf("������ISBN\n");
		scanf("%s", &book[NumOfBook - 1].ISBN);
		printf("������۸�\n");
		scanf("%s", &book[NumOfBook - 1].price);
		printf("������ͼ�鱾��\n");
		scanf("%d", &book[NumOfBook - 1].RestOfBook);

		fp6 = fopen("NumOfBook.txt", "w");
		fprintf(fp6, "%d", NumOfBook);//��ͼ����д���ļ���
		fclose(fp6);
		fp5 = fopen("Book.txt", "wb");
		fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
		fclose(fp5);
		free(book);
		printf("�����ɣ������������\n");
		_getch();
		BookOpreation();
	}
}
void view()
{
	if ((fp6 = fopen("NumOfBook.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfBook.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfBook.txt", "rb");
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���ͼ����Ϣ
	{
		system("cls");
		printf("��ǰû��ͼ����Ϣ\n�����������");
		_getch();
		BookOpreation();
	}

	else//�����ͼ����Ϣ
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);
		if (NumOfBook == 0)//ͼ����Ϊ0
		{
			system("cls");
			printf("��ǰû��ͼ����Ϣ\n�����������");
			_getch();
			BookOpreation();
		}
		else//ͼ������Ϊ0
		{
			struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
			fp5 = fopen("Book.txt", "rb");
			fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
			fclose(fp5);
			system("cls");
			for (int i = 0; i < NumOfBook; i++)
			{
				printf("NO.%d\n", book[i].no);
				printf("���ߣ�%s\n", book[i].writer);
				printf("ͼ������%s\n", book[i].BookName);
				printf("�����磺%s\n", book[i].press);
				printf("ISBN��%s\n", book[i].ISBN);
				printf("�۸�%s\n", book[i].price);
				printf("ʣ�౾����%d\n", book[i].RestOfBook);
				printf("                                                 \n");
				printf("-------------------------------------------------\n");
				printf("                                                 \n");
			}
			free(book);
			printf("�����������");
			_getch();
			BookOpreation();
		}
	}
}

void modify()
{
	if ((fp6 = fopen("NumOfBook.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfBook.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfBook.txt", "rb");
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���ͼ����Ϣ
	{
		system("cls");
		printf("��ǰû��ͼ����Ϣ\n�����������");
		_getch();
		BookOpreation();
	}

	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);
		if (NumOfBook == 0)//ͼ����Ϊ0
		{
			system("cls");
			printf("��ǰû��ͼ����Ϣ\n�����������");
			_getch();
			BookOpreation();
		}
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);

		system("cls");
		printf("��ѡ��Ҫ�޸ĵ�ͼ����");
		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfBook; i++)
		{
			if (no == book[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("û���ҵ���ͼ����Ϣ\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				BookOpreation();
			else
				modify();
		}
		else//�ҵ���Ӧͼ����Ϣ
		{
			system("cls");
			printf("NO.%d\n", book[no - 1].no);
			printf("���ߣ�%s\n", book[no - 1].writer);
			printf("ͼ������%s\n", book[no - 1].BookName);
			printf("�����磺%s\n", book[no - 1].press);
			printf("ISBN��%s\n", book[no - 1].ISBN);
			printf("�۸�%s\n", book[no - 1].price);
			printf("ʣ�౾����%d\n", book[no - 1].RestOfBook);
			printf("\n");
			printf("��ѡ��Ҫ�޸ĵ�����\n");
			printf("************************\n");
			printf("***   1.����         ***\n");
			printf("***   2.ͼ����       ***\n");
			printf("***   3.������       ***\n");
			printf("***   4.�۸�         ***\n");
			printf("***   5.ʣ�౾��       ***\n");
			printf("***   6.ISBN         ***\n");
			printf("***   7.������һ��   ***\n");
			printf("************************\n");
			int choose = _getch();
			switch (choose)
			{
			case 49:printf("����������"); scanf("%s", &book[no - 1].writer); break;
			case 50:printf("������ͼ����"); scanf("%s", &book[no - 1].BookName); break;
			case 51:printf("�����������"); scanf("%s", &book[no - 1].press); break;
			case 52:printf("������۸�"); scanf("%s", &book[no - 1].price); break;
			case 53:printf("������ʣ�౾��"); scanf("%d", &book[no - 1].RestOfBook); break;
			case 54:printf("������ISBN"); scanf("%s", &book[no - 1].ISBN); break;
			case 55:modify(); break;
			}
			fp5 = fopen("Book.txt", "wb");
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
			fclose(fp5);
			free(book);
			system("cls");
			printf("������ɣ������������");
			_getch();
			BookOpreation();
		}
	}
}

void delet()
{
	if ((fp6 = fopen("NumOfBook.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfBook.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfBook.txt", "rb");
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���ͼ����Ϣ
	{
		system("cls");
		printf("��ǰû��ͼ����Ϣ\n�����������");
		_getch();
		BookOpreation();
	}

	else//��ӹ�ͼ����Ϣ
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);

		if (NumOfBook == 0)//ͼ����Ϊ0
		{
			system("cls");
			printf("��ǰû��ͼ����Ϣ\n�����������");
			_getch();
			BookOpreation();
		}

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);

		system("cls");
		printf("��ѡ��Ҫɾ����ͼ����\n");
		for (int i = 0; i < NumOfBook; i++)
		{
			printf("NO.%d\n", book[i].no);
			printf("���ߣ�%s\n", book[i].writer);
			printf("ͼ������%s\n", book[i].BookName);
			printf("�����磺%s\n", book[i].press);
			printf("ISBN��%s\n", book[i].ISBN);
			printf("�۸�%s\n", book[i].price);
			printf("ʣ�౾����%d\n", book[i].RestOfBook);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfBook; i++)//Ѱ�Ҷ�Ӧͼ����Ϣ
		{
			if (no == book[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("û���ҵ���ͼ����Ϣ\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				BookOpreation();
			else
			{
				delet();
			}
		}
		else
		{
			system("cls");
			printf("NO.%d\n", book[no - 1].no);
			printf("���ߣ�%s\n", book[no - 1].writer);
			printf("ͼ������%s\n", book[no - 1].BookName);
			printf("�����磺%s\n", book[no - 1].press);
			printf("ISBN��%s\n", book[no - 1].ISBN);
			printf("�۸�%s\n", book[no - 1].price);
			printf("ʣ�౾����%d\n", book[no - 1].RestOfBook);
			printf("\n");
			printf("��ȷ��Ҫɾ����ͼ����Ϣ��\n");
			printf("�������ȷ�ϣ�ESCȡ��\n");
			int esc = _getch();
			if (esc == 27)
			{
				BookOpreation();
			}
			else
			{
				for (int i = no - 1; i < NumOfBook - 1; i++)
				{
					book[i] = book[i + 1];
				}
				book = (struct book*)realloc(book, sizeof(struct book) * (NumOfBook - 1));
				NumOfBook--;
				for (int i = 0; i < NumOfBook; i++)//ɾ�������±��
				{
					book[i].no = i + 1;
				}
				fp6 = fopen("NumOfBook.txt", "w");
				fprintf(fp6, "%d", NumOfBook);//��ͼ����д���ļ���
				fclose(fp6);
				fp5 = fopen("Book.txt", "wb");
				fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
				fclose(fp5);
				free(book);
				printf("ɾ����ɣ������������\n");
				_getch();
				BookOpreation();
			}
		}
	}
}
void ModifyNum()
{
	if ((fp6 = fopen("NumOfBook.txt", "r")) == NULL)
	{
		fp6 = fopen("NumOfBook.txt", "w");
		fclose(fp6);
	}
	fp6 = fopen("NumOfBook.txt", "rb");
	fseek(fp6, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp6);//����ļ�����
	fseek(fp6, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ

	if (len == 0)//δ���ͼ����Ϣ
	{
		system("cls");
		printf("��ǰû��ͼ����Ϣ\n�����������");
		_getch();
		BackStage();
	}

	else//��ӹ�ͼ����Ϣ
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);

		if (NumOfBook == 0)//ͼ����Ϊ0
		{
			system("cls");
			printf("��ǰû��ͼ����Ϣ\n�����������");
			_getch();
			BackStage();
		}

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);

		system("cls");
		for (int i = 0; i < NumOfBook; i++)
		{
			printf("NO.%d\n", book[i].no);
			printf("���ߣ�%s\n", book[i].writer);
			printf("ͼ������%s\n", book[i].BookName);
			printf("�����磺%s\n", book[i].press);
			printf("ISBN��%s\n", book[i].ISBN);
			printf("�۸�%s\n", book[i].price);
			printf("ʣ�౾����%d\n", book[i].RestOfBook);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("��ѡ��Ҫ������ͼ����\n");

		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfBook; i++)//Ѱ�Ҷ�Ӧͼ����Ϣ
		{
			if (no == book[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("û���ҵ���ͼ����Ϣ\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				BookOpreation();
			else
			{
				ModifyNum();
			}
		}
		else
		{
			printf("�������޸ĵ�ͼ����Ŀ\n");
			scanf("%d", &book[no - 1].RestOfBook);
			fp5 = fopen("Book.txt", "wb");
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
			fclose(fp5);
			free(book);
			system("cls");
			printf("������ɣ������������");
			_getch();
			BackStage();
		}
	}
}