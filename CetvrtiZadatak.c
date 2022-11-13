#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME (128)
#define MAX_LINE (1024)
#define FILE_OPENING_ERROR (-1)
#define ALLOCATION_ERROR (-2)

struct _elements;
typedef struct _elements* EPosition;
struct _polynominal;
typedef struct _polynominal* PPosition;

typedef struct _elements {
	int coef;
	int exp;
	EPosition eNext;
}Elements;

typedef struct _polynominal {
	PPosition pNext;
	EPosition eNext;
}Polynominal;

int EnterFilename(char* filename);
int Menu(PPosition pHead);
int ExtractFromFile(PPosition pHead, char* filename);
int CreatePolynominal(PPosition pHead, char* buffer);
PPosition CreateNewPoly();
int AddPolyAtEnd(PPosition pHead, PPosition newPoly);
PPosition FindLast(PPosition pHead);
EPosition CreateNewElement(int coef, int exp);
int SortElement(PPosition Poly, EPosition Element);
int PrintPolynominals(PPosition pHead);
int DeleteAfter(EPosition pos);
int Merge(EPosition pos, EPosition newElement);
int CountPolynominals(PPosition pHead);
PPosition PolynominalAddition(PPosition Result, PPosition pHead, int pos);
PPosition MenuAddition(PPosition pHead);
PPosition PolynominalMultiplication(PPosition Result, PPosition pHead, int pos);
PPosition MenuMultiplication(PPosition pHead);
int PrintPolynominal(PPosition Result);
int Deallocation(PPosition pHead);


int main() {
	Polynominal Zeroth = { .pNext = NULL,.eNext = NULL };
	PPosition pHead = &Zeroth;
	char filename[MAX_NAME] = { 0 };
	int status = 2;

	EnterFilename(filename); //unos imena datoteke

	ExtractFromFile(pHead, filename); //cita polinome i stavlja ih u listu

	PrintPolynominals(pHead);

	Menu(pHead);

	status = Deallocation(pHead);
	if (status == 0)
		printf("\nDeallocation of memory is successful!\n");
	else
		printf("Deallocation ERROR\n");
	


	return EXIT_SUCCESS;
}


int EnterFilename(char* filename) {
	printf("Please enter file name: ");
	scanf(" %s", filename);

	return EXIT_SUCCESS;
}

int Menu(PPosition pHead) {
	int count = 0, poly = 0, choice = 0;
	PPosition Result = NULL;
	count = CountPolynominals(pHead);

	printf("\nChoose an action"
		"\n1)	Addition +"
		"\n2)	Multiplication *\n");
	scanf(" %d", &choice);
	switch (choice) {
	case(1):
		Result = MenuAddition(pHead);
		break;
	case(2):
		Result = MenuMultiplication(pHead);
		break;
	default:
		printf("\nWrong choice!\n");
	}

	return EXIT_SUCCESS;
}

PPosition MenuAddition(PPosition pHead) {
	int count = 0, poly = 0, choice = 0;
	PPosition Result = CreateNewPoly();
	count = CountPolynominals(pHead);

	printf("\nChoose a poynominal: ");
	scanf(" %d", &poly);
	while (choice != 2) {
		Result = PolynominalAddition(Result, pHead, poly);
		printf("\n1)	+"
			"\n2)	=\n");
		scanf(" %d", &choice);
		if (choice == 1) {
			printf("\nChoose a poynominal: ");
			scanf(" %d", &poly);
		}
		else if (choice == 2)
			break;
	}

	PrintPolynominal(Result);

	return Result;
}

PPosition MenuMultiplication(PPosition pHead) {
	int count = 0, poly = 0, choice = 0;
	PPosition Result = CreateNewPoly();
	count = CountPolynominals(pHead);
	Result->eNext->coef = 1;
	Result->eNext->exp = 0;

	printf("\nChoose a poynominal: ");
	scanf(" %d", &poly);
	while (choice != 2) {
		Result = PolynominalMultiplication(Result, pHead, poly);
		printf("\n1)	*"
			"\n2)	=\n");
		scanf(" %d", &choice);
		if (choice == 1) {
			printf("\nChoose a poynominal: ");
			scanf(" %d", &poly);
		}
		else if (choice == 2)
			break;
	}

	PrintPolynominal(Result);

	return Result;
}

int ExtractFromFile(PPosition pHead, char* filename) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	char buffer[MAX_LINE] = { 0 };

	if (!fp) {
		printf("\nFile can not open.");
		return FILE_OPENING_ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp); //cita jedan redak
		CreatePolynominal(pHead, buffer); //stvara taj polinom
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int CreatePolynominal(PPosition pHead, char* buffer) {
	int coef = 0, exp = 0, bytes = 0;
	PPosition newPoly = NULL;
	EPosition newElement = NULL;
	newPoly = CreateNewPoly(); //napravi novi i stavi ga na kraj (da se redaju)
	if (!newPoly) {
		printf("Allocation error!");
		return ALLOCATION_ERROR;
	}
	AddPolyAtEnd(pHead, newPoly); //po defaultu na kraj ide

	while (strlen(buffer) > 0) {
		if ((sscanf(buffer, "%d %d %n", &coef, &exp, &bytes)) == 2) { //ucitaj iz buffera
			if (coef != 0) { //glavni filter na pocetak
				newElement = CreateNewElement(coef, exp); //stvori novi element
				SortElement(newPoly, newElement); //odmah i sort i postavljanje veza
			}
		}
		buffer += bytes;
	}

	return EXIT_SUCCESS;
}

PPosition CreateNewPoly() {
	PPosition newPoly = NULL;
	EPosition ZeroElement = NULL; //nulti element

	newPoly = (PPosition)malloc(sizeof(Polynominal));
	if (!newPoly) {
		return ALLOCATION_ERROR;
	}

	ZeroElement = (EPosition)malloc(sizeof(Elements));  //KREIRANJE NULTOG ELEMENTA
	ZeroElement->coef = 0;
	ZeroElement->exp = 0;
	ZeroElement->eNext = NULL;

	newPoly->eNext = ZeroElement; //postavi pointer na neki nulti element (newpoly.enext je sad head elemenata za ovaj poly)

	return newPoly;
}

int AddPolyAtEnd(PPosition pHead, PPosition newPoly) {
	PPosition Last = NULL;
	Last = FindLast(pHead);

	newPoly->pNext = Last->pNext;
	Last->pNext = newPoly;

	return EXIT_SUCCESS;
}

PPosition FindLast(PPosition pHead) {
	PPosition TEMP = pHead;
	while (TEMP->pNext) {
		TEMP = TEMP->pNext;
	}
	return TEMP;
}

EPosition CreateNewElement(int coef, int exp) {
	EPosition newElement = NULL;
	newElement = (EPosition)malloc(sizeof(Elements));
	if (!newElement) {
		printf("\nAllocation error!");
		return ALLOCATION_ERROR;
	}

	newElement->coef = coef;
	newElement->exp = exp;
	newElement->eNext = NULL;

	return newElement;
}

int SortElement(PPosition Poly, EPosition Element) {
	EPosition TEMP = Poly->eNext; //ovo ti je Head element od ovog polinoma
	while (TEMP->eNext != NULL && TEMP->eNext->exp > Element->exp) {
		TEMP = TEMP->eNext;
	}
	Merge(TEMP, Element);

	return EXIT_SUCCESS;
}

int Merge(EPosition pos, EPosition newElement) { //radi dobro, ona od lani tvoja ima malo falinki
	int result = 0;

	if (pos->eNext == NULL && pos->coef == 0 && pos->exp == 0) {
		newElement->eNext = pos->eNext;
		pos->eNext = newElement;
	}
	else if (pos->eNext == NULL && pos->exp != newElement->exp) {
		newElement->eNext = pos->eNext;
		pos->eNext = newElement;
	}
	else if (pos->eNext->exp == newElement->exp) {
		result = pos->eNext->coef + newElement->coef;
		if (result == 0) {
			DeleteAfter(pos);
		}
		else {
			pos->eNext->coef = result;
		}
	}
	else {
		newElement->eNext = pos->eNext;
		pos->eNext = newElement;
	}

	return EXIT_SUCCESS;
}

int DeleteAfter(EPosition pos) {
	EPosition TEMP = NULL;

	TEMP = pos->eNext;
	pos->eNext = TEMP->eNext;
	free(TEMP);

	return 0;
}

int PrintPolynominals(PPosition pHead) {
	PPosition pTEMP = pHead->pNext;
	EPosition eTEMP = NULL;
	int i = 0;

	printf("Polynomials from the file");
	while (pTEMP) {
		printf("\np%d -->	", ++i); //vidi sta sam iskoristio hahahaha
		eTEMP = pTEMP->eNext->eNext;		//zato jer ptemp.enext je onaj nulti
		while (eTEMP) {
			printf("%dx^%d	", eTEMP->coef, eTEMP->exp);
			eTEMP = eTEMP->eNext;
		}
		pTEMP = pTEMP->pNext;
	}

	return EXIT_SUCCESS;
}

int CountPolynominals(PPosition pHead) {
	PPosition TEMP = pHead->pNext;
	int count = 0;
	while (TEMP) {
		TEMP = TEMP->pNext;
		count++;
	}
	return count;
}

PPosition PolynominalMultiplication(PPosition Result, PPosition pHead, int pos) {
	int count = 0;
	PPosition newPoly = NULL;
	EPosition newElement = NULL;
	PPosition temp = pHead;
	newPoly = CreateNewPoly();
	if (!newPoly) {
		printf("Allocation error!");
		return ALLOCATION_ERROR;
	}
	AddPolyAtEnd(pHead, newPoly);

	for (count = 0; count < pos; count++)
		temp = temp->pNext;

	EPosition head1 = Result->eNext;
	EPosition head2 = temp->eNext->eNext;

	EPosition i = NULL;
	EPosition j = NULL;

	for (i = head1; i != NULL; i = i->eNext) {
		for (j = head2; j != NULL; j = j->eNext)
		{
			newElement = CreateNewElement(i->coef * j->coef, i->exp + j->exp);
			if (newElement->coef != 0)
				SortElement(newPoly, newElement);
		}
	}

	return newPoly;
}

PPosition PolynominalAddition(PPosition Result, PPosition pHead, int pos) {
	int coef = 0, exp = 0, i = 0;
	PPosition newPoly = NULL;
	EPosition newElement = NULL;
	PPosition temp = pHead;
	newPoly = CreateNewPoly(); //napravi novi i stavi ga na kraj (da se redaju)
	if (!newPoly) {
		printf("Allocation error!");
		return ALLOCATION_ERROR;
	}
	AddPolyAtEnd(pHead, newPoly);

	for (i = 0; i < pos; i++)
		temp = temp->pNext;

	EPosition head1 = Result->eNext->eNext;
	EPosition head2 = temp->eNext->eNext;

	while (head1) {
		newElement = CreateNewElement(head1->coef, head1->exp);
		SortElement(newPoly, newElement);
		head1 = head1->eNext;
	}
	while (head2) {
		newElement = CreateNewElement(head2->coef, head2->exp);
		SortElement(newPoly, newElement);
		head2 = head2->eNext;
	}

	return newPoly;
}

int PrintPolynominal(PPosition Result) {
	EPosition TEMP = Result->eNext->eNext;

	while (TEMP) {
		printf("%dx^%d	", TEMP->coef, TEMP->exp);
		TEMP = TEMP->eNext;
	}

	return EXIT_SUCCESS;
}

int Deallocation(PPosition pHead)
{
	PPosition temp = pHead->pNext;
	while (temp->pNext) {
		while (temp->eNext->eNext)
		{
			DeleteAfter(temp->eNext);
		}

		DeletePoly(temp);
	}

	return EXIT_SUCCESS;
}

int DeletePoly(PPosition head)
{
	PPosition temp1 = head;
	PPosition temp2 = NULL;

	while (temp1->pNext)
	{
		temp2 = temp1->pNext;
		temp1->pNext = temp2->pNext;
		free(temp2);
	}


	return EXIT_SUCCESS;
}

