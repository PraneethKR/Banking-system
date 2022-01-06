#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "commonHelpers.h"
#include"account.h"
#include<time.h>
// Uses the time.h library to obtain current year information // Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}
int getInteger()
{
	char c = 'x';
	int valid = 1;
	int v;

	do {
		scanf(" %d%c", &v, &c);


		if (c == '\n')

		{
			return v;
			valid = 1;
		}
		else
		{

			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
			valid = 0;
		}
	} while (valid != 1);

	return 1;

}
int getPositiveInteger()
{
	int a, valid = 0;

	do
	{
		scanf(" %d", &a);
		if (a > 0)
		{
			return a;
		}
		else printf("ERROR: Value must be a positive integer greater than zero: ");
	} while (valid != 1);
	return 1;
}
int getIntFromRange(int a, int b)
{

	int valid = 1;
	int v;
	do {
		char c = 'x';
		scanf("%d%c", &v, &c);


		if (c == '\n')
		{
			if (v >= a && v <= b)
			{
				return v;
				valid = 1;

			}
			else
			{
				printf("ERROR: Value must be between %d and %d inclusive: ", a, b);
				valid = 0;
			}
		}
		else
		{
			printf("ERROR: Value must be an integer: ");
			clearStandardInputBuffer();
			valid = 0;


		}
	} while (valid != 1);
	return 1;
}
double getDouble()
{
	char c = 'x';
	int valid = 1;
	double v;
	do
	{

		scanf("%lf%c", &v, &c);
		if (c == '\n')
		{
			valid = 1;

			return v;
		}
		else printf("ERROR: Value must be a double floating-point number: ");
		clearStandardInputBuffer();
		valid = 0;
	} while (valid != 1);
	return 1;
}
double getPositiveDouble()
{
	double a;
	int valid = 0;

	do
	{
		char c = 'x';
		scanf("%lf%c", &a, &c);
		if (c == '\n')
		{
			if (a > 0)
			{
				return a;
				valid = 1;

			}
			else

			{
				printf("ERROR: Value must be a positive double floating-point number: ");
				valid = 0;
			}
		}
		else
		{
			printf("ERROR: Value must be a double floating-point number: ");
			clearStandardInputBuffer();
			valid = 0;
		}
	} while (valid != 1);
	return 1;
}
char getCharOption(char* a)
{
	int valid = 0;
	int error = 0;
	int correct = 0;
	char letter;
	int i = 0;

	char letter1 = 'x';
	do {
		scanf(" %c%c", &letter, &letter1);
		if (letter1 == '\n')
		{
			for (i = 0; a[i] != '\0'; i++)
			{


				if (letter == a[i])
				{
					correct++;
				}

				else
					error++;




			}

			if (correct >= 1)
			{
				valid = 1;
				return letter;
			}
			else
			{
				printf("ERROR: Character must be one of [%s]: ", a);
			}
		}
		else {
			printf("ERROR: Character must be one of [%s]: ", a);

			clearStandardInputBuffer();
		}
	} while (valid != 1);
	return 1;
}
char getCString(char a[], int b, int c)
{
	int valid = 0;
	int x = 0;
	do {

		char temp[100];

		scanf(" %[^\n]s", temp);
		x = strlen(temp);
		if (x >= b && x <= c)
		{

			strcpy(a, temp);
			valid = 1;

		}
		else if (b == c && x != c)
		{
			printf("ERROR: String length must be exactly %d chars: ", b);
			x = 0;
			clearStandardInputBuffer();
		}
		else if (x > c)
		{
			printf("ERROR: String length must be no more than %d chars: ", c);
			x = 0;
			clearStandardInputBuffer();

		}
		else
		{
			printf("ERROR: String length must be between %d and %d chars: ", b, c);
			x = 0;

			clearStandardInputBuffer();
		}
	} while (valid != 1);
	return 1;
}
int getnoSpace(char name[], int length)
{
	int i = 0;
	for (i = 0; i <= length; i++)
	{
		if (name[i] != 32);
		else
		{
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			return -1;
		}
	}
	return 1;
}
int getsecuritypassword(char a[], int* A, int* b, int* c, int* d)
{
	int i = 0;
	int num = 0;
	int snum = 0;
	int bnum = 0;
	int symbol = 0;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] <= '9' && a[i] >= '0')
		{
			num++;
		}
		else if (a[i] >= 'a' && a[i] <= 'z')
		{
			snum++;
		}
		else if (a[i] >= 'A' && a[i] <= 'Z')
		{
			bnum++;
		}
		else if (a[i] == '!' || a[i] == '@' || a[i] == '#' || a[i] == '$' || a[i] == '%' || a[i] == '^' || a[i] == '&' || a[i] == '*')
		{
			symbol++;
		}
		*A = num;
		*b = snum;
		*c = bnum;
		*d = symbol;
	}
	return 1;
}
int errorpassword(int a, int b, int c, int d)
{
	if (a == 2 && b == 2 && c == 2 && d == 2)
	{
		return 1;
	}
	else {
		printf("SECURITY: Password must contain 2 of each:\n");
		printf("          Digit: 0-9\n");
		printf("          UPPERCASE character\n");
		printf("          lowercase character\n");
		printf("          symbol character: !@#$%%^&*\n");
		return -1;
	}
}
