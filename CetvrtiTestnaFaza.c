#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE (1024)
#define FILE_OPENING_ERROR (-1)
#define MAX_NAME (128)
#define ALLOCATION_ERROR (-1)

struct _polynominal;
struct _elements;
typedef struct _elements* EPosition;
typedef struct _polynominal* PPosition;

typedef struct _elements {
	int coef;
	int exp;
	EPosition elNext;
}Element;

typedef struct _polynominal {
	PPosition pNext;
	EPosition elNext;
}Poly;

int EnterFilename(char* filename);
int ExtractFromFile(PPosition pHead, char* filename);
int CreatePoly(PPosition pHead, char* buffer);
PPosition FindLast(PPosition pHead);
int AddAfterPoly(PPosition pos1, PPosition pos2);
int CreateElement(PPosition Poly, int coef, int exp);
EPosition FindLastElement(PPosition Poly);
int AddAfterElement(EPosition pos1, EPosition pos2);

int main() {
	//prvo stvorit nulti polinom
	Poly Zeroth = { .pNext = NULL,.elNext = NULL };
	PPosition pHead = &Zeroth;
	char filename[MAX_NAME] = { 0 };

	EnterFilename(filename); //ime datoteke

	ExtractFromFile(pHead, filename); //ova funkcija sluzi da preko nje sve iz datoteke ide u listu
	 
	//da bi dokazao da mi radi napravio sam samo ovu funkciju
	/*necu lagat, malo ponosan na sebe sto sam skonto ovo,
	doduse sto jest jest ruzno je pa sad treba ic ka dekadenciji*/
	PrintPolynominalList(pHead);

	return EXIT_SUCCESS;
}

int EnterFilename(char* filename) {
	printf("\nPlease enter the file name: ");
	scanf(" %s", filename);

	return EXIT_SUCCESS;
}

int ExtractFromFile(PPosition pHead, char* filename) {
	FILE* fp;
	fp = fopen(filename, "r");
	char buffer[MAX_LINE] = { 0 };
	
	if (!fp) {
		printf("\nFile can not open!");
		return FILE_OPENING_ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);	//cita redak i stavlja u buffer
		CreatePoly(pHead, buffer);	//stvori polinom
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int CreatePoly(PPosition pHead, char* buffer) {
	PPosition Last = NULL;
	PPosition newPoly = NULL;

	int coef = 0;
	int exp = 0;
	int bytes = 0;
	int value = 0;
	newPoly = (PPosition)malloc(sizeof(Poly)); //prvo stvorit i alocirat
	if (!newPoly) {
		printf("\nAllocation error.");
		return ALLOCATION_ERROR;
	}
	//sad treba napravit njegov nulti element
	EPosition newElement = NULL;
	newElement = (EPosition)malloc(sizeof(Element));
	newElement->coef = 0;
	newElement->exp = 0;
	newElement->elNext = NULL;
	newPoly->elNext = newElement;

	Last = FindLast(pHead); //nalazi zadnji, klasika
	AddAfterPoly(Last, newPoly);//ide zadnje uvijek jer takvim redom ih kupi


	//sad imamo poly -> treba citat iz buffera i stvarat element listu koja se veže za ovaj poly
	while (strlen(buffer) > 0) {
		sscanf(buffer, "%d %d %n", &coef, &exp, &bytes);
		CreateElement(newPoly, coef, exp); //kreiraj element
		buffer += bytes;
	}


	return EXIT_SUCCESS;
}

PPosition FindLast(PPosition pHead) {
	PPosition TEMP = pHead;

	while (TEMP->pNext) {
		TEMP = TEMP->pNext;
	}
	return TEMP;
}

int AddAfterPoly(PPosition pos1, PPosition pos2) {
	pos2->pNext = pos1->pNext;
	pos1->pNext = pos2;
	return EXIT_SUCCESS;
}

int CreateElement(PPosition Poly, int coef, int exp) {
	EPosition LastElement = NULL;
	EPosition newElement = NULL;
	newElement = (EPosition)malloc(sizeof(Element)); //kreiraj alociraj
	if (!newElement) {
		printf("\nAllocation error.");
		return ALLOCATION_ERROR;
	}
	//unos brojeva
	newElement->coef = coef;
	newElement->exp = exp;
	newElement->elNext = NULL;

	//isto dodaj na kraj/
	LastElement = FindLastElement(Poly); //Last element ovog pHeada naravno
	AddAfterElement(LastElement, newElement); //zbog ovog mora imat nulti element svaki poly

	return EXIT_SUCCESS;
}

EPosition FindLastElement(PPosition Poly) {
	EPosition temp = Poly->elNext;
	while (temp->elNext) { 
		temp = temp->elNext;
	}
	return temp;
}

int AddAfterElement(EPosition pos1,EPosition pos2) { /*jer ako nema onda pos1 u prvom slucaju ovo pozivanje je nemoguce zbog nullptr odnosno pos1 nema nikakve alocirane varijable*/
	pos2->elNext = pos1->elNext;
	pos1->elNext = pos2;
	return EXIT_SUCCESS;
}

int PrintPolynominalList(PPosition pHead) {
	PPosition temp1 = pHead->pNext;
	EPosition temp2 = NULL;
	int i = 1;
	while (temp1){
		printf("\n%d. -->	", i);
		temp2 = temp1->elNext->elNext;   //caka je u tom što prilicno vjerujem da mora imat nulti element
		while (temp2) {
			printf("coef: %d exp: %d	", temp2->coef, temp2->exp);
			temp2 = temp2->elNext;
		}
		i++;
		temp1 = temp1->pNext;
	}

	return EXIT_SUCCESS;
}