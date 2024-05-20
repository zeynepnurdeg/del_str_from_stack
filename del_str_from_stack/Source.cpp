#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack_int.h"

void readFile(FILE* inp, stack_t* s) {
	SType temp[MAX];
	while (fscanf(inp, " %s", temp) != EOF)
		push(s, temp);
}

void displayStack(stack_t s) {
	if (!isEmptyS(&s)) {
		SType temp[MAX];
		strcpy(temp, pop(&s));
		displayStack(s);
		printf("%s ", temp);
	}
}

void deleteStr_ReverseStack(stack_t* s, stack_t* newS, char* str, int *check) {
	if (!isEmptyS(s)) {
		SType item[MAX];
		strcpy(item, pop(s));
		if (strcmp(item, str) != 0)
			push(newS, item);
		else
			*check = 1;
		deleteStr_ReverseStack(s, newS, str, check);
	}
}

int main(void)
{
	FILE* inp;
	inp = fopen("strings.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		stack_t words;
		initializeS(&words);

		stack_t reverse;
		initializeS(&reverse);

		readFile(inp, &words);
		fclose(inp);

		displayStack(words);

		SType delStr[MAX];
		printf("\n\nEnter a word to delete: ");
		scanf(" %s", delStr);

		int check = 0;
		deleteStr_ReverseStack(&words, &reverse, delStr, &check);

		if (check)
		{
			printf("\nString has been deleted\n");
			printf("Reverse of stack: \n");
			displayStack(reverse);
		}
		else
		{
			printf("\nEntered string doesnt exist\n");
			printf("Reverse of stack: \n");
			displayStack(reverse);
		}
		printf("\n");
	}
	return 0;
}