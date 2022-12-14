#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (256)
#define MAX_LINE (1024)
#define ALLOCATION_ERROR (-1)
#define FILE_OPENING_ERROR (-2)
#define POSTFIX_ERROR (-3)

struct _stack;
typedef struct _stack* Position;
typedef struct _stack {
	double number;
	Position Next;
} Stack;

int ReadFromFile(char* filename, Position Head);
int Push(double number, Position Head);
int Pop(Position Head);
int Operation(char operand, Position Head);
int DeleteAfter(Position pos);
int PrintPostfixResult(Position Head,int count);
int Deallocation(Position Head);

int main() {
	Stack Zeroth = { .number = 0,.Next = NULL };
	Position Head = &Zeroth;
	int status = 7;

	char filename[MAX_NAME] = { 0 };

	printf("\nFile name:	");
	scanf(" %s", filename);

	ReadFromFile(filename, Head);

	status = Deallocation(Head);
	if (status == 0)
		printf("\nDeallocation of memory is successful!\n");
	else
		printf("Deallocation ERROR\n");

	return EXIT_SUCCESS;
}

int ReadFromFile(char* filename, Position Head) {
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	int count = 1;

	fp = fopen(filename, "r");
	if (!fp) {
		printf("\nFile does not exist.");
		return FILE_OPENING_ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		ReadBuffer(buffer, Head);
		PrintPostfixResult(Head,count);
		count++;
		DeleteAfter(Head);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadBuffer(char* buffer, Position Head) {
	double number = 0;
	int bytes = 0;
	char operand = 0;

	while (strlen(buffer) > 0) {
		if (sscanf(buffer, " %lf %n", &number, &bytes) == 1) {
			Push(number, Head);
		}
		else if (sscanf(buffer, " %c %n", &operand, &bytes) == 1) {
			Operation(operand, Head);
		}
		buffer += bytes;
	}

	return EXIT_SUCCESS;
}

int Push(double number, Position Head) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Stack));
	if (!newElement) {
		printf("\nAllocation error!");
		return ALLOCATION_ERROR;
	}

	newElement->number = number;

	newElement->Next = Head->Next;
	Head->Next = newElement;

	return EXIT_SUCCESS;
}

int Operation(char operand, Position Head) {
	double num1 = 0, num2 = 0, result = 0;

	if (!Head->Next || !Head->Next->Next) {
		printf("Incorrect postfix expression!	1"); 
		return POSTFIX_ERROR;
	}

	num1 = Pop(Head);
	num2 = Pop(Head);

	switch (operand) {
	case '+':
		result = num2 + num1;
		break;
	case '-':
		result = num2 - num1;
		break;
	case '*':
		result = num2 * num1;
		break;
	case '/':
		result = num2 / num1;
		break;
	default:
		printf("Incorrect postfix expression!	2");
		return POSTFIX_ERROR;
	}

	Push(result, Head);

	return EXIT_SUCCESS;
}

int Pop(Position Head) {
	Position TEMP = Head->Next;
	double temp_number = TEMP->number;
	


	Head->Next = TEMP->Next;
	free(TEMP);

	return temp_number;
}

int PrintPostfixResult(Position Head,int count) {
	

	if (!Head->Next || Head->Next->Next) {
		printf("Incorrect postfix expression!	3");
		return POSTFIX_ERROR;
	}

	printf("\nResult of postfix expression %d.: %.2lf",count, Head->Next->number); //mala promjena u print, cisto ako ima vise izraza

	return EXIT_SUCCESS;
}

int DeleteAfter(Position pos) {
	Position TEMP = pos->Next;
	pos->Next = TEMP->Next;
	free(TEMP);

	return EXIT_SUCCESS;
}

int Deallocation(Position Head) {
	while (Head->Next)
		DeleteAfter(Head);

	Head = NULL;
	return EXIT_SUCCESS;
}
