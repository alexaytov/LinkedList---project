#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>



FILE * getFile() {
	FILE *fp;
	if (!fopen("list.dat", "rb")) {
		fopen("list.dat", "wb");
	}
	if (!(fp = fopen("list.dat", "r+"))) {
		printf("Проблем при зареждаен ан файл - list.dat");
		system("pause");
		exit(1);
	}

	return fp;
}

void getInfo(MEDICAMENT *p) {

	int i;
	printf("Име на лекарството: ");
	//getchar();
	fflush(stdin);
	do {
		if (fgets(p->name, 30, stdin) == NULL) {

			printf("Проблем при четене на данни!!!");
			system("pause");
			exit(1);
		}
	} while (!strcmp(p->name, "\n"));
	
	i = strlen(p->name) - 1;
	if (p->name[i] == '\n') {
		p->name[i] = '\0';
	}

	printf("Номенклатурен номер: ");

	if (fgets(p->Nnum, 30, stdin) == NULL) {
		
		printf("Проблем при четене на данни!!!");
		system("pause");
		exit(1);
	}
	i = strlen(p->Nnum) - 1;
	if (p->Nnum[i] == '\n') {
		p->Nnum[i] = '\0';
	}
	printf("Цена на лекартсвото: ");
	if (!(scanf("%f", &p->price) > 0)) {
		printf("Проблем при четене на данни!!!");
		system("pause");
		exit(1);
	}
	do {
		printf("Дата на производство във формат ДД.ММ.ГГГГ: ");
		if (!(scanf("%d.%d.%d", &p->date, &p->month, &p->year))) {
			printf("Проблем при четене на данни!!!");
			system("pause");
			exit(1);
		}
	} while (!(p->date >= 1 && p->date <= 31 && p->month >= 1 && p->month <= 12 && p->year > 999 && p->year <= 10000));
	do {
		printf("Въведете срок на годност в години: ");
		if (!(scanf("%d", &p->expiryDate))) {
			printf("Проблем при четене на данни!!!");
			system("pause");
			exit(1);
		}
	} while (p->expiryDate < 0);
	p->expiryDate += p->year;
}
NODE * push(NODE * head, MEDICAMENT p) {
	NODE *hlp;
	if (!(hlp = (NODE *)malloc(sizeof(NODE)))) {
		printf("Problem allocating memory!!!");
		system("pause");
		exit(1);
	}
	hlp->med = p;
	hlp->next = head;
	head = hlp;
	return head; //резултат - ново начало на списъка
}

void checkingID(NODE *head) {
	if (head == NULL) {
		printf("\nСписъкът е празен\n\n");
		system("pause");
		system("cls");
		return;
	}
	int flag;
	NODE *crnt;
	char numToCheck[30];
	
	printf("Въведете номенклатурен номер: ");
	if (!(scanf("%s", numToCheck) > 0)) {
		printf("Проблем при четене на данни!!!");
		system("pause");
		exit(1);
	}
	
	flag = 0;
	crnt = head;
	while (crnt != NULL) {
		if (!strcmp(numToCheck, crnt->med.Nnum)) {
			printf("\nИме на лекарството: %s\n", crnt->med.name);
			printf("Номенклатурен номер: %s\n", crnt->med.Nnum);
			printf("Цена на лекарството: %.2f\n", crnt->med.price);
			printf("Дата на производство: %d.%d.%d\n", crnt->med.date, crnt->med.month, crnt->med.year);
			printf("Срок на годсност %d.%d.%d\n\n", crnt->med.date, crnt->med.month, crnt->med.expiryDate);

			flag = 1;
			break;
		}
		crnt = crnt->next;
	}
	if (!flag) {
		printf("\nНяма лекарство с номенклатурен номер: %s\n\n", numToCheck);
	}
	system("pause");

}

void priceChange(NODE *head) {
	if (head == NULL) {
		printf("\nСписъкът е празен\n\n");
		system("pause");
		system("cls");
		return;
	}

	char nameToCheck[30];
	int flag = 0;
	NODE *crnt;
	crnt = head;
	printf("Въведете име на лекарство ");
	if (!(scanf("%s", nameToCheck) > 0)) {
		printf("Проблем при четене на данни!!!");
		system("pause");
		exit(1);
	}
	while (crnt != NULL) {
		if (!strcmp(nameToCheck, crnt->med.name)) {

			printf("\nСтара цена на лекарството: %.2f\n", crnt->med.price);
			do {
				printf("\nВъведете нова цена на лекартсвото: ");
				if (!(scanf("%f", &crnt->med.price))) {
					printf("Проблем при четене на данни!!!");
					system("pause");
					exit(1);
				}
			} while (!crnt->med.price > 0);
			flag = 1;
			break;

		}
		crnt = crnt->next;
	}
	if (!flag) {
		printf("Няма лекарство с това име %s в списъка!", nameToCheck);

	}
	else {
		printf("Цената на лекарството е променена\n");
	}
	system("pause");
}

void printAll(NODE *head) {
	if (head == NULL) {
		printf("\nСписъкът е празен\n\n");
		system("pause");
		system("cls");
		return;
	}
	NODE *crnt;
	crnt = head;
	printf("ЛЕКАРСТВА:\n");
	while (crnt != NULL) {

		printf("\nИме: %s", crnt->med.name);
		printf("\nНоменклатурен номер: %s", crnt->med.Nnum);
		printf("\nЦена: %.2f", crnt->med.price);
		printf("\nДата на производствo: %d.%d.%d\n", crnt->med.date, crnt->med.month, crnt->med.year);
		printf("Срок на годност %d.%d.%d\n\n", crnt->med.date, crnt->med.month, crnt->med.expiryDate);

		crnt = crnt->next;
	}
	system("pause");


}

void expDate(NODE *head) {
	if (head == NULL) {
		printf("\nСписъкът е празен\n\n");
		system("pause");
		system("cls");
		return;
	}
	NODE *crnt;
	crnt = head;
	int date, month, year;
	int flag = 0;

	do {
		printf("Въведете сегашна дата във формат ДД.ММ.ГГГГ: ");
		if (!(scanf("%d.%d.%d", &date, &month, &year) > 0)) {
			printf("Проблем при четене на данни!!!");
			system("pause");
			exit(1);
		}
	} while (!(date >= 0 && date <= 31 && month >= 1 && month <= 12 && year > 999 && year <= 10000));

	while (crnt != NULL) {
		if (year > crnt->med.expiryDate) {
			printf("\nИме: %s", crnt->med.name);
			printf("Номенклатурен номер: %s\n", crnt->med.Nnum);
			printf("Цена: %.2f", crnt->med.price);
			printf("\nДата на производствo: %d.%d.%d\n", crnt->med.date, crnt->med.month, crnt->med.year);
			printf("Срок на годност %d.%d.%d\n\n", crnt->med.date, crnt->med.month, crnt->med.expiryDate);
			flag = 1;
		}
		else if ((month > crnt->med.month) && (year == crnt->med.expiryDate)) {
			printf("\nИме: %s", crnt->med.name);
			printf("\nНоменклатурен номер: %s", crnt->med.Nnum);
			printf("\nЦена: %.2f", crnt->med.price);
			printf("\nДата на производствo: %d.%d.%d\n", crnt->med.date, crnt->med.month, crnt->med.year);
			printf("Срок на годност %d.%d.%d\n\n", crnt->med.date, crnt->med.month, crnt->med.expiryDate);
			flag = 1;
		}
		else if ((date > crnt->med.date) && (month == crnt->med.month) && (year == crnt->med.expiryDate)) {
			printf("\nИме: %s", crnt->med.name);
			printf("\nНоменклатурен номер: %s", crnt->med.Nnum);
			printf("\nЦена: %.2f", crnt->med.price);
			printf("\nДата на производствo: %d.%d.%d\n", crnt->med.date, crnt->med.month, crnt->med.year);
			printf("Срок на годност %d.%d.%d\n\n", crnt->med.date, crnt->med.month, crnt->med.expiryDate);
			flag = 1;
		}

		crnt = crnt->next;
	}
	if (!flag) {
		printf("\nНяма лекарства с изтекъл срок на годност\n");
		system("pause");
	}


}

NODE * free_m(NODE *crnt) {
	NODE *next;
	while (crnt != NULL) {
		next = crnt->next;
		free(crnt);
		crnt = next;
	}
	return NULL;
}

NODE *deleteItem(NODE* head) {
	char NnumToBeDeleted[30];
	NODE *crnt, *prev;
	int isDeleted = 0;
	
	
	printf("Въведете номенклатурен номер на лекарство: ");
	scanf("%s", NnumToBeDeleted);
	
	crnt = head;
	prev = head;
	while (crnt) {
		if (!(strcmp(NnumToBeDeleted, crnt->med.Nnum))) {
			if (crnt == head) {
				head = crnt->next;
				isDeleted = 1;
				break;

			}
			else {
				prev->next = crnt->next;
				isDeleted = 1;
				free(crnt);
				break;
			}
			
			
		
		}
		
		prev = crnt;
		crnt = crnt->next;

	}
	if (isDeleted) {
		printf("Лекарството е изтрито от системата!\n");
		system("pause");
		system("cls");

	}
	else {
		printf("Не е намерено лекарство с този номенклатурен номер: %s\n", NnumToBeDeleted);
		system("pause");
		system("cls");


	}

	return head;

}

