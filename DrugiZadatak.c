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
//int InsertFirst(Position Head, Position newPerson);

int InsertIntoEnd(Position Head, int num);
int AppendList(Position Last, char* name, char* surname, int birth_year);
//int InsertLast(Position Last, Position newPerson);

int PersonBySurname(Position Head, char* surname);
int PrintPerson_Surname(Position Surname);

//int DeleteElement(Position Head, int num);
//Position FindPrevious(Position Head, Position Element);
int InsertAfter(Position head, Position newPerson);
Position FindPrev(Position head, int prethodni);
int DeleteAfter(Position head, int prethodni);

//dealokacija
int DeleteAll(Position head);

int main() {
	Person Zeroth = { .name = {0},.surname = {0},.birth_year = 0,.Next = NULL };
	Position Head = &Zeroth;
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
	DeleteAfter(Head, num-1); //saljes head i num-1 kao izbrisi nakon num-1 jer je funkcija deleteAFTER 

	PrintList(Head->Next);

	//fali ti dealokacija cijele liste,jer nakon zavrsetka programa mora se uvijek pobrisati memorija
	DeleteAll(Head);
	printf("\n\nDeallocation of memory in successful!\n");
	
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

	InsertAfter(Head, nP);

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birth_year) {
	Position nP = NULL;

	nP = (Position)malloc(sizeof(Person));
	if (!nP) {
		printf("\tAllocation error!\n");
		return -1; //ne mozes vracati nP ako ga nema 
	}
	strcpy(nP->name, name);
	strcpy(nP->surname, surname);
	nP->birth_year = birth_year;
	nP->Next = NULL;

	return nP;
}

/*int InsertFirst(Position Head, Position newPerson) {
	newPerson->Next = Head->Next;
	Head->Next = newPerson;

	return EXIT_SUCCESS;
}*/ // nepotrebna funkcija, sve se moze uraditi sa InsertAfter (radjena je na prredavanju), samo se mijenaju parametru funkcije 

int InsertIntoEnd(Position Head, int num) {
	Position Last = NULL;
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birth_year = 0;

	Last = FindLast(Head);// IZVAN WHILE JER CE SE ONDA STALNO TRAZITI ZADNJI,POTREBAN JE ZADNJI PRIJE UNOSA NA KRAJ
	while (num) {
		
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
		printf("\tAllocation error!\n");
		return ALLOCATION_ERROR; //ne mozes vracati nP ako ga nema 
	}

	InsertAfter(Last, nP);

	return EXIT_SUCCESS;
}

/*int InsertLast(Position Last, Position newPerson) {
	newPerson->Next = Last->Next;
	Last->Next = newPerson;

	return EXIT_SUCCESS;
}*/ // NEPOTREBNO 

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

/*int DeleteElement(Position Head, int num) {//nepotrebo prekomplicirano, jednostavno koristis DeleteAfter i brises next element od onoga kojeg korisnik odabere(on postaje previous)
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
	PreviousElement = FindPrevious(Head, Element);
	PreviousElement->Next = Element->Next;
	free(Element);

	return EXIT_SUCCESS;
}


Position FindPrevious(Position Head, Position Element) {
	Position TEMP = Head;
	while (!(TEMP->Next == Element)) // javlja se greska "Unable to read memory" ako se odabere da se obrise prvi element,zato sto ako se odabere prvi element, ovaj uvjet ga odmah provjerava sa njegovim nextom tj. automatski ga preskace, pa se prakticki izidje iz petlje, tj TEMP postaje NULL, pa TEMP->NEXT pristupa izvan memorije "Unhandled exception thrown: read access violation. **TEMP** was nullptr."
		
		TEMP = TEMP->Next;

	return TEMP;
}
*/



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int DeleteAfter(Position head, int prethodni)
{
	Position temp1 = FindPrev(head, prethodni);
	Position temp2 = NULL;
	if (!temp1)
	{
		printf("Nepostojeci element.\n");
		return NULL;
	}

	temp2 = temp1->Next;
	temp1->Next = temp2->Next;

	free(temp2);


	return EXIT_SUCCESS;
}

Position FindPrev(Position head, int prethodni)
{
	Position temp = head;

	while (prethodni)
	{
		temp = temp->Next;
		prethodni--;
	}

	return temp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int PrintList(Position Head) {
	Position TEMP = Head;
	int i = 1;
	while (TEMP) {
		printf("\n%d\nName: %s\nSurname: %s\nBirth year: %d", i, TEMP->name, TEMP->surname, TEMP->birth_year);
		TEMP = TEMP->Next;
		i++;
	}

	return EXIT_SUCCESS;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int InsertAfter(Position head, Position newPerson)
{
	newPerson->Next = head->Next;
	head->Next = newPerson;

	return EXIT_SUCCESS;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//dealokacija
int DeleteAll(Position head)
{
	Position temp1 = head;
	Position temp2 = NULL;

	while (temp1->Next)
	{
		temp2 = head->Next;
		temp1->Next = temp2->Next;
		free(temp2);
	}
	head = NULL;

	return EXIT_SUCCESS;
}
