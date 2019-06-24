#include <stdio.h>
#include "my_func.h"
#include <windows.h>
#include <ctype.h>
#include <limits.h>




//menu
char *txt_menu_g[] =
{
	"PROGRAM MEDICINE:",
	"Добавяне на ново лекарство",
	"Промяна на цената на зададено лекарство",
	"Всички лекарства с изтекъл срок на годност",
	"Информация за лекарство",
	"Показване на всички лекарствa в системата",
	"Изтриване на лекарство от системата",
	"Изход",
	NULL
};



int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int mode;
	int flag = 0;
	MEDICAMENT p;
	NODE *head = NULL, *newE = NULL, *crnt = NULL, *prev = NULL;
	FILE *fp = NULL;
	//Making list from a the list file
	fp = getFile();
	do {
		if (!fread(&p, sizeof(p), 1, fp)) {
			
			break;
		}
		head = push(head, p);
	} while (1);
	//End of making list


	
	//menu
	do{
		mode = menu(txt_menu_g);
		switch (mode){
			case 1:
				getInfo(&p);
				head = push(head, p);
				/*if (fwrite(&p, sizeof(p), 1, fp) != 1) {
					printf("Проблем при записване във файла!!!");
					system("pause");
					exit(1);
				}
			*/	
				break;
			case 2:
				priceChange(head);
				break;
			case 3:
				expDate(head);
				break;

			case 4:
				checkingID(head);
				break;
			case 5:
				printAll(head);
				break;
			case 6:
				head = deleteItem(head);

		}
	} while (mode != 7);
	
	fclose(fp);
	// Writing the updated list to the file
	if (!(fp = fopen("list.dat", "wb"))) {
		printf("Проблем при записване във файла!!! - list.dat");
		system("pause");
		exit(1);
	}
	crnt = head;
	while (crnt != NULL) {
		fwrite(&crnt->med, sizeof(p), 1, fp);
		crnt = crnt->next;

	}
	crnt = head;
	head = free_m(crnt);







	/*NODE *head = NULL, *newE = NULL, *crnt = NULL, *prev = NULL;

	do
	{
		newE = (NODE*)malloc(sizeof(NODE));
		if (newE == NULL)
		{
			printf("Не се заделя памет!");
			exit(1);
		}
		printf("\nВъведете име на поредния студент:");
		scanf("%s", newE->s.name);//proverki
		if (!strcmp(newE->s.name, "*"))
			break;
		printf("\nВъведете фн на поредния студент:");
		scanf("%d", &newE->s.fn);//proverki

		if (head == NULL)
		{
			newE->next = NULL;
			head = newE;
		}
		else
		{
			newE->next = head;
			head = newE;
			//vuvejdane v opashkata
			/*crnt = head;
			while (crnt->next != NULL){
				crnt = crnt->next;
			}
			newE->next = NULL;
			crnt->next = newE;
			
		}

	} while (1);
	// iztrivane na konkreten element !

	crnt = head;
	while (crnt != NULL){
		if (!strcmp("ivan", crnt->s.name)){


			if (prev == NULL){
				head = crnt->next;
				free(crnt);

				break;
			}
			else {
				prev = crnt->next;
				crnt->next = crnt - crnt -> next;
				free(crnt);
				break;
			}
		}
		
		prev = crnt;
		crnt = crnt->next;
	}

	printf("\nСъдържание на списъка:");
	crnt = head;
	while (crnt != NULL)
	{
		printf("\nИме:%s", crnt->s.name);
		printf("Факултетен номер:%d", crnt->s.fn);
		crnt = crnt->next;
	}
	system("pause");
	*/

	
	return 0;
}
