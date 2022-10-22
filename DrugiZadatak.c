#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (128)
#define ALLOCATION_ERROR (-1)

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int birth_year;
	Position Next;
}Person;

Position CreatePerson(char* name, char* surname, int birth_year);
Position FindLast(Position Head);
int PrintList(Position Head);
int InsertIntoBeggining(Position Head, int num);
int PrependList(Position Head, char* name, char* surname, int birth_year);
int InsertFirst(Position Head, Position newPerson);

int InsertIntoEnd(Position Head, int num);
int AppendList(Position Last, char* name, char* surname, int birth_year);
int InsertLast(Position Last, Position newPerson);

int PersonBySurname(Position Head, char* surname);
int PrintPerson_Surname(Position Surname);

int DeleteElement(Position Head, int num);
Position FindPrevious(Position Head, Position Element);

int main() {
	Person Zero = { .name = {0},.surname = {0},.birth_year = 0,.Next = NULL };
	Position Head = &Zero;
	int num = 0;
	char surname[MAX_NAME] = { 0 }; 

	printf("How many people do you want to add at the beginning: ");
	scanf(" %d", &num);
	InsertIntoBeggining(Head, num);

	printf("\nHow many people do you want to add at the end: ");
	scanf(" %d", &num);
	InsertIntoEnd(Head, num);

	printf("\n\n\n");
	PrintList(Head->Next);

	printf("\n\n\nEnter the surname you want to find: ");
	scanf(" %s", surname);
	PersonBySurname(Head, surname);

	printf("\n\n\nWhich element do you want to delete from the linked list: ");
	scanf(" %d", &num);
	DeleteElement(Head->Next, num);

	PrintList(Head->Next);

	return EXIT_SUCCESS;
}

int InsertIntoBeggining(Position Head, int num) {
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birth_year = 0;
	
	while (num) {
		printf("\nName: ");
		scanf(" %s", name);
		printf("Surname: ");
		scanf(" %s", surname);
		printf("Birth year: ");
		scanf(" %d", &birth_year);
		PrependList(Head, name, surname, birth_year);
		num--;
	}

	return EXIT_SUCCESS;
}

int PrependList(Position Head, char* name, char* surname, int birth_year) {
	Position nP = NULL;
	nP = CreatePerson(name, surname, birth_year);

	if (!nP) {
		return ALLOCATION_ERROR;
	}
	
	InsertFirst(Head, nP);

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birth_year) {
	Position nP = NULL;

	nP = (Position)malloc(sizeof(Person));
	if (!nP) {
		printf("\tAllocation error!");	
		return nP;
	}
	strcpy(nP->name, name);
	strcpy(nP->surname, surname);
	nP->birth_year = birth_year;
	nP->Next = NULL;

	return nP;
}

int InsertFirst(Position Head, Position newPerson) {
	newPerson->Next = Head->Next;
	Head->Next = newPerson;

	return EXIT_SUCCESS;
}

int InsertIntoEnd(Position Head, int num) {
	Position Last = NULL;
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birth_year = 0;

	while (num) {
		Last = FindLast(Head);
		printf("\nName: ");
		scanf(" %s", name);
		printf("Surname: ");
		scanf(" %s", surname);
		printf("Birth year: ");
		scanf(" %d", &birth_year);
		AppendList(Last, name, surname, birth_year);
		num--;
	}

	return EXIT_SUCCESS;
}

int AppendList(Position Last, char* name, char* surname, int birth_year) {
	Position nP = NULL;
	nP = CreatePerson(name, surname, birth_year);

	if (!nP) {
		return ALLOCATION_ERROR;
	}

	InsertLast(Last, nP);

	return EXIT_SUCCESS;
}

int InsertLast(Position Last, Position newPerson) {
	newPerson->Next = Last->Next;
	Last->Next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position Head) {
	Position TEMP = Head;

	while (TEMP->Next) {
		TEMP = TEMP->Next;
	}
	return TEMP;
}

int PersonBySurname(Position Head, char* surname) {
	Position TEMP = Head;
	int number = 0;

	while (TEMP) {
		if (strcmp(TEMP->surname, surname) == 0) {
			PrintPerson_Surname(TEMP);
			number++;
		}
		TEMP = TEMP->Next;
	}
	if (!number) {
		printf("\nA person with that surname does not exist!\n");
	}
	return EXIT_SUCCESS;
}

int PrintPerson_Surname(Position Surname) {
	printf("\nName: %s\nSurname: %s\nBirth year: %d\n", Surname->name, Surname->surname, Surname->birth_year);

	return EXIT_SUCCESS;
}

int DeleteElement(Position Head, int num) {
	Position Element = Head;
	Position PreviousElement = NULL;
	
	int i = 1;
	while (!(i == num)) {
		Element = Element->Next;
		if (!Element) {
			printf("\nError! Element does not exist.\n");
			return EXIT_SUCCESS;
		}
		i++;
	}
	PreviousElement = FindPrevious(Head,Element);
	PreviousElement->Next = Element->Next;
	free(Element);

	return EXIT_SUCCESS;
}

Position FindPrevious(Position Head, Position Element) {
	Position TEMP = Head;
	while (!(TEMP->Next == Element))
		TEMP = TEMP->Next;

		return TEMP;
}

int PrintList(Position Head) {
	Position TEMP = Head;
	int i = 1;
	while (TEMP) {
		printf("\n\n%d\nName: %s\nSurname: %s\nBirth year: %d",i, TEMP->name, TEMP->surname, TEMP->birth_year);
		TEMP = TEMP->Next;
		i++;
	}

	return EXIT_SUCCESS;
}