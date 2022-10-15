#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)
#define MAX_NAME (128)
#define ERROR_FILE_PROBLEM (-1) //treba izbjegavati ovakve reserved (tipa ERROR,auto,case,const......) rijeci
#define MAX_PTS (100)

struct _students; //praksa je prvo ovako sa ovim "_" i malim slovom
typedef struct _students {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int points;
} Student; //Onda ovdje veliko slovo jer je ovo zapravo ime strukture, pa ono kao ime poc.vel.slovom

int CountStudents(char* fname);
Student* Allocation(int num, Student* s, char* fname);
int Printing(int num, Student* s); // NE SMIJU SE KORISTITI VOID FUNKCIJE NA OVOM PREDMETU, MORA VRACATI NESTO BAR 0 ILI NULL
double RelativePoints(int pts);


int main() {
	Student* studenti = NULL;
	int NumOfStudents = 0;
	char name_buffer[MAX_NAME] = { 0 };
	char* file_name = 0;
	file_name = &name_buffer;
	/*Gledajuci tvoj kod od prosle godine cini mi se da i treba se ime datoteke prenosit
	pa nek ono pita korisnika kako se zove on ukuca tipa studenti.txt i odradi se sve*/
	printf("\nEnter file name: ");
	gets_s(name_buffer, MAX_NAME); /*isto ko i scanf jel jer moram svakako na pokazivac prebacivat, kako zelis*/

	/* pozvati funkciju koja racuna broj studenata u datoteci*/
	NumOfStudents = CountStudents(file_name);

	/* pozvati funkciju koja alocira i reda ih u strukturu*/
	studenti = Allocation(NumOfStudents, studenti, file_name);

	/*Pozvati funkciju da printa ovo*/
	Printing(NumOfStudents, studenti);

	return EXIT_SUCCESS; // u mainu je dobro koristiti EXIT_SUCCESS jer on obavlja jos neke provjere pri izlazu iz maina
}

int CountStudents(char* fname) {
	int count = 0;
	char buffer[MAX_SIZE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("File can not open!\n");
		return ERROR_FILE_PROBLEM;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_SIZE, fp);
		/* da nije prazna linija
		ali se ne sjecam je li ovako ispravno zbog onog \r na linuxu ili sta vec*/
		if (strcmp("\n", buffer) != 0) // dobro je ali strcmp provjerava desni argument sa prvim pa je ovaj moj logicniji poredak
			count++;
	}

	fclose(fp);
	return count;
}

Student* Allocation(int num, Student* s, char* fname) {
	FILE* fp = NULL;
	fp = fopen(fname, "r");
	char buffer[MAX_SIZE] = { 0 };
	s = (Student*)malloc(num * sizeof(Student));
	int i = 0; //ovo je c,a ne c++ pa bi sve deklaracije i inicijalizacije trebale biti na vrhu funkcije, no u vecini slucajeva moze i onako kako si ti

	if (fp == NULL) {
		printf("File can not open!\n");
		return ERROR_FILE_PROBLEM;
	}


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (!s) //moras provjeriti je li uspjesna alokacija   (pametno)
	{
		printf("Greska alokacije\n");
		return NULL;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	while (!feof(fp)) {
		 fscanf(fp,"%s %s %d", s[i].name, s[i].surname, &s[i].points);
		 i++;    /*da da, lakse ovo, nez sto sam mislio da fscanf ce uzet nesto iz prazne linije pf*/
	}

	fclose(fp);
	return s;
}


//ne smije se koristiti void
int Printing(int num, Student* s) {
	int i = 0;

	for (i = 0; i < num; i++)
		printf("\nIme i prezime:\t%s %s \nApsolutni i relativni bodovi:\t%d %.2lf\n",//zaokruzivanje na 2 decimale
			s[i].name, s[i].surname, s[i].points, RelativePoints(s[i].points));
	return EXIT_SUCCESS;
}

double RelativePoints(int pts) {
	double RPts = 0;
	RPts = ((double)pts / (double)MAX_PTS) * 100; //bolje je obaviti prvo izracun pa onda return da vraca vec izracunatu vrijednost 
	return RPts;
}
