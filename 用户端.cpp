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
int IdOfUser;
extern FILE* fp2;
extern FILE* fp2;
extern FILE* fp4;
extern FILE* fp4;
extern FILE* fp5;//Book.txt
extern FILE* fp6;//NumOfBook.txt
extern int NumOfManager;
extern int NumOfUser;
extern int NumOfBook;
void BookingMenu()
{
	system("cls");
	printf(" ��ѡ������Ҫ�ķ���\n");
	printf("*************************\n");
	printf("***   1.ͼ���ѯ      ***\n");
	printf("***   2.�鿴�ҵ�ͼ��  ***\n");
	printf("***   3.����ͼ��    ***\n");
	printf("***   4.����ͼ��    ***\n");
	printf("***   5.������һ��    ***\n");
	printf("***   ��esc�˳�����   ***\n");
	printf("*************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:UserView(); break;
	case 50:ViewMine(); break;
	case 51:LendBook();  break;
	case 52:ReturnBook(); break;
	case 53:main(); break;
	case 27:exit(0);
	}
}
void UserLog()
{
	system("cls");
	printf("   ��ӭʹ��ͼ�����ϵͳ\n");
	printf("**************************\n");
	printf("***    1.��¼�����˻�  ***\n");
	printf("***    2.ע�����˻�    ***\n");
	printf("***    3.������һ��    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:UserLogin(); break;
	case 50:UserLogon(); break;
	case 51:main();
	}
}

void UserLogon()
{
	if ((fp4 = fopen("NumOfUser.txt", "r")) == NULL)
	{
		fp4 = fopen("NumOfUser.txt", "w");
		fclose(fp4);
	}
	fp4 = fopen("NumOfUser.txt", "rb");
	fseek(fp4, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp4);//����ļ�����
	fseek(fp4, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)//��һ���û������˺�
	{
		char key[20];//���ڴ洢�ٴ����������
		system("cls");
		struct user* user = (struct user*)malloc(sizeof(struct user));
		printf("�봴��һ���˺�\n");
		scanf("%s", &user[0].id);
		printf("��������������\n");
		scanf("%s", &user[0].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(user[0].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &user[0].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(user[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfUser++;
		user[0].NumOfBook = 0;
		fp4 = fopen("NumOfUser.txt", "w");//����NumOfUser.txt
		fprintf(fp4, "%d", NumOfUser);//���û�����д���ļ���
		fclose(fp4);
		fp2 = fopen("User.txt", "wb");
		fwrite(user, sizeof(struct user), NumOfUser, fp2);//���û��ṹ��д���ļ�
		fclose(fp2);
		free(user);
		system("cls");
		printf("�����˻��ɹ�\n����������ص�¼����");
		_getch();
		UserLog();
	}
	else//�����û������˺�
	{
		system("cls");
		fp4 = fopen("NumOfUser.txt", "r");
		fscanf(fp4, "%d", &NumOfUser);//���ļ���ȡ�û�����
		fclose(fp4);

		struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
		fp2 = fopen("User.txt", "rb");
		fread(user, sizeof(struct user), NumOfUser, fp2);//���ļ��ж�ȡ�û��ṹ��
		fclose(fp2);

		user = (struct user*)realloc(user, sizeof(struct user) * (NumOfUser + 1));
		//�û��ṹ������һ����λ

		char key[20];//���ڴ洢�ٴ����������
		printf("�봴��һ���˺�\n");
		scanf("%s", &user[NumOfUser].id);
		for (int i = 0; i < NumOfUser; i++)
		{
			if (strcmp(user[NumOfUser].id, user[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("�����˺ţ�����������");
					scanf("%s", &user[NumOfUser].id);
					for (int n = 0; n < NumOfUser; n++)
					{
						if (strcmp(user[NumOfUser].id, user[n].id) == 0)
							break;
						if (n == NumOfUser - 1)
							flag = 0;
					}
				}
				break;
			}
		}
		printf("��������������\n");
		scanf("%s", &user[NumOfUser].password);
		printf("��ȷ����������\n");
		scanf("%s", &key);
		if (strcmp(user[NumOfUser].password, key) != 0)//�����������������Ƿ���ͬ
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("��������������벻ͬ����������������\n");
				scanf("%s", &user[NumOfUser].password);
				printf("��ȷ����������");
				scanf("%s", key);
				if (strcmp(user[NumOfUser].password, key) == 0)
					flag = 0;
			}
		}
		printf("�����˻��ɹ�\n����������ص�¼����");
		user[NumOfUser].NumOfBook = 0;
		NumOfUser++;
		fp4 = fopen("NumOfUser.txt", "w");
		fprintf(fp4, "%d", NumOfUser);//���û�����д���ļ���
		fclose(fp4);
		fp2 = fopen("User.txt", "wb");
		fwrite(user, sizeof(struct user), NumOfUser, fp2);//������д���û��ļ���
		fclose(fp2);
		free(user);
		_getch();
		system("cls");
		UserLog();
	}
}
void UserLogin()//�˻���¼
{
	char id[20];
	char password[20];
	system("cls");
	printf("�������˺�\n");
	scanf("%s", &id);
	printf("����������\n");
	scanf("%s", &password);

	if ((fp4 = fopen("NumOfUser.txt", "r")) == NULL)
	{
		fp4 = fopen("NumOfUser.txt", "w");
		fclose(fp4);
	}
	fp4 = fopen("NumOfUser.txt", "rb");
	fseek(fp4, 0, SEEK_END);//���ļ�ָ���Ƶ��ļ�ĩβ
	int len = ftell(fp4);//����ļ�����
	fseek(fp4, 0, SEEK_SET);//���ļ�ָ���Ƶ��ļ���ͷ
	if (len == 0)
	{
		system("cls");
		printf("��������˺Ż����������������������,ESC����");
		int esc = _getch();
		if (esc == 27)
		{
			UserLog();
		}
		else
		{
			UserLogin();
		}
	}

	fp4 = fopen("NumOfUser.txt", "r");
	fscanf(fp4, "%d", &NumOfUser);//���ļ���ȡ�û�����
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//���ļ��ж�ȡ�û��ṹ��
	fclose(fp2);
	int flag = 1;
	while (flag)
	{
		for (int i = 0; i < NumOfUser; i++)
		{
			if (strcmp(id, user[i].id) == 0)
			{
				for (int m = 0; m < NumOfUser; m++)
				{
					if (strcmp(password, user[m].password) == 0)
					{
						flag = 0;
						IdOfUser = m;
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
				UserLog();
			system("cls");
			printf("�������˺�\n");
			scanf("%s", &id);
			printf("����������\n");
			scanf("%s", &password);
		}
	}
	BookingMenu();
}
void UserView()
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
		BookingMenu();
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
			BookingMenu();
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
			printf("�����������");
			_getch();
			BookingMenu();
		}
	}
}
void LendBook()
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
		printf("��ǰû�пɽ��ĵ�ͼ��\n�����������");
		_getch();
		BookingMenu();
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
		printf("��ѡ��Ҫ���ĵ�ͼ����\n");
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
				BookingMenu();
			else
			{
				LendBook();
			}
		}
		else
		{
			system("cls");
			printf("��ȷ��Ҫ���ĸ�ͼ��ͼ����\n");
			printf("NO.%d\n", book[no - 1].no);
			printf("ͼ������%s\n", book[no - 1].BookName);
			printf("���ߣ�%s\n", book[no - 1].writer);
			printf("�����磺%s\n", book[no - 1].press);
			printf("�۸�%s\n", book[no - 1].price);
			printf("ISBN��%s\n", book[no - 1].ISBN);
			printf("\n");
			if (book[no - 1].RestOfBook <= 0)
			{
				system("cls");
				printf("�Բ��𣬸�ͼ���ѱ�������\n");
				printf("�����������");
				_getch();
				BookingMenu();
			}
			printf("�������ȷ�ϣ�ESCȡ��\n");
			int esc = _getch();
			if (esc == 27)
			{
				BookingMenu();
			}
			else
			{
				fp4 = fopen("NumOfUser.txt", "r");
				fscanf(fp4, "%d", &NumOfUser);//���ļ���ȡ�û�����
				fclose(fp4);

				struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
				fp2 = fopen("User.txt", "rb");
				fread(user, sizeof(struct user), NumOfUser, fp2);//���ļ��ж�ȡ�û��ṹ��
				fclose(fp2);
				user[IdOfUser].NoOfBook[user[IdOfUser].NumOfBook] = book[no - 1].no;//��ͼ����д���û���Ϣ��
				user[IdOfUser].NumOfBook++;
				book[no - 1].RestOfBook--;
				fp5 = fopen("Book.txt", "wb");
				fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
				fclose(fp5);
				free(book);
				fp2 = fopen("User.txt", "wb");
				fwrite(user, sizeof(struct user), NumOfUser, fp2);//���û��ṹ��д���ļ�
				fclose(fp2);
				free(user);
				printf("�����ɣ������������");
				BookingMenu();
			}

		}
	}
}
void ViewMine()
{
	fp4 = fopen("NumOfUser.txt", "r");
	fscanf(fp4, "%d", &NumOfUser);//���ļ���ȡ�û�����
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//���ļ��ж�ȡ�û��ṹ��
	fclose(fp2);

	if (user[IdOfUser].NumOfBook == 0)
	{
		system("cls");
		printf("��δ��ѯ������ͼ�������Ϣ\n");
		printf("�����������");
		_getch();
		free(user);
		BookingMenu();
	}
	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);

		system("cls");
		printf("����%d�����ĵ�ͼ��\n", user[IdOfUser].NumOfBook);
		for (int i = 0; i < user[IdOfUser].NumOfBook; i++)
		{
			printf("NO.%d\n", book[user[IdOfUser].NoOfBook[i] - 1].no);
			printf("���ߣ�%s\n", book[user[IdOfUser].NoOfBook[i] - 1].writer);
			printf("ͼ������%s\n", book[user[IdOfUser].NoOfBook[i] - 1].BookName);
			printf("�����磺%s\n", book[user[IdOfUser].NoOfBook[i] - 1].press);
			printf("ISBN��%s\n", book[user[IdOfUser].NoOfBook[i] - 1].ISBN);
			printf("�۸�%s\n", book[user[IdOfUser].NoOfBook[i] - 1].price);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("�����������");
		free(book);
		free(user);
		_getch();
		BookingMenu();
	}
}

void ReturnBook()
{
	fp4 = fopen("NumOfUser.txt", "r");
	fscanf(fp4, "%d", &NumOfUser);//���ļ���ȡ�û�����
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//���ļ��ж�ȡ�û��ṹ��
	fclose(fp2);

	if (user[IdOfUser].NumOfBook == 0)
	{
		system("cls");
		printf("��δ��ѯ������ͼ�������Ϣ\n");
		printf("�����������");
		free(user);
		_getch();
		BookingMenu();
	}
	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//���ļ���ȡͼ����
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//���ļ��ж�ȡͼ��ṹ��
		fclose(fp5);

		system("cls");
		for (int i = 0; i < user[IdOfUser].NumOfBook; i++)
		{
			printf("NO.%d\n", book[user[IdOfUser].NoOfBook[i] - 1].no);
			printf("���ߣ�%s\n", book[user[IdOfUser].NoOfBook[i] - 1].writer);
			printf("ͼ������%s\n", book[user[IdOfUser].NoOfBook[i] - 1].BookName);
			printf("�����磺%s\n", book[user[IdOfUser].NoOfBook[i] - 1].press);
			printf("ISBN��%s\n", book[user[IdOfUser].NoOfBook[i] - 1].ISBN);
			printf("�۸�%s\n", book[user[IdOfUser].NoOfBook[i] - 1].price);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("��ѡ��Ҫ�����ͼ����");
		int no;
		int index;//����ͼ���Ŵ�����NoOfBook�е�λ��
		scanf("%d", &no);
		int flag = 0;
		for (int i = 0; i < user[IdOfUser].NumOfBook; i++)
		{
			if (user[IdOfUser].NoOfBook[i] == no)
			{
				flag = 1;
				index = i;
				break;
			}
		}
		if (flag == 0)
		{
			system("cls");
			printf("�Բ�����û�н��ĸ�ͼ��\n");
			printf("��������������룬��ESC����");
			int esc = _getch();
			if (esc == 27)
				BookingMenu();
			else
				ReturnBook();
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
			printf("\n");
			printf("��ȷ��Ҫ����ͼ�������Ϣ��\n");
			printf("�������ȷ������ESCȡ��\n");
			int esc = _getch();
			if (esc == 27)
				BookingMenu();
			else
			{
				for (int i = index; i < user[IdOfUser].NumOfBook - 1; i++)
				{
					user[IdOfUser].NoOfBook[i] = user[IdOfUser].NoOfBook[i + 1];
				}
				user[IdOfUser].NumOfBook--;
				book[no - 1].RestOfBook++;
			}
			fp5 = fopen("Book.txt", "wb");
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//��ͼ��ṹ��д���ļ�
			fclose(fp5);
			free(book);
			fp2 = fopen("User.txt", "wb");
			fwrite(user, sizeof(struct user), NumOfUser, fp2);//���û��ṹ��д���ļ�
			fclose(fp2);
			free(user);
			printf("ɾ���ɹ��������������");
			_getch();
			BookingMenu();
		}
	}
}
