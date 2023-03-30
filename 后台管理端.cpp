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
extern FILE* fp1;
extern FILE* fp2;
extern FILE* fp3;
extern FILE* fp4;
extern FILE* fp5;//Book.txt
extern FILE* fp6;//NumOfBook.txt
extern int NumOfManager;
extern int NumOfUser;
extern int NumOfBook;
void ManagerLog()//员工登录注册界面
{
	system("cls");
	printf("     欢迎使用后台管理\n");
	printf("**************************\n");
	printf("***    1.登录已有账户  ***\n");
	printf("***    2.注册新账户    ***\n");
	printf("***    3.返回上一级    ***\n");
	printf("**************************\n");
	int choose = _getch();
	switch (choose)
	{
	case 49:login(); break;
	case 50:logon(); break;
	case 51:main();
	}
}
void BackStage()//后台管理界面
{
	system("cls");
	printf(" 请选择您需要的服务\n");
	printf("************************\n");
	printf("***   1.图书操作     ***\n");
	printf("***   2.库存操作     ***\n");
	printf("***   3.返回上一级   ***\n");
	printf("***   按esc退出程序  ***\n");
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
void logon()//管理员账户注册
{
	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp3);//检查文件长度
	fseek(fp3, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)//第一个员工创建账号
	{
		char key[20];//用于存储再次输入的密码
		system("cls");
		struct manager* manager = (struct manager*)malloc(sizeof(struct manager));
		printf("请创建一个账号\n");
		scanf("%s", &manager[0].id);
		printf("请输入您的密码\n");
		scanf("%s", &manager[0].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(manager[0].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &manager[0].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(manager[0].password, key) == 0)
					flag = 0;
			}
		}
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");//创建NumOfManager.txt
		fprintf(fp3, "%d", NumOfManager);//将管理人员人数写入文件中
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//将管理人员结构体写入文件
		fclose(fp1);
		free(manager);
		system("cls");
		printf("创建账户成功\n按任意键返回登录界面");
		_getch();
		ManagerLog();
	}
	else//后续员工创建账号
	{
		system("cls");
		fp3 = fopen("NumOfManager.txt", "r");
		fscanf(fp3, "%d", &NumOfManager);//从文件读取管理人员人数
		fclose(fp3);

		struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
		fp1 = fopen("Manager.txt", "rb");
		fread(manager, sizeof(struct manager), NumOfManager, fp1);//从文件中读取管理人员结构体
		fclose(fp1);

		manager = (struct manager*)realloc(manager, sizeof(struct manager) * (NumOfManager + 1));
		//管理人员结构体扩容一个单位

		char key[20];//用于存储再次输入的密码
		printf("请创建一个账号\n");
		scanf("%s", &manager[NumOfManager].id);
		for (int i = 0; i < NumOfManager; i++)
		{
			if (strcmp(manager[NumOfManager].id, manager[i].id) == 0)
			{
				int flag = 1;
				while (flag)
				{
					system("cls");
					printf("已有账号，请重新输入");
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
		printf("请输入您的密码\n");
		scanf("%s", &manager[NumOfManager].password);
		printf("请确认您的密码\n");
		scanf("%s", &key);
		if (strcmp(manager[NumOfManager].password, key) != 0)//检验两次输入密码是否相同
		{
			int flag = 1;
			while (flag)
			{
				system("cls");
				printf("您输入的两次密码不同，请重新输入密码\n");
				scanf("%s", &manager[NumOfManager].password);
				printf("请确认您的密码");
				scanf("%s", key);
				if (strcmp(manager[NumOfManager].password, key) == 0)
					flag = 0;
			}
		}
		printf("创建账户成功\n按任意键返回登录界面");
		NumOfManager++;
		fp3 = fopen("NumOfManager.txt", "w");
		fprintf(fp3, "%d", NumOfManager);//将管理人员人数写入文件中
		fclose(fp3);
		fp1 = fopen("Manager.txt", "wb");
		fwrite(manager, sizeof(struct manager), NumOfManager, fp1);//将管理人员人数写入文件中
		fclose(fp1);
		free(manager);
		_getch();
		system("cls");
		ManagerLog();
	}
}

void login()//账户登录
{
	char id[20];
	char password[20];
	system("cls");
	printf("请输入账号\n");
	scanf("%s", &id);
	printf("请输入密码\n");
	scanf("%s", &password);

	if ((fp3 = fopen("NumOfManager.txt", "r")) == NULL)
	{
		fp3 = fopen("NumOfManager.txt", "w");
		fclose(fp3);
	}
	fp3 = fopen("NumOfManager.txt", "rb");
	fseek(fp3, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp3);//检查文件长度
	fseek(fp3, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)
	{
		system("cls");
		printf("您输入的账号或密码有误按任意键重新输入,ESC返回");
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
	fscanf(fp3, "%d", &NumOfManager);//从文件读取管理人员人数
	fclose(fp3);

	struct manager* manager = (struct manager*)malloc(sizeof(struct manager) * NumOfManager);
	fp1 = fopen("Manager.txt", "rb");
	fread(manager, sizeof(struct manager), NumOfManager, fp1);//从文件中读取管理人员结构体
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
			printf("您输入的账号或密码有误\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				ManagerLog();
			system("cls");
			printf("请输入账号\n");
			scanf("%s", &id);
			printf("请输入密码\n");
			scanf("%s", &password);
		}
	}
	BackStage();
}

void BookOpreation()
{
	system("cls");
	printf(" 请选择您需要的操作\n");
	printf("************************\n");
	printf("***   1.查看图书     ***\n");
	printf("***   2.添加图书     ***\n");
	printf("***   3.修改图书     ***\n");
	printf("***   4.删除图书     ***\n");
	printf("***   5.返回上一级   ***\n");
	printf("***   按esc退出程序  ***\n");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头
	if (len == 0)//第一次添加图书
	{
		NumOfBook = 1;
		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		book[0].no = NumOfBook;
		system("cls");
		printf("请输入图书名\n");
		scanf("%s", &book[NumOfBook - 1].BookName);
		printf("请输入作者\n");
		scanf("%s", &book[NumOfBook - 1].writer);
		printf("请输入出版社\n");
		scanf("%s", &book[NumOfBook - 1].press);
		printf("请输入ISBN\n");
		scanf("%s", &book[NumOfBook - 1].ISBN);
		printf("请输入价格\n");
		scanf("%s", &book[NumOfBook - 1].price);
		printf("请输入图书本数\n");
		scanf("%d", &book[NumOfBook - 1].RestOfBook);
		fp6 = fopen("NumOfBook.txt", "w");
		fprintf(fp6, "%d", NumOfBook);//将图书数写入文件中
		fclose(fp6);
		fp5 = fopen("Book.txt", "wb");
		fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
		fclose(fp5);
		free(book);
		printf("添加完成，按任意键返回\n");
		_getch();
		BookOpreation();
	}
	else//后续添加图书
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		NumOfBook++;
		fclose(fp6);
		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);
		system("cls");
		book[NumOfBook - 1].no = NumOfBook;
		printf("请输入图书名\n");
		scanf("%s", &book[NumOfBook - 1].BookName);
		printf("请输入作者\n");
		scanf("%s", &book[NumOfBook - 1].writer);
		printf("请输入出版社\n");
		scanf("%s", &book[NumOfBook - 1].press);
		printf("请输入ISBN\n");
		scanf("%s", &book[NumOfBook - 1].ISBN);
		printf("请输入价格\n");
		scanf("%s", &book[NumOfBook - 1].price);
		printf("请输入图书本数\n");
		scanf("%d", &book[NumOfBook - 1].RestOfBook);

		fp6 = fopen("NumOfBook.txt", "w");
		fprintf(fp6, "%d", NumOfBook);//将图书数写入文件中
		fclose(fp6);
		fp5 = fopen("Book.txt", "wb");
		fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
		fclose(fp5);
		free(book);
		printf("添加完成，按任意键返回\n");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有图书信息\n按任意键返回");
		_getch();
		BookOpreation();
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
			BookOpreation();
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
			free(book);
			printf("按任意键返回");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有图书信息\n按任意键返回");
		_getch();
		BookOpreation();
	}

	else
	{
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);
		if (NumOfBook == 0)//图书数为0
		{
			system("cls");
			printf("当前没有图书信息\n按任意键返回");
			_getch();
			BookOpreation();
		}
		fp6 = fopen("NumOfBook.txt", "r");
		fscanf(fp6, "%d", &NumOfBook);//从文件读取图书数
		fclose(fp6);

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);

		system("cls");
		printf("请选择要修改的图书编号");
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
			printf("没有找到该图书信息\n");
			printf("按任意键重新输入，按ESC返回");
			int esc = _getch();
			if (esc == 27)
				BookOpreation();
			else
				modify();
		}
		else//找到对应图书信息
		{
			system("cls");
			printf("NO.%d\n", book[no - 1].no);
			printf("作者：%s\n", book[no - 1].writer);
			printf("图书名：%s\n", book[no - 1].BookName);
			printf("出版社：%s\n", book[no - 1].press);
			printf("ISBN：%s\n", book[no - 1].ISBN);
			printf("价格：%s\n", book[no - 1].price);
			printf("剩余本数：%d\n", book[no - 1].RestOfBook);
			printf("\n");
			printf("请选择要修改的内容\n");
			printf("************************\n");
			printf("***   1.作者         ***\n");
			printf("***   2.图书名       ***\n");
			printf("***   3.出版社       ***\n");
			printf("***   4.价格         ***\n");
			printf("***   5.剩余本数       ***\n");
			printf("***   6.ISBN         ***\n");
			printf("***   7.返回上一级   ***\n");
			printf("************************\n");
			int choose = _getch();
			switch (choose)
			{
			case 49:printf("请输入作者"); scanf("%s", &book[no - 1].writer); break;
			case 50:printf("请输入图书名"); scanf("%s", &book[no - 1].BookName); break;
			case 51:printf("请输入出版社"); scanf("%s", &book[no - 1].press); break;
			case 52:printf("请输入价格"); scanf("%s", &book[no - 1].price); break;
			case 53:printf("请输入剩余本数"); scanf("%d", &book[no - 1].RestOfBook); break;
			case 54:printf("请输入ISBN"); scanf("%s", &book[no - 1].ISBN); break;
			case 55:modify(); break;
			}
			fp5 = fopen("Book.txt", "wb");
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
			fclose(fp5);
			free(book);
			system("cls");
			printf("更改完成，按任意键返回");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有图书信息\n按任意键返回");
		_getch();
		BookOpreation();
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
			BookOpreation();
		}

		struct book* book = (struct book*)malloc(sizeof(struct book) * NumOfBook);
		fp5 = fopen("Book.txt", "rb");
		fread(book, sizeof(struct book), NumOfBook, fp5);//从文件中读取图书结构体
		fclose(fp5);

		system("cls");
		printf("请选择要删除的图书编号\n");
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
			printf("作者：%s\n", book[no - 1].writer);
			printf("图书名：%s\n", book[no - 1].BookName);
			printf("出版社：%s\n", book[no - 1].press);
			printf("ISBN：%s\n", book[no - 1].ISBN);
			printf("价格：%s\n", book[no - 1].price);
			printf("剩余本数：%d\n", book[no - 1].RestOfBook);
			printf("\n");
			printf("您确定要删除该图书信息吗？\n");
			printf("按任意键确认，ESC取消\n");
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
				for (int i = 0; i < NumOfBook; i++)//删除后重新编号
				{
					book[i].no = i + 1;
				}
				fp6 = fopen("NumOfBook.txt", "w");
				fprintf(fp6, "%d", NumOfBook);//将图书数写入文件中
				fclose(fp6);
				fp5 = fopen("Book.txt", "wb");
				fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
				fclose(fp5);
				free(book);
				printf("删除完成，按任意键返回\n");
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
	fseek(fp6, 0, SEEK_END);//将文件指针移到文件末尾
	int len = ftell(fp6);//检查文件长度
	fseek(fp6, 0, SEEK_SET);//将文件指针移到文件开头

	if (len == 0)//未添加图书信息
	{
		system("cls");
		printf("当前没有图书信息\n按任意键返回");
		_getch();
		BackStage();
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
		printf("请选择要操作的图书编号\n");

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
				BookOpreation();
			else
			{
				ModifyNum();
			}
		}
		else
		{
			printf("请输入修改的图书数目\n");
			scanf("%d", &book[no - 1].RestOfBook);
			fp5 = fopen("Book.txt", "wb");
			fwrite(book, sizeof(struct book), NumOfBook, fp5);//将图书结构体写入文件
			fclose(fp5);
			free(book);
			system("cls");
			printf("更改完成，按任意键返回");
			_getch();
			BackStage();
		}
	}
}