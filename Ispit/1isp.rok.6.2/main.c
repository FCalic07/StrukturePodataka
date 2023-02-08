#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN (128)

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int Subject1;
	int Subject2;
	int Subject3;
	StudentP Next;
}Student;

int ReadFromFile(StudentP head, char* filename);
StudentP CreateStudent(char* fname, char* lname, int grade, int file);
int InsertAfter(StudentP head, StudentP new);
int Merge(StudentP head4, StudentP head);
StudentP Insert(StudentP P, StudentP Q);
int PrintList(StudentP head);

int main() {
	Student Zeroth1 = { .firstName = {0},.lastName = {0},.Next = NULL,.Subject1 = 0,.Subject2 = 0,.Subject3 = 0 };
	Student Zeroth2 = { .firstName = {0},.lastName = {0},.Next = NULL,.Subject1 = 0,.Subject2 = 0,.Subject3 = 0 };
	Student Zeroth3 = { .firstName = {0},.lastName = {0},.Next = NULL,.Subject1 = 0,.Subject2 = 0,.Subject3 = 0 };
	Student Zeroth4 = { .firstName = {0},.lastName = {0},.Next = NULL,.Subject1 = 0,.Subject2 = 0,.Subject3 = 0 };
	StudentP head1 = &Zeroth1;
	StudentP head2 = &Zeroth2;
	StudentP head3 = &Zeroth3;
	StudentP head4 = &Zeroth4;

	ReadFromFile(head1, "Subject1.txt");
	ReadFromFile(head2, "Subject2.txt");
	ReadFromFile(head3, "Subject3.txt");
	
	Merge(head4, head1);
	Merge(head4, head2);
	Merge(head4, head3);

	PrintList(head4);

	return EXIT_SUCCESS;
}

int ReadFromFile(StudentP head, char* filename) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	char fname[MAX_NAME_LEN] = { 0 };
	char lname[MAX_NAME_LEN] = { 0 };
	int grade = 0, file = 0;
	StudentP new = NULL;

	if (filename == "Subject1.txt")
		file = 1;
	else if (filename == "Subject2.txt")
		file = 2;
	else if (filename == "Subject3.txt")
		file = 3;


	while (!feof(fp)) {

		if (fscanf(fp, " %s %s %d", fname, lname, &grade) == 3) {
			new = CreateStudent(fname, lname, grade, file);
			InsertAfter(head, new);
		}

	}

	fclose(fp);

	return EXIT_SUCCESS;
}

StudentP CreateStudent(char* fname, char* lname, int grade, int file) {
	StudentP new = NULL;

	new = (StudentP)malloc(sizeof(Student));

	strcpy(new->firstName, fname);
	strcpy(new->lastName, lname);
	if (file == 1) {
		new->Subject1 = grade;
		new->Subject2 = 1;
		new->Subject3 = 1;
	}
	else if (file == 2) {
		new->Subject1 = 1;
		new->Subject2 = grade;
		new->Subject3 = 1;
	}
	else if (file == 3) {
		new->Subject1 = 1;
		new->Subject2 = 1;
		new->Subject3 = grade;
	}
	new->Next = NULL;

	return new;
}

int InsertAfter(StudentP head, StudentP new) {
	
	new->Next = head->Next;
	head->Next = new;

	return EXIT_SUCCESS;
}

int Merge(StudentP head4, StudentP head) {
	StudentP temp = head->Next;

	while (temp) {
		head4->Next = Insert(head4->Next, temp);
		temp = temp->Next;
	}

	return EXIT_SUCCESS;
}

int PrintList(StudentP head) {
	StudentP temp = head->Next;

	while (temp) {
		printf("\n- %s %s (%d, %d, %d)", temp->lastName, temp->firstName, temp->Subject1, temp->Subject2, temp->Subject3);
		temp = temp->Next;
	}

	return EXIT_SUCCESS;
}

StudentP Insert(StudentP P, StudentP Q) {
	if (NULL == P) {
		StudentP new = CreateStudent(Q->firstName, Q->lastName, 1, 1);
		new->Subject1 = Q->Subject1;
		new->Subject2 = Q->Subject2;
		new->Subject3 = Q->Subject3;
		return new;
	}
	else if (strcmp(P->firstName, Q->firstName) == 0 && strcmp(P->lastName, Q->lastName) == 0) {
		P->Subject1 = P->Subject1 + Q->Subject1 - 1;
		P->Subject2 = P->Subject2 + Q->Subject2 - 1;
		P->Subject3 = P->Subject3 + Q->Subject3 - 1;
		return P;
	}
	else
		P->Next = Insert(P->Next, Q);

	return P;
}