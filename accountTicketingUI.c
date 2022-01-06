#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "account.h"
#include"accountTicketingUI.h"
#include "commonHelpers.h"
#include<ctype.h>
#include<string.h>
#define SIZE 5
// Pause execution until user enters the enter key void
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}
void displayAccountSummaryHeader()
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}
void displayAccountSummaryRecord(struct AccountTicketingData* account)
{
	int i = 0;
	for (i = 0; i < account->ACCOUNT_MAX_SIZE; i++)
	{

		if (account->accounts[i].acnumber != 0)
		{
			printf("%05d %-9s %5d\n", account->accounts[i].acnumber, account->accounts[i].type == 'A' ? "AGENT" : "CUSTOMER", account->accounts[i].demo.DOB);
		}
	}
}
void displayAccountDetailHeader()
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountDetailRecord(struct AccountTicketingData* account)
{
	int i = 0, z = 0;
	char password[20] = { 0 };
	for (z = 0; z < account->ACCOUNT_MAX_SIZE; z++)
	{
		strcpy(password, account->accounts[z].login.password);
		for (i = 1; i < 9; i += 2)
		{
			password[i] = '*';
		}

		if (account->accounts[z].acnumber)
		{
			printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %-8s\n", account->accounts[z].acnumber, account->accounts[z].type == 'A' ? "AGENT" : "CUSTOMER", account->accounts[z].demo.DOB, account->accounts[z].demo.HHIncome, account->accounts[z].demo.name, account->accounts[z].login.nameofcustomer, account->accounts[z].login.userlogin, password);
		}
	}

}
int findAccountIndexByAccNum(int accountnumber, struct  AccountTicketingData account[], int a, int* correct)
{
	int c = 0;
	int i = 0;
	int valid = 0;
	for (i = 0; i < a && valid == 0; i++)
	{
		if (accountnumber == account->accounts[i].acnumber)
		{
			c++;
			*correct = i;
			valid = 1;
		}
		else
		{
			*correct = -1;
		}

	}
	return 1;
}
int displayAllAccountSummaryRecords(struct AccountTicketingData* account, int a)
{
	printf("\n");
	displayAccountSummaryHeader();

	{
		displayAccountSummaryRecord(account);
	}
	printf("\n");
	return 1;
}
int displayAllAccountDetailsRecords(struct AccountTicketingData* account, int a)
{

	printf("\n");
	displayAccountDetailHeader();


	displayAccountDetailRecord(account);
	printf("\n");
	return 1;
}
int menuLogin(struct AccountTicketingData account[])
{

	int valid = 0;
	int selection;
	char c;
	int accountnumber;
	do {
		printf("==============================================\nAccount Ticketing System - Login\n==============================================\n1) Login to the system\n0) Exit application\n----------------------------------------------\n\n");
		printf("Selection: ");

		selection = getIntFromRange(0, 1);
		if (selection == 0)
		{
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			c = getCharOption("yYnN");
			if (c == 'n' || c == 'N')
			{
				printf("\n");
				valid = 0;
			}
			else if (c == 'y' || c == 'Y')
			{
				printf("\n==============================================\nAccount Ticketing System - Terminated\n==============================================\n");
				valid = 1;
			}
		}
		else if (selection == 1)
		{
			int correct = 0;
			int i = 3;
			int correct1 = 0;

			while (i > 0)
			{
				printf("\n");
				printf("Enter the account#: ");
				accountnumber = getInteger();
				findAccountIndexByAccNum(accountnumber, account, account->ACCOUNT_MAX_SIZE, &correct);
				findusernamepassword(account, &correct1, correct);
				if (correct >= 0 && correct1 == 1)
				{
					i = -1;
				}
				else
				{
					i--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", i);

				}
				if (i == 0)
				{
					printf("\nERROR:  Login failed!\n\n");
					pauseExecution();
				}
			}

			printf("\n");
			if (correct >= 0 && correct1 == 1)
			{
				if (account->accounts[correct].type == 'C')
				{
					CustomerMenu(account, account->accounts[correct], account->tickets);
				}
				else
				{
					menuAgent(account, account->accounts[correct]);
				}
			}
		}
	} while (valid == 0);
	return 1;
}
void menuAgent(struct AccountTicketingData accounts[], struct Account account)
{
	int size = accounts->ACCOUNT_MAX_SIZE - 1;

	int valid2 = 0;
	//printf("%d", size);
	int deletedtickets = 0;
	int deletedaccounts = 0;
	int deletedmessages = 0;
	int agentselection;
	do {
		//printf("%d", size);
		printf("AGENT: %s (%d)\n", account.login.nameofcustomer, account.acnumber);
		printf("==============================================\nAccount Ticketing System - Agent Menu\n==============================================\n");
		printf(" 1) Add a new account\n 2) Modify an existing account\n 3) Remove an account\n 4) List accounts: summary view\n 5) List accounts: detailed view\n----------------------------------------------\n 6) List new tickets\n 7) List active tickets\n 8) List closed tickets\n 9) Manage a ticket\n10) Archive closed tickets\n----------------------------------------------\n11) View archived account statistics\n12) View archived tickets statistics\n----------------------------------------------\n0) Logout\n\n");
		printf("Selection: ");
		agentselection = getIntFromRange(0, 12);
		if (agentselection == 0)
		{
			int p = 0;
			int accountsremaining = 0;
			printf("\nSaving session modifications...\n");
			int i = 0;

			FILE* fp;
			fp = fopen("ticket.txt", "w");
			int logtickets = 0;
			for (p = 0; p < accounts->TICKET_MAX_SIZE; p++)
			{
				if (accounts->tickets[p].ticketstatus == 1)
				{
					int i = 0;

					if (fp != NULL)
					{
						if (accounts->tickets[p].ticketnumber != 0)
						{
							fprintf(fp, "%d|%d|%d|%s|%d", accounts->tickets[p].ticketnumber, accounts->tickets[p].accountnoofticket, accounts->tickets[p].ticketstatus, accounts->tickets[p].messages, accounts->tickets[p].counter);
							for (i = 0; i < accounts->tickets[p].counter; i++)
							{
								fprintf(fp, "|%c|%s|%s", accounts->tickets[p].data[i].accountype, accounts->tickets[p].data[i].nameofcustomer, accounts->tickets[p].data[i].message);
							}
							logtickets++;
							if (p > 0 && p < accounts->TICKET_MAX_SIZE - 1)
							{
								fprintf(fp, "\n");
							}
						}
					}
				}
			}
			fclose(fp);
			FILE* fp1;
			fp1 = fopen("account.txt", "w");
			for (i = 0; i < accounts->ACCOUNT_MAX_SIZE; i++)
			{
				if (fp1 != NULL && accounts->accounts[i].acnumber != 0)
				{
					fprintf(fp1, "%d~%c~%s~%s~%s~%d~%lf~%s\n", accounts->accounts[i].acnumber, accounts->accounts[i].type, accounts->accounts[i].login.nameofcustomer, accounts->accounts[i].login.userlogin, accounts->accounts[i].login.password, accounts->accounts[i].demo.DOB, accounts->accounts[i].demo.HHIncome, accounts->accounts[i].demo.name);
					accountsremaining++;
				}
			}
			fclose(fp1);
			printf("   %d account saved.\n", accountsremaining);
			printf("   %d tickets saved.\n", logtickets);
			printf("### LOGGED OUT ###\n\n");
			valid2 = 1;
		}
		else if (agentselection == 1)
		{

			int index = -1;
			if (size < accounts->ACCOUNT_MAX_SIZE - 1)
			{
				size++;

				if (size < accounts->ACCOUNT_MAX_SIZE)
				{
					int i = 0;
					for (i = 0; i < accounts->ACCOUNT_MAX_SIZE && index == -1; i++)
					{
						if (accounts->accounts[i].acnumber == 0)
						{
							index = i;
						}
					}
					printf("\n");
					getselectedaccount(&accounts->accounts[index], accounts);
					getUserLogin(&accounts->accounts[index]);
					getDemographic(&accounts->accounts[index]);
					printf("*** New account added! ***\n\n");
					pauseExecution();
					printf("\n");
				}
			}
			else {
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
		}
		else if (agentselection == 2)
		{
			int accountnumber, correct = 0;
			printf("\n");
			printf("Enter the account#: ");
			accountnumber = getInteger();
			findAccountIndexByAccNum(accountnumber, accounts, accounts->ACCOUNT_MAX_SIZE, &correct);

			if (correct >= 0)
			{
				printf("\n");
				updateAccount(&accounts->accounts[correct]);
			}

		}
		else if (agentselection == 3)
		{
			int x;
			printf("\n");
			printf("Enter the account#: ");
			x = getInteger();
			if (account.acnumber == x)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else
			{
				int correct = 0;
				findAccountIndexByAccNum(x, accounts, accounts->ACCOUNT_MAX_SIZE, &correct);
				if (correct >= 0)
				{

					displayAccountDetailHeader();
					displayRemoveddetails(accounts->accounts[correct]);
					char c;
					printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
					c = getCharOption("YN");
					if (c == 'N')
					{
						printf("\n*** No changes made! ***\n\n");
						pauseExecution();
					}
					else
					{
						int i = 0;

						for (i = 0; i <= 17; i++)
						{
							if (accounts->tickets[i].accountnoofticket == accounts->accounts[correct].acnumber)
							{
								if (accounts->tickets[i].ticketstatus == 1)
								{
									accounts->tickets[i].accountnoofticket = 0;
									accounts->tickets[i].ticketnumber = 0;
								}
								else
								{
									deletedmessages += accounts->tickets[i].counter;
									archivetickets(accounts->tickets[i]);
									deletedtickets++;
									accounts->tickets[i].accountnoofticket = 0;
									accounts->tickets[i].ticketnumber = 0;
								}
							}
						}
						deletedaccounts++;
						archiveaccount(accounts->accounts[correct]);
						accounts->accounts[correct].acnumber = 0;

						printf("\n*** Account Removed! ***\n\n");
						size--;
						//printf("%d", size);
						pauseExecution();
					}
				}
			}
		}
		else if (agentselection == 4)
		{
			displayAllAccountSummaryRecords(accounts, size);
			pauseExecution();
		}
		else if (agentselection == 5)
		{
			displayAllAccountDetailsRecords(accounts, size);
			pauseExecution();
		}
		else if (agentselection == 6)
		{
			int ticketnumber = 0;
			int value = 0;
			do {
				printf("\n");
				Ticketheader();
				TicketDisplaydetails(accounts);
				ticketentryheader();
				ticketnumber = getTicketnumber();
				//printf("%d",ticketnumber);
				value = findticnumber(ticketnumber, accounts);
				if (ticketnumber != 0)
				{
					if (value >= 0)
					{
						foundticketheader(accounts->tickets[value]);
						displaymessages(accounts->tickets[value]);
						pauseExecution();
					}
					else
					{
						printf("\nERROR: Invalid ticket number.\n\n");
						pauseExecution();
					}
				}
				else
				{
					printf("\n");
				}
			} while (ticketnumber != 0);
		}
		else if (agentselection == 7)
		{
			int ticketnumber = 0;
			int value = 0;
			printf("\n");
			do
			{

				Ticketheader();
				displayallticketdetails(accounts->tickets);

				ticketentryheader();
				ticketnumber = getTicketnumber();
				value = findticnumber(ticketnumber, accounts);
				if (ticketnumber != 0)
				{
					if (value >= 0)
					{
						foundticketheader(accounts->tickets[value]);
						displaymessages(accounts->tickets[value]);
						printf("<< ENTER key to Continue... >>\n");
						printf("\n");
					}
					else
					{
						printf("\nERROR: Invalid ticket number.\n\n");
						printf("<< ENTER key to Continue... >>\n");
					}
				}
				else
				{
					printf("\n");
				}
			} while (ticketnumber != 0);
		}
		else if (agentselection == 8)
		{
			int ticketnumber = 0;
			int value = 0;

			do
			{
				printf("\n");
				Ticketheader();
				displayclosedtickets(accounts->tickets);
				ticketentryheader();
				ticketnumber = getTicketnumber();
				value = findticnumber(ticketnumber, accounts);
				if (ticketnumber != 0)
				{
					if (value >= 0)
					{
						foundticketheader(accounts->tickets[value]);
						displaymessages(accounts->tickets[value]);
						pauseExecution();
					}
					else
					{
						printf("\nERROR: Invalid ticket number.\n\n");
						pauseExecution();
					}

				}
			} while (ticketnumber != 0);
			printf("\n");
		}
		else if (agentselection == 9)
		{
			int ticketnumber = 0;
			int value = 0;
			printf("\n");
			printf("Enter ticket number: ");
			ticketnumber = getTicketnumber();
			//printf("%d",ticketnumber);
			printf("\n");
			value = findticnumber(ticketnumber, accounts);
			if (ticketnumber != 0)
			{
				if (value >= 0)
				{
					int valid = 0;
					do {
						printf("----------------------------------------\nTicket %06d - Update Options\n----------------------------------------\n", accounts->tickets[value].ticketnumber);
						printf("Status  : %s\n", accounts->tickets[value].ticketstatus == 1 ? "ACTIVE" : "CLOSED");
						printf("Subject : %s\n", accounts->tickets[value].messages);
						printf("Acct#   : %d\n", accounts->tickets[value].accountnoofticket);
						printf("Customer: %s\n", accounts->tickets[value].data->nameofcustomer);
						printf("----------------------------------------\n1) Add a message\n2) Close ticket\n3) Re-open ticket\n0) Done\nSelection: ");
						int selection = getIntFromRange(0, 3);
						printf("\n");
						if (selection == 1)
						{
							if (accounts->tickets[value].ticketstatus == 1)
							{
								messagemodification(&accounts->tickets[value], account);
								printf("\n");
							}
							else
							{
								printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
							}
						}
						else if (selection == 2)
						{
							if (accounts->tickets[value].ticketstatus == 1)
							{
								printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");

								char value1 = getCharOption("YN");
								if (value1 == 'Y')
								{
									accounts->tickets[value].ticketstatus = 0;
									char value2 = 0;
									printf("\n");
									if (accounts->tickets[value].counter < 20)
									{
										printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
										value2 = getCharOption("YN");
										if (value2 == 'Y')
										{
											printf("\n");
											messagemodification(&accounts->tickets[value], account);
											printf("\n*** Ticket closed! ***\n\n");
										}
										else
										{
											printf("\n*** Ticket closed! ***\n\n");
										}
									}
									else
									{
										printf("*** Ticket closed! ***\n\n");
									}
								}
								else
								{
									printf("\n");
								}
							}
							else
							{
								printf("ERROR: Ticket is already closed!\n\n");
							}
						}
						else if (selection == 3)
						{
							char i = 0;
							if (accounts->tickets[value].ticketstatus == 0)
							{
								printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
								i = getCharOption("YN");
								if (i == 'Y')
								{
									accounts->tickets[value].ticketstatus = 1;
									printf("\n*** Ticket re-opened! ***\n\n");
								}
								else
								{
									printf("\n");
								}
							}
							else
							{
								printf("ERROR: Ticket is already active!\n\n");
							}
						}
						else if (selection == 0)
						{
							valid = 1;
						}

					} while (valid == 0);
				}
				else
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
				}
			}

		}
		else if (agentselection == 10)
		{
			printf("\n");
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			char selection = 0;
			selection = getCharOption("YN");

			if (selection == 'Y')
			{

				int total = 0;
				int i = 0;
				for (i = 0; i < accounts->TICKET_MAX_SIZE; i++)
				{
					if (accounts->tickets[i].ticketstatus == 0 && accounts->tickets[i].ticketnumber != 0)
					{
						total++;
						archivetickets(accounts->tickets[i]);
						accounts->tickets[i].accountnoofticket = 0;
						accounts->tickets[i].ticketnumber = 0;
						deletedmessages += accounts->tickets[i].counter;
					}
				}
				deletedtickets += total;

				printf("\n*** %d tickets archived ***\n\n", total);
				pauseExecution();
			}
		}
		else if (agentselection == 11)
		{
			printf("\nThere are %d account(s) currently archived.\n\n", deletedaccounts);
			pauseExecution();
		}
		else if (agentselection == 12)
		{
			printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", deletedtickets, deletedmessages);
			pauseExecution();
		}
		else if (agentselection == 0)
		{
			valid2 = 1;
		}
	} while (valid2 == 0);
}
int applicationStartup(struct AccountTicketingData accounts[])
{

	menuLogin(accounts);
	return 0;
}
int CustomerMenu(struct AccountTicketingData ticket[], struct Account account, struct Ticket* tickets)
{
	int valid = 0, max1;
	max1 = ticket->TICKET_MAX_SIZE - 2;
	do {
		printf("CUSTOMER: %s (%d)\n", account.login.nameofcustomer, account.acnumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n2) Create a new ticket\n3) Modify an active ticket\n4) List my tickets\n----------------------------------------------\n0) Logout\n\n");
		printf("Selection: ");
		int selection = 0;
		selection = getIntFromRange(0, 4);
		printf("\n");
		if (selection == 1)
		{
			displayAccountDetailHeader();
			displayCustomerDetails(account);
			printf("\n");
			pauseExecution();
		}
		else if (selection == 2)
		{
			max1++;
			int i = 0;
			int index = -1;
			if (max1 < ticket->TICKET_MAX_SIZE)
			{
				for (i = 0; i < ticket->TICKET_MAX_SIZE && index == -1; i++)
				{
					if (tickets[i].ticketnumber == 0)
					{
						index = i;
					}
				}
				tickets[index].accountnoofticket = account.acnumber;
				tickets[index].counter = 0;
				tickets[index].ticketstatus = 1;
				tickets[index].data->accountype = account.type;
				int i = 0;
				for (i = 0; account.login.nameofcustomer[i] != '\0'; i++)
				{
					tickets[index].data->nameofcustomer[i] = account.login.nameofcustomer[i];
				}
				findhighestticketnumber(ticket, &ticket->tickets[index]);
				pauseExecution();
				printf("\n");
			}
			else
			{
				printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}


		}
		else if (selection == 3)
		{
			int ticketnumber = 0;
			int value = 0;
			printf("Enter ticket number: ");
			ticketnumber = getTicketnumber();
			value = findticnumber(ticketnumber, ticket);
			printf("\n");
			if (ticketnumber != 0)
			{
				if (value >= 0)
				{
					if (ticket->tickets[value].ticketstatus == 1)
					{
						if (account.acnumber == ticket->tickets[value].accountnoofticket)
						{
							int valid7 = 0;
							do {
								printf("----------------------------------------\nTicket %06d - Update Options\n----------------------------------------\n", ticket->tickets[value].ticketnumber);
								printf("Status  : %s\n", ticket->tickets[value].ticketstatus == 1 ? "ACTIVE" : "CLOSED");
								printf("Subject : %s\n----------------------------------------\n", ticket->tickets[value].messages);
								printf("1) Modify the subject\n2) Add a message\n3) Close ticket\n0) Done\nSelection: ");
								int selection1 = 0;
								selection1 = getIntFromRange(0, 3);
								printf("\n");
								if (selection1 == 0)
								{
									pauseExecution();
									valid7 = 1;
								}
								else if (selection1 == 1)
								{
									subjectmodification(&ticket->tickets[value]);
								}
								else if (selection1 == 2)
								{

									messagemodification(&ticket->tickets[value], account);
									printf("\n");
								}
								else if (selection == 3 && ticket->tickets[value].ticketstatus == 1)
								{
									char option = 0;
									char option1 = 0;
									printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
									option = getCharOption("YN");
									printf("\n");
									if (option == 'Y')
									{
										ticket->tickets[value].ticketstatus = 0;
										if (ticket->tickets[value].counter < 20)
										{
											printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
											option1 = getCharOption("YN");
											printf("\n");
											if (option1 == 'Y')
											{
												messagemodification(&ticket->tickets[value], account);

												printf("\n");
												printf("*** Ticket closed! ***\n\n");
												pauseExecution();
												printf("\n");
											}
											else
											{
												printf("*** Ticket closed! ***\n\n");
												pauseExecution();

											}
										}
										else
										{
											printf("*** Ticket closed! ***\n\n");
											pauseExecution();

										}
										valid7 = 1;
									}
								}
								else
								{
									printf("ERROR: Invalid ticket number - you may only acess your own tickets.\n\n");
									pauseExecution();
								}


							} while (valid7 != 1);
						}
						else
						{
							printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
							pauseExecution();
							printf("\n");
						}
					}
					else
					{
						printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
						pauseExecution();
						printf("\n");
					}
				}
				else
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					pauseExecution();
					printf("\n");
				}
			}


		}
		else if (selection == 4)
		{
			int ticketnumber;
			int value = 0;

			do
			{
				customerticketheader();
				customerticketdetails(ticket, account);
				printf("\n");
				ticketentryheader();
				ticketnumber = getTicketnumber();
				value = findticnumber(ticketnumber, ticket);
				if (ticketnumber != 0)
				{
					if (value >= 0)
					{
						if (account.acnumber == ticket->tickets[value].accountnoofticket)
						{
							foundticketheader(ticket->tickets[value]);
							displaymessages(ticket->tickets[value]);
							printf("<< ENTER key to Continue... >>\n");
							printf("\n");

						}
						else
						{
							printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
							pauseExecution();
							printf("\n");
						}


					}
					else
					{
						printf("\nERROR: Invalid ticket number.\n\n");
						pauseExecution();
						printf("\n");
					}
				}
				else
				{
					printf("\n");
				}
			} while (ticketnumber != 0);
		}
		else if (selection == 0)
		{
			int p = 0;
			int totaltickets = 0;
			printf("Saving session modifications...\n");
			FILE* fp = NULL;
			fp = fopen("ticket.txt", "w");
			for (p = 0; p < ticket->TICKET_MAX_SIZE; p++)
			{
				if (ticket->tickets[p].ticketnumber != 0)
				{

					int i = 0;

					if (fp != NULL)
					{
						fprintf(fp, "\n%d|%d|%d|%s|%d", ticket->tickets[p].ticketnumber, ticket->tickets[p].accountnoofticket, ticket->tickets[p].ticketstatus, ticket->tickets[p].messages, ticket->tickets[p].counter);
						for (i = 0; i < ticket->tickets[p].counter; i++)
						{
							fprintf(fp, "|%c|%s|%s", ticket->tickets[p].data[i].accountype, ticket->tickets[p].data[i].nameofcustomer, ticket->tickets[p].data[i].message);
						}
					}


					totaltickets++;
				}
			}
			fclose(fp);
			printf("   %d tickets saved.\n", totaltickets);
			printf("### LOGGED OUT ###\n\n");
			valid = 1;
		}
	} while (valid == 0);
	return 1;
}
int displayCustomerDetails(struct Account account)
{
	int i = 0;
	char password[10] = { 0 };
	strcpy(password, account.login.password);
	for (i = 1; i < 8; i += 2)
	{

		password[i] = '*';

	}
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %-8s\n", account.acnumber, account.type == 'A' ? "AGENT" : "CUSTOMER", account.demo.DOB, account.demo.HHIncome, account.demo.name, account.login.nameofcustomer, account.login.userlogin, password);
	return 1;
}
int findusernamepassword(struct AccountTicketingData account[], int* a, int b)
{
	char userlogin[100] = { 0 };
	char password[100] = { 0 };
	int user = 0;
	printf("User Login    : ");
	getCString(userlogin, 0, 100);
	printf("Password      : ");
	getCString(password, 0, 100);
	validateusernamepassword(userlogin, password, account->accounts, &user, b);
	*a = user;
	return 1;
}
int validateusernamepassword(char a[], char b[], struct Account account[], int* c, int d)
{
	int x = 20;
	int p = 20;
	x = strcmp(a, account[d].login.userlogin);
	p = strcmp(b, account[d].login.password);
	if (x == 0 && p == 0)
	{
		*c = 1;
	}
	else
	{
		*c = -1;
	}
	return 1;
}
int Ticketheader()
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	return 1;
}
int TicketDisplaydetails(struct AccountTicketingData ticket[])
{
	int i = 0;
	int valid = -1;
	for (i = 0; i < ticket->TICKET_MAX_SIZE; i++)
	{
		if (ticket->tickets[i].counter == 1 && ticket->tickets[i].ticketstatus == 1)
		{
			valid = i;
			printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket->tickets[valid].ticketnumber, ticket->tickets[valid].accountnoofticket, ticket->tickets[valid].data->nameofcustomer, ticket->tickets[valid].ticketstatus == 1 ? "ACTIVE" : "CLOSED", ticket->tickets[valid].messages, ticket->tickets[valid].counter);
		}
	}

	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
	return 1;
}
int ticketentryheader()
{
	printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
	return 1;
}
int getTicketnumber()
{
	int i;
	int valid = 0;
	do {
		scanf("%d", &i);
		if (i >= 0)
		{
			valid = 1;
		}
		else
		{
			printf("ERROR: Value must be positive or zero: ");
		}
	} while (valid == 0);
	return i;
}
int findticnumber(int a, struct AccountTicketingData ticket[])
{
	int i = 0;
	int valid = -1;

	for (i = 0; i < ticket->TICKET_MAX_SIZE && valid == -1; i++)
	{
		if (a == ticket->tickets[i].ticketnumber)
		{
			valid = i;
		}
		else
		{
			valid = -1;
		}
	}
	//printf("%d", a);
	return valid;
	//printf("%d",valid);
}
int foundticketheader(struct Ticket ticket)
{
	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticket.ticketnumber, ticket.ticketstatus == 1 ? "ACTIVE" : "CLOSED", ticket.messages);
	printf("================================================================================\n");
	return 1;
}
int displaymessages(struct Ticket ticket)
{
	int i = 0;

	for (i = 0; i < ticket.counter; i++)
	{
		if (ticket.counter > 4)
		{
			if (i != 0 && i % 5 == 0)
			{
				pauseExecution();
				if (i == 5)
				{
					printf("\n");
				}
			}
		}
		printf("%s (%s):\n", ticket.data[i].accountype == 'C' ? "CUSTOMER" : "AGENT", ticket.data[i].nameofcustomer);
		printf("   %s\n\n", ticket.data[i].message);

	}
	return 1;
}
int displayallticketdetails(struct Ticket ticket[])
{
	int i = 0;
	for (i = 0; i < 16; i++)
	{
		if (ticket[i].ticketstatus == 1)
		{
			if (ticket[i].ticketnumber != 0 && ticket[i].accountnoofticket != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket[i].ticketnumber, ticket[i].accountnoofticket, ticket[i].data->nameofcustomer, ticket[i].ticketstatus == 1 ? "ACTIVE" : "CLOSED", ticket[i].messages, ticket[i].counter);
			}
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
	return 1;
}
int customerticketheader()
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
	return 1;
}
int customerticketdetails(struct AccountTicketingData ticket[], struct Account account)
{
	int i = 0;
	for (i = 0; i < ticket->TICKET_MAX_SIZE && ticket->tickets->accountnoofticket != 0; i++)
	{
		if (account.acnumber == ticket->tickets[i].accountnoofticket)
		{
			printf("%06d %6s %-30s %5d\n", ticket->tickets[i].ticketnumber, ticket->tickets[i].ticketstatus == 1 ? "ACTIVE" : "CLOSED", ticket->tickets[i].messages, ticket->tickets[i].counter);
		}
	}
	printf("------ ------ ------------------------------ --------\n");
	return 1;
}
int subjectmodification(struct Ticket* account)
{
	printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
	getCString(account->messages, 0, 30);
	printf("\n");
	return 1;
}
int messagemodification(struct Ticket account[], struct Account accounts)
{
	if (account->counter < 20)
	{
		account->counter++;
		int i = account->counter;
		account->data[i - 1].accountype = accounts.type;

		strcpy(account->data[i - 1].nameofcustomer, accounts.login.nameofcustomer);


		printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(account->data[i - 1].message, 0, 150);
	}
	else
	{
		printf("ERROR: Message limit has been reached, call ITS Support!\n");
	}
	return 1;
}
int displayclosedtickets(struct Ticket* ticket)
{
	int i = 0;
	for (i = 0; i < 17; i++)
	{
		if (ticket[i].ticketstatus == 0 && ticket[i].accountnoofticket != 0)
		{
			printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket[i].ticketnumber, ticket[i].accountnoofticket, ticket[i].data->nameofcustomer, ticket[i].ticketstatus == 1 ? "ACTIVE" : "CLOSED", ticket[i].messages, ticket[i].counter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
	return 1;
}
int displayRemoveddetails(struct Account account)
{
	char password[9] = { 0 };
	int i = 0;
	strcpy(password, account.login.password);
	for (i = 1; i < 9; i += 2)
	{
		password[i] = '*';
	}

	if (account.acnumber)
	{
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %-8s\n", account.acnumber, account.type == 'A' ? "AGENT" : "CUSTOMER", account.demo.DOB, account.demo.HHIncome, account.demo.name, account.login.nameofcustomer, account.login.userlogin, password);
	}
	return 1;
}



