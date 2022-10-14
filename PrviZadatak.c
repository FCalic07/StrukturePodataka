#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1024)
#define MAX_NAME (128)
#define ERROR (-1)
#define MAX_PTS (100)

struct Students;
typedef struct Students {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int points;
} student;

int CountStudents();
student* Allocation(int num, student* s);
void Printing(int num, student* s);
double RelativePoints(int pts);


int main() {
	student* studenti = NULL;
	int NumOfStudents = 0;
	/* pozvati funkciju koja racuna broj studenata u datoteci*/
	NumOfStudents = CountStudents();

	/* pozvati funkciju koja alocira i reda ih u strukturu*/
	studenti= Allocation(NumOfStudents,studenti);

	/*Pozvati funkciju da printa ovo*/
	Printing(NumOfStudents,studenti);

	return 0;
}

int CountStudents() {
	int count = 0;
	char buffer[MAX_SIZE] = { 0 };
	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");

	if (fp == NULL) {
		printf("File can not open!\n");
		return ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_SIZE, fp);
		/* da nije prazna linija
		ali se ne sjecam je li ovako ispravno zbog onog \r na linuxu ili sta vec*/
		if (strcmp(buffer,"\n") != 0)
			count++;
	}

	fclose(fp);
	return count;
}

student* Allocation(int num,student* s) {
	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");
	char buffer[MAX_SIZE] = { 0 };
	s = (student*)malloc(num * sizeof(student));

	if (fp == NULL) {
		printf("File can not open!\n");
		return ERROR;
	}

	int i = 0;
	while (!feof(fp)) {
		fgets(buffer, MAX_SIZE, fp);
		if (strcmp(buffer, "\n") != 0) {
			sscanf(buffer, "%s %s %d", s[i].name, s[i].surname, &s[i].points); /*ovo si mi ti spominjao i vid fakat radi*/
			i++;
		}
	}

	fclose(fp);
	return s;
}

void Printing(int num, student* s) {
	int i = 0;

	for (i = 0; i < num; i++)
		printf("\nIme i prezime:\t%s %s \nApsolutni i relativni bodovi:\t%d %lf\n",
			s[i].name, s[i].surname, s[i].points, RelativePoints(s[i].points));
}

double RelativePoints(int pts) {
	double RPts=0;
	return RPts = ((double)pts / (double)MAX_PTS) * 100;
}