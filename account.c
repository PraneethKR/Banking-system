#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"commonHelpers.h"
#include"account.h"
#include "ticket.h"
#include"accountTicketingUI.h"
#include <ctype.h>

char getAccount(struct Account* account)
{

	printf("Account Data: New Record\n");
	printf("----------------------------------------\n");
	accountnumberheader();
	account->acnumber = getInteger();
	accounttypeheader();
	account->type = getCharOption("AC");
	printf("\n");
	return 1;
}
int getUserLogin(struct Account* account)
{
	char userlogin[11];
	int login_valid = 0;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	do
	{
		loginheader();
		getCString(userlogin, 0, 10);
		int sucessfull = getnoSpace(userlogin, strlen(userlogin));
		if (sucessfull != -1)
		{
			
			strcpy(account->login.userlogin, userlogin);
			login_valid = 1;
		}

	} while (login_valid != 1);
	displaynameheader();
	getCString(account->login.nameofcustomer, 0, 30);
	int password_valid = 0;
	int num = 0, snum = 0, bnum = 0, symbol = 0;
	do
	{
		passwordheader();
		char protopassword[9];
		getCString(protopassword, 8, 8);
		getsecuritypassword(protopassword, &num, &snum, &bnum, &symbol);
		int x = errorpassword(num, snum, bnum, symbol);
		if (x == 1)
		{
			strcpy(account->login.password, protopassword);
			password_valid = 1;
		}
	} while (password_valid == 0);
	printf("\n");
	return 1;
}
char getDemographic(struct Account* account)
{
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	birthheader();
	int year = 0;
	int range = 0;
	int range1 = 0;
	int valid = 0;
	do {
		scanf("%d", &account->demo.DOB);
		year = currentYear();
		range = year - 110;
		range1 = year - 18;
		if (account->demo.DOB<range || account->demo.DOB>range1)
		{
			printf("ERROR: Value must be between 1911 and 2003 inclusive: ");
			valid = 0;
		}
		else valid = 1;
	} while (valid != 1);
	incomeHeader();
	account->demo.HHIncome = getPositiveDouble();
	countryheader();
	getCString(account->demo.name, 0, 30);
	int i = 0;
	for (i = 0; account->demo.name[i] != '\0'; i++)
	{
		account->demo.name[i] = toupper(account->demo.name[i]);
	}
	printf("\n");
	return 1;
}
void updateUserLogin(struct Account* login)
{
	int valid4 = 0, b;
	do {
		printf("User Login: %s - Update Options\n----------------------------------------\n", login->login.userlogin);
		printf("1) Display name (current value: %s)\n2) Password\n0) Done\nSelection: ", login->login.nameofcustomer);
		b = getIntFromRange(0, 2);
		printf("\n");
		if (b == 1)
		{
			displaynameheader();
			getCString(login->login.nameofcustomer, 0, 30);
			printf("\n");
		}
		else if (b == 2)
		{
			int password_valid = 0, i = 0;
			int num = 0, snum = 0, bnum = 0, symbol = 0;
			do
			{
				passwordheader();
				char protopassword[9];
				getCString(protopassword, 8, 8);
				getsecuritypassword(protopassword, &num, &snum, &bnum, &symbol);
				int x = errorpassword(num, snum, bnum, symbol);
				if (x == 1)
				{
					for (i = 0; protopassword[i] != '\0'; i++)
					{
						login->login.password[i] = protopassword[i];
					}
					password_valid = 1;
				}
			} while (password_valid == 0);
			printf("\n");
		}
		else
		{
			valid4 = 1;
		}
	} while (valid4 == 0);
}
void updateDemographic(struct Account* demo)
{
	int x;
	int valid5 = 0; int i = 0;
	do {
		for (i = 0; demo->demo.name[i] != '\0'; i++)
		{
			demo->demo.name[i] = toupper(demo->demo.name[i]);
		}
		printf("Demographic Update Options\n----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n2) Country (current value: %s)\n0) Done\n", demo->demo.HHIncome, demo->demo.name);
		printf("Selection: ");
		x = getIntFromRange(0, 2);
		printf("\n");
		if (x == 1)
		{
			incomeHeader();
			demo->demo.HHIncome = getPositiveDouble();
			printf("\n");
		}
		else if (x == 2)
		{
			countryheader();
			getCString(demo->demo.name, 0, 30);
			for (i = 0; demo->demo.name[i] != '\0'; i++)
			{
				demo->demo.name[i] = toupper(demo->demo.name[i]);
			}
			printf("\n");
		}
		else if (x == 0)
		{
			valid5 = 1;
		}
	} while (valid5 == 0);
}
void updateAccount(struct Account* account)
{
	int x;
	int valid3 = 0;
	do {
		printf("Account: %d - Update Options\n----------------------------------------\n", account->acnumber);
		printf("1) Update account type (current value: %c)\n", account->type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		x = getIntFromRange(0, 3);
		printf("\n");
		if (x == 1)
		{
			accounttypeheader();
			account->type = getCharOption("AC");
			

		}
		else if (x == 2)
		{
			updateUserLogin(account);
		}
		else if (x == 3)
		{

			updateDemographic(account);
		}
		else if (x == 0)
		{
			valid3 = 1;
		}
	} while (valid3 == 0);
}
int getselectedaccount(struct Account* account, struct AccountTicketingData* accounts)
{

	account->acnumber = getAccountNumber(account, accounts);
	printf("New Account Data (Account#:%d)\n", account->acnumber);
	printf("----------------------------------------\n");
	accounttypeheader();
	account->type = getCharOption("AC");
	printf("\n");
	return 1;
}
int  findhighestticketnumber(struct AccountTicketingData* accounts, struct Ticket* account)
{


	account->ticketnumber = getticketnumber(accounts, account);
	printf("New Ticket (Ticket#:%06d)\n", account->ticketnumber);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(account->messages, 0, 30);
	printf("\n");
	printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(account->data->message, 0, 150);
	account->counter++;
	printf("\n*** New ticket created! ***\n\n");
	return 1;
}
int getticketnumber(struct AccountTicketingData* accounts, struct Ticket* account)
{
	int i = 0;

	for (i = 0; i < 9; i++)
	{

		if (accounts->tickets[i].ticketnumber != 0)
		{


			if (account->ticketnumber < accounts->tickets[i].ticketnumber)
			{
				account->ticketnumber = accounts->tickets[i].ticketnumber;
			}


		}
	}
	return account->ticketnumber + 1;
}
int getAccountNumber(struct Account* account, struct AccountTicketingData* accounts)
{
	int i = 0;
	for (i = 0; i <= accounts->ACCOUNT_MAX_SIZE; i++)
	{
		if (accounts->accounts[i].acnumber != 0)
		{


			if (account->acnumber < accounts->accounts[i].acnumber)
			{
				account->acnumber = accounts->accounts[i].acnumber;
			}


		}
	}

	//printf("%d",account->acnumber);
	return account->acnumber + 1;
}
void loginheader()
{
	printf("Enter user login (10 chars max): ");
}
void accounttypeheader()
{
	printf("Enter the account type (A=Agent | C=Customer): ");
}
void countryheader()
{
	printf("Enter the country (30 chars max.): ");
}
void incomeHeader()
{
	printf("Enter the household Income: $");
}
void passwordheader()
{
	printf("Enter the password (must be 8 chars in length): ");
}
void displaynameheader()
{
	printf("Enter the display name (30 chars max): ");
}
void birthheader()
{
	printf("Enter birth year (current age must be between 18 and 110): ");
}
void accountnumberheader()
{
	printf("Enter the account number: ");
}
