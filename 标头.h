struct manager
{
	char id[50];
	char password[50];
};
struct user
{
	char id[50];
	char password[50];
	char UserName[20];
	char sex[4];
	char birthday[50];
	char major[100];
	int NoOfBook[20];//���ڴ���ͼ����
	int NumOfBook;
};
struct book
{
	int no;
	char ISBN[50];
	char writer[50];
	char BookName[50];
	char press[50];
	char price[50];
	int RestOfBook;
};
void BackStage();
void BookingMenu();
int main();

void ManagerLog();
void logon();
void login();

void UserLog();
void UserLogin();
void UserLogon();
void ViewMine();
void LendBook();
void ReturnBook();

void BookOpreation();
void AddBook();
void view();
void modify();
void delet();
void ModifyNum();

void UserView();//�û��鿴ͼ����Ϣ

