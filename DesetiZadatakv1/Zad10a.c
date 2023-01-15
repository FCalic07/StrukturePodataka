#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "filehandling.h"
#include "querry.h"

int Zadatak10a() {

	/*CITAJ IME FILEA             0*/
	/*OTVORI TAJ FILE             0*/
	/*CITAJ IZ FILEA IME_DRZAVE IME_DATOTEKE*/
	/*FORMIRAJ VEZANU LISTU TIH DRZAVA SA CVOROM STABLA*/
	/*.......OTVORI FILE GRADOVA
	* .......CITAJ IZ FILEA GRAD BROJ_ST
	*........U STABLO STAVLJAJ GRADOVE
	
	PRINTAJ DRZAVE - NJENE GRADOVE - BROJ STANOVNIKA

	IZVRSI UPIT
	*/
	CountryList Zeroth = { .country_name = {0},.Next = NULL,.Root = NULL };
	Position Head = &Zeroth;
	int status = 23;

	char filename[MAX_NAME] = { 0 };
	FILE* fp = NULL;
	int file_status = 0;

	printf("\nPlease enter the <states> filename\nFilename: ");
	scanf(" %s", filename);
	
	file_status = ReadStatesFromFile(Head, filename);
	if (file_status) {
		return FILE_OPENING_ERROR;
	}

	PrintAll(Head);

	CityQuerry(Head);

	//Dealokacija
	status = DeallocationList(Head);
	if (NULL == status) {
		printf("\nDeallocation successfull!");
	}
	else {
		printf("\nDeallocation unsuccessfull!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int PrintAll(Position Head) {
	Position Country = Head->Next;
	Branch City = NULL;

	while (Country) {
		printf("\n%s's cities found\n", Country->country_name);
		
		City = Country->Root;
		InorderPrint(City);
		
		Country = Country->Next;
	}

	return EXIT_SUCCESS;
}