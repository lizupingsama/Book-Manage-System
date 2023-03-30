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
#include<标头.h>
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
	printf(" 请选择您需要的服务\n");
	printf("*************************\n");
	printf("***   1.图书查询      ***\n");
	printf("***   2.查看我的图书  ***\n");
	printf("***   3.借阅图书    ***\n");
	printf("***   4.还借图书    ***\n");
	printf("***   5.返回上一级    ***\n");
	printf("***   按esc退出程序   ***\n");
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
	printf("   欢迎使用图书管理系统\n");
	printf("**************************\n");
	printf("***    1.登录已有账户  ***\n");
	printf("***    2.注册新账户    ***\n");
	printf("***    3.返回上一级    ***\n");
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
	fseek(fp4, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp4);//检查文件长度
	fseek(fp4, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)//第一个用户创建账号
	{
		char key[20];//用于存储再次输入的密码
		system("cls");
		struct user* user = (struct user*)malloc(sizeof(struct user));
		printf("请创建一个账号\n");
		scanf("%s", &user[0].id);
		printf("请输入您的密码\n");
		scanf("%s", &user[0].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(user[0].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &user[0].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(user[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfUser++;
		user[0].NumOfBook = 0;
		fp4 = fopen("NumOfUser.txt", "w");//创建NumOfUser.txt
		fprintf(fp4, "%d", NumOfUser);//将用户人数写入文件中
		fclose(fp4);
		fp2 = fopen("User.txt", "wb");
		fwrite(user, sizeof(struct user), NumOfUser, fp2);//将用户结构体写入文件
		fclose(fp2);
		free(user);
		system("cls");
		printf("创建账户成功\n按任意键返回登录界面");
		_getch();
		UserLog();
	}
	else//后续用户创建账号
	{
		system("cls");
		fp4 = fopen("NumOfUser.txt", "r");
		fscanf(fp4, "%d", &NumOfUser);//从文件读取用户人数
		fclose(fp4);

		struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
		fp2 = fopen("User.txt", "rb");
		fread(user, sizeof(struct user), NumOfUser, fp2);//从文件中读取用户结构体
		fclose(fp2);

		user = (struct user*)realloc(user, sizeof(struct user) * (NumOfUser + 1));
		//用户结构体扩容一个单位

		char key[20];//用于存储再次输入的密码
		printf("请创建一个账号\n");
		scanf("%s", &user[NumOfUser].id);
		for (int i = 0; i < NumOfUser; i++)
		{
			if (strcmp(user[NumOfUser].id, user[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("已有账号，请重新输入");
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
		printf("请输入您的密码\n");
		scanf("%s", &user[NumOfUser].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(user[NumOfUser].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &user[NumOfUser].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(user[NumOfUser].password, key) == 0)
					flag = 0;
			}
		}
		printf("创建账户成功\n按任意键返回登录界面");
		user[NumOfUser].NumOfBook = 0;
		NumOfUser++;
		fp4 = fopen("NumOfUser.txt", "w");
		fprintf(fp4, "%d", NumOfUser);//将用户人数写入文件中
		fclose(fp4);
		fp2 = fopen("User.txt", "wb");
		fwrite(user, sizeof(struct user), NumOfUser, fp2);//将人数写入用户文件中
		fclose(fp2);
		free(user);
		_getch();
		system("cls");
		UserLog();
	}
}
void UserLogin()//账户登录
{
	char id[20];
	char password[20];
	system("cls");
	printf("请输入账号\n");
	scanf("%s", &id);
	printf("请输入密码\n");
	scanf("%s", &password);

	if ((fp4 = fopen("NumOfUser.txt", "r")) == NULL)
	{
		fp4 = fopen("NumOfUser.txt", "w");
		fclose(fp4);
	}
	fp4 = fopen("NumOfUser.txt", "rb");
	fseek(fp4, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp4);//检查文件长度
	fseek(fp4, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)
	{
		system("cls");
		printf("您输入的账号或密码有误按任意键重新输入,ESC返回");
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
	fscanf(fp4, "%d", &NumOfUser);//从文件读取用户人数
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//从文件中读取用户结构体
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
			printf("您输入的账号或密码有误\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				UserLog();
			system("cls");
			printf("请输入账号\n");
			scanf("%s", &id);
			printf("请输入密码\n");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有图书信息\n按任意键返回");
		_getch();
		BookingMenu();
	}

	else//已添加图书信息
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);
		if (NumOfBook == 0)//图书数为0
		{
			system("cls");
			printf("当前没有图书信息\n按任意键返回");
			_getch();
			BookingMenu();
		}
		else//图书数不为0
		{
			struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
			fp5 = fopen("Book.txt", "rb");
			fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
			fclose(fp5);
			system("cls");
			for (int i = 0; i < NumOfBook; i++)
			{
				printf("NO.%d\n", book[i].no);
				printf("作者：%s\n", book[i].writer);
				printf("图书名：%s\n", book[i].BookName);
				printf("出版社：%s\n", book[i].press);
				printf("ISBN：%s\n", book[i].ISBN);
				printf("价格：%s\n", book[i].price);
				printf("剩余本数：%d\n", book[i].RestOfBook);
				printf("                                                 \n");
				printf("-------------------------------------------------\n");
				printf("                                                 \n");
			}
			printf("按任意键返回");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有可借阅的图书\n按任意键返回");
		_getch();
		BookingMenu();
	}

	else//添加过图书信息
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);

		if (NumOfBook == 0)//图书数为0
		{
			system("cls");
			printf("当前没有图书信息\n按任意键返回");
			_getch();
			BackStage();
		}

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);

		system("cls");
		for (int i = 0; i < NumOfBook; i++)
		{
			printf("NO.%d\n", book[i].no);
			printf("作者：%s\n", book[i].writer);
			printf("图书名：%s\n", book[i].BookName);
			printf("出版社：%s\n", book[i].press);
			printf("ISBN：%s\n", book[i].ISBN);
			printf("价格：%s\n", book[i].price);
			printf("剩余本数：%d\n", book[i].RestOfBook);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("请选择要借阅的图书编号\n");
		int no;
		scanf("%d", &no);
		int flag = 1;

		for (int i = 0; i < NumOfBook; i++)//寻找对应图书信息
		{
			if (no == book[i].no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			printf("没有找到该图书信息\n");
			printf("按任意键重新输入，按ESC返回");
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
			printf("您确定要借阅该图书图书吗？\n");
			printf("NO.%d\n", book[no - 1].no);
			printf("图书名：%s\n", book[no - 1].BookName);
			printf("作者：%s\n", book[no - 1].writer);
			printf("出版社：%s\n", book[no - 1].press);
			printf("价格：%s\n", book[no - 1].price);
			printf("ISBN：%s\n", book[no - 1].ISBN);
			printf("\n");
			if (book[no - 1].RestOfBook <= 0)
			{
				system("cls");
				printf("对不起，该图书已被借阅完\n");
				printf("按任意键返回");
				_getch();
				BookingMenu();
			}
			printf("按任意键确认，ESC取消\n");
			int esc = _getch();
			if (esc == 27)
			{
				BookingMenu();
			}
			else
			{
				fp4 = fopen("NumOfUser.txt", "r");
				fscanf(fp4, "%d", &NumOfUser);//从文件读取用户人数
				fclose(fp4);

				struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
				fp2 = fopen("User.txt", "rb");
				fread(user, sizeof(struct user), NumOfUser, fp2);//从文件中读取用户结构体
				fclose(fp2);
				user[IdOfUser].NoOfBook[user[IdOfUser].NumOfBook] = book[no - 1].no;//将图书编号写入用户信息中
				user[IdOfUser].NumOfBook++;
				book[no - 1].RestOfBook--;
				fp5 = fopen("Book.txt", "wb");
				fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
				fclose(fp5);
				free(book);
				fp2 = fopen("User.txt", "wb");
				fwrite(user, sizeof(struct user), NumOfUser, fp2);//将用户结构体写入文件
				fclose(fp2);
				free(user);
				printf("添加完成，按任意键返回");
				BookingMenu();
			}

		}
	}
}
void ViewMine()
{
	fp4 = fopen("NumOfUser.txt", "r");
	fscanf(fp4, "%d", &NumOfUser);//从文件读取用户人数
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//从文件中读取用户结构体
	fclose(fp2);

	if (user[IdOfUser].NumOfBook == 0)
	{
		system("cls");
		printf("暂未查询到您的图书借阅信息\n");
		printf("按任意键返回");
		_getch();
		free(user);
		BookingMenu();
	}
	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);

		system("cls");
		printf("您有%d本借阅的图书\n", user[IdOfUser].NumOfBook);
		for (int i = 0; i < user[IdOfUser].NumOfBook; i++)
		{
			printf("NO.%d\n", book[user[IdOfUser].NoOfBook[i] - 1].no);
			printf("作者：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].writer);
			printf("图书名：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].BookName);
			printf("出版社：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].press);
			printf("ISBN：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].ISBN);
			printf("价格：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].price);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("按任意键返回");
		free(book);
		free(user);
		_getch();
		BookingMenu();
	}
}

void ReturnBook()
{
	fp4 = fopen("NumOfUser.txt", "r");
	fscanf(fp4, "%d", &NumOfUser);//从文件读取用户人数
	fclose(fp4);

	struct user* user = (struct user*)malloc(sizeof(struct user) * NumOfUser);
	fp2 = fopen("User.txt", "rb");
	fread(user, sizeof(struct user), NumOfUser, fp2);//从文件中读取用户结构体
	fclose(fp2);

	if (user[IdOfUser].NumOfBook == 0)
	{
		system("cls");
		printf("暂未查询到您的图书借阅信息\n");
		printf("按任意键返回");
		free(user);
		_getch();
		BookingMenu();
	}
	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);

		system("cls");
		for (int i = 0; i < user[IdOfUser].NumOfBook; i++)
		{
			printf("NO.%d\n", book[user[IdOfUser].NoOfBook[i] - 1].no);
			printf("作者：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].writer);
			printf("图书名：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].BookName);
			printf("出版社：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].press);
			printf("ISBN：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].ISBN);
			printf("价格：%s\n", book[user[IdOfUser].NoOfBook[i] - 1].price);
			printf("                                                 \n");
			printf("-------------------------------------------------\n");
			printf("                                                 \n");
		}
		printf("请选择要还借的图书编号");
		int no;
		int index;//记下图书编号储存在NoOfBook中的位置
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
			printf("对不起，您没有借阅该图书\n");
			printf("按任意键重新输入，按ESC返回");
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
			printf("作者：%s\n", book[no - 1].writer);
			printf("图书名：%s\n", book[no - 1].BookName);
			printf("出版社：%s\n", book[no - 1].press);
			printf("ISBN：%s\n", book[no - 1].ISBN);
			printf("价格：%s\n", book[no - 1].price);
			printf("\n");
			printf("您确定要还该图书借阅信息吗？\n");
			printf("按任意键确定，按ESC取消\n");
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
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
			fclose(fp5);
			free(book);
			fp2 = fopen("User.txt", "wb");
			fwrite(user, sizeof(struct user), NumOfUser, fp2);//将用户结构体写入文件
			fclose(fp2);
			free(user);
			printf("删除成功，按任意键返回");
			_getch();
			BookingMenu();
		}
	}
}
