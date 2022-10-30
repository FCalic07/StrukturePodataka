#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME (128)
#define ALLOCATION_ERROR (-1)
#define while_on (1)
#define DESCENDING_ORDER (0)
#define FILE_OPENING_ERROR (-1)

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int birth_year;
	Position Next;
}Person;

int printMenu();
Position CreatePerson(char* name, char* surname, int birth_year);
int InsertAfter(Position pos1, Position pos2); /* pozicija 2 nakon pozicije 1 */
int PrintList(Position Head);
int PrintPerson(Position pos);
Position DataEntry(Position newPerson);
int DeleteAll(Position Head);

int AddAtBeggining(Position Head);
int AddAtEnd(Position Head);
Position FindLast(Position Head);
int FindSurname(Position Head);
int DeleteElement(Position Head);
int DeleteAfter(Position Head, Position pos);
Position FindPrev(Position Head, Position pos);

int SurnameSort(Position Head);
int AddAfter(Position Head);
int AddBefore(Position Head);

int WriteInFile(Position Head);
int ReadFromFile(Position Head);
//malo sam izgubio koncentraciju na nekim stvarima ali sve radi

int main() {
	Person Zeroth = { .name = {0},.surname = {0},.birth_year = 0,.Next = NULL };
	Position Head = &Zeroth;
	char choice = '\0';

	while (while_on) {
		printMenu(); /*meni*/
		scanf(" %c", &choice);
		choice = toupper(choice);

		if (choice == 'Z') /*end program*/
			break;

		switch (choice) { /*opcije*/ //ovdje mi je fazon da sve budu s parametrom head jer je mocno
		case('A'):
			AddAtBeggining(Head);
			break;
		case('B'):
			AddAtEnd(Head);
			break;
		case('C'):
			FindSurname(Head);
			break;
		case('D'):
			DeleteElement(Head); /*ovo mi je labavo*/
			break;
		case('P'):
			PrintList(Head);
			break;
		case('S'):
			SurnameSort(Head);
			break;
		case('Q'):
			AddAfter(Head);
			break;
		case('E'):
			AddBefore(Head);
			break;
		case('W'):
			WriteInFile(Head);
			break;
		case('R'):
			ReadFromFile(Head);
			break;
		default:
			printf("\nSta ti je jarane\n");
		}
	}
	
	DeleteAll(Head); /*zaboravio sam kako je ono duje uradio*/
	printf("\nDeallocation of memory is successful!\n");

	return EXIT_SUCCESS;
}

int printMenu() {
	printf("\n--------------------------------------\n\t\tMENU\n--------------------------------------\nA) Add an element at the beggining\nB) Add an element at the end\nC) Find surname\nD) Delete element\nP) Print list\nS) Sort by surnames\nQ) Add after an element\nE) Add before an element\nW) Write the list into a file\nR) Read the list from a file\nZ) End\n\n");
	return EXIT_SUCCESS;
}

int AddAtBeggining(Position Head) {
	Position nP = NULL;
	nP = DataEntry(nP);		/*provjeri trebal provjeravat i ovdje ///////////////*/
	InsertAfter(Head, nP);

	return EXIT_SUCCESS;
}

Position DataEntry(Position newPerson) { /* zivciralo me sto se ponavlja */
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birth_year = 0;

	printf("\nName: "); /*unos*/
	scanf(" %s", name);
	printf("Surname: ");
	scanf(" %s", surname);
	printf("Birth year: ");
	scanf(" %d", &birth_year);

	newPerson = CreatePerson(name, surname, birth_year);
	if (!newPerson) {
		return ALLOCATION_ERROR;
	}
	return newPerson;
}

Position CreatePerson(char* name, char* surname, int birth_year) {
	Position nP = NULL;

	nP = (Position)malloc(sizeof(Person));
	if (!nP) {
		printf("\tAllocation error!\n");
		return ALLOCATION_ERROR;
	}
	strcpy(nP->name, name);
	strcpy(nP->surname, surname);
	nP->birth_year = birth_year;
	nP->Next = NULL;

	return nP;
}

int InsertAfter(Position pos1, Position pos2)
{
	pos2->Next = pos1->Next;
	pos1->Next = pos2;
	return EXIT_SUCCESS;
}

int AddAtEnd(Position Head) {
	Position Last = NULL;
	Position nP = NULL;

	nP = DataEntry(nP);
	Last = FindLast(Head);
	InsertAfter(Last, nP);

	return EXIT_SUCCESS;
}

Position FindLast(Position Head) {
	Position TEMP = Head;

	while (TEMP->Next) {
		TEMP = TEMP->Next;
	}
	return TEMP;
}

int FindSurname(Position Head) {
	Position TEMP = Head;
	int count = 0;
	char surname[MAX_NAME] = { 0 };

	printf("\nEnter the surname you want to find: ");
	scanf(" %s", surname);

	while (TEMP) { /*nmg ovdje stavit if usporedbu jer temp=temp.next mi mora bit izvan*/
		if (strcmp(TEMP->surname, surname) == 0) {
			PrintPerson(TEMP);
			count++;
		}
		TEMP = TEMP->Next;
	}
	if (!count) {
		printf("\nA person with that surname does not exist!\n");
	}
	return EXIT_SUCCESS;
}

int DeleteElement(Position Head) { //ovo mi jako smeta jer sta ako ima vise prezime//
	Position TEMP = Head;				// ali u isto vrijeme ne znam sta je najbolje da pitam korisnika onda//
	char surname[MAX_NAME] = { 0 };
	int count = 0;

	printf("\nEnter the surname of the person you want to delete: ");
	scanf(" %s", surname);


	while (TEMP) {
		if (strcmp(TEMP->surname, surname) == 0) {
			DeleteAfter(Head, TEMP);
			count++;
			break;
		}
		TEMP = TEMP->Next;
	}
	if (!count) {
		printf("\nA person with that surname does not exist!\n");
	}
	return EXIT_SUCCESS;
}

int DeleteAfter(Position Head, Position pos) {
	Position TEMP = pos;
	Position prev_TEMP = FindPrev(Head, TEMP);
	prev_TEMP->Next = TEMP->Next;
	free(TEMP);

	return EXIT_SUCCESS;
}

Position FindPrev(Position Head, Position pos) {
	Position TEMP = Head;
	while (TEMP) {
		if (TEMP->Next == pos) {
			return TEMP;
		}
		TEMP = TEMP->Next;
	}
	if (!TEMP) {
		printf("\nNon-existing element.\n");
		return NULL;
	}
}

int PrintPerson(Position pos) {
	printf("\n\nFull name: %s %s\nBirth year: %d\n", pos->name, pos->surname, pos->birth_year);
	return EXIT_SUCCESS;
}

int PrintList(Position Head) {
	Position TEMP = Head->Next;
	int i = 1;
	while (TEMP) {
		printf("\n%d\nFull name: %s %s\nBirth year: %d\n", i, TEMP->name, TEMP->surname, TEMP->birth_year);
		TEMP = TEMP->Next;
		i++;
	}

	return EXIT_SUCCESS;
}

int SurnameSort(Position Head) {
	Position TEMP = NULL;
	Position end = NULL;
	Position prev_pos = Head;
	Position pos = Head->Next;

	while (Head->Next != end) {
		prev_pos = Head;
		pos = Head->Next;
		while (pos->Next != end) {
			if (strcmp(pos->surname, pos->Next->surname) > DESCENDING_ORDER) {
				TEMP = pos->Next;
				prev_pos->Next = TEMP;
				pos->Next = TEMP->Next;
				TEMP->Next = pos;

				pos = TEMP;
			}
			prev_pos = pos;
			pos = pos->Next;
		}
		end = pos;
	}

	return EXIT_SUCCESS;
}

int AddAfter(Position Head) {
	Position TEMP = Head;
	Position nP = NULL;
	char surname[MAX_NAME] = { 0 };
	int count = 0;

	printf("\nAfter which person do you want to add a new one: ");
	scanf(" %s", surname);

	while (TEMP) {
		if (strcmp(TEMP->surname, surname) == 0) {
			count++;
			nP = DataEntry(nP);
			InsertAfter(TEMP, nP);
			break;
		}
		TEMP = TEMP->Next;
	}
	if (!count) {
		printf("\nA person with that surname isn't in the list!\n");
	}
	return EXIT_SUCCESS;
}

int AddBefore(Position Head) {
	Position TEMP = Head;
	Position nP = NULL;
	char surname[MAX_NAME] = { 0 };
	int count = 0;

	printf("\nBefore which person do you want to add a new one: ");
	scanf(" %s", surname);

	while (TEMP) {
		if (strcmp(TEMP->surname, surname) == 0) {
			count++;
			nP = DataEntry(nP);
			TEMP = FindPrev(Head, TEMP);
			InsertAfter(TEMP, nP);
			break;
		}
		TEMP = TEMP->Next;
	}
	if (!count) {
		printf("\nA person with that surname isn't in the list!\n");
	}
	return EXIT_SUCCESS;
}

int WriteInFile(Position Head) {
	Position TEMP = Head->Next;
	
	FILE* fp = NULL;
	fp = fopen("People.txt", "w");
	if (!fp) {
		printf("\nFile can not open!\n");
		return FILE_OPENING_ERROR;
	}

	while (TEMP) {
		fprintf(fp, "\n%s %s %d", TEMP->name, TEMP->surname, TEMP->birth_year);
		TEMP = TEMP->Next;
	}

	printf("\nList successfully written into a file ''People.txt''\n");

	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadFromFile(Position Head) { 
	Position TEMP = Head;
	Position newPerson = NULL;
	Position Last = NULL;
	char name[MAX_NAME] = { 0 }; 
	char surname[MAX_NAME] = { 0 }; 
	int birth_year = 0;

	FILE* fp = NULL;
	fp = fopen("People.txt", "r");
	if (!fp) {
		printf("\nFile can not open!\n");
		return FILE_OPENING_ERROR;
	}
	
	DeleteAll(TEMP); //idk jel zele da obrisem sve ili da dodajem na kraj ali kako god nije nesto tesko

	while (!feof(fp)) {
		fscanf(fp, "%s%s%d", name, surname, &birth_year);
		newPerson = CreatePerson(name, surname, birth_year);
		if (!newPerson) {
			return ALLOCATION_ERROR;
		}
		Last = FindLast(TEMP);
		InsertAfter(Last, newPerson);
	}
	fclose(fp);

	printf("\nList successfully updated from ''People.txt''\n");

	return EXIT_SUCCESS;
}

int DeleteAll(Position Head)
{
	Position temp1 = Head;
	Position temp2 = NULL;

	while (temp1->Next)
	{
		temp2 = Head->Next;
		temp1->Next = temp2->Next;
		free(temp2);
	}
	Head = NULL;

	return EXIT_SUCCESS;
}