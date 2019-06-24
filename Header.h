typedef struct
{
	char Nnum[30];
	char name[30];
	float price;
	int date;
	int month;
	int year;
	int expiryDate;

}MEDICAMENT;
typedef struct item
{
	MEDICAMENT med;
	struct item *next;
}NODE;

int menu(char *t[]);


