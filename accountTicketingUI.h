#ifndef ACCOUNTTICKETING_H_
#define ACCOUNTTICKETING_H_

#include"account.h"
#include"ticket.h"

/* The struct AccountTicketingData contains the following data
1.Address of the Account struct to acess it
2.An integer value representing the max size of the accounts
3.Address of the Ticket struct to acess it
4.An integer value representing the max size of the accounts
*/
struct AccountTicketingData
{
	struct Account* accounts; // array of accounts 
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array 

	struct Ticket* tickets; // array of tickets 
	const int TICKET_MAX_SIZE; // maximum elements for ticket array 
};
/* The function dosent recieves any parameters */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print statements for the table for other functions */
void displayAccountSummaryHeader();

/* The function recieves parameters of address for struct AccountTicketingData */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print out the value like account number, date of birth and account type */
/* The function loops over all the members of the struct and prints them if they are non zero*/
void displayAccountSummaryRecord();

/* The function dosent recieves any parameters */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print statements for the table for other functions */
void displayAccountDetailHeader();

/* The function recieves parameters of address for struct AccountTicketingData */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print out the value like account number, date of birth, account type, Income, name of country, userid, password, name of customer */
/* The function loops over all the members of the struct and prints them if they are non zero */
void displayAccountDetailRecord();

/* The function recieves parameters of struct AccountTicketingData */
/* It returns the value of type int */
/* This function is responsible for calling the main logic fucntion to enter the menu system */
/* It calls the function and sends all the value of the structs Account and ticket together as AccountTicketingData */
int applicationStartup();

/* The function recieves parameters of struct AccountTicketingData */
/* The function returns a value of type int */
/* The system asks for the user to enter 1 for login and 0 to exit */
/* The system ask the user to enter the account number , userid , password */
/* If all the 3 value matches excatly for the respective value in the struct the user goes into other function depends on the account type */
int menuLogin();

/* The function recieves parameters of struct AccountTicketingData and a particular account that we used to login to system */
/* The function dosent return any values its a void function */
/* The function displays a menu system and asks the user to input the an int of which he wants to enter */
/* Necessary logic is made to take valid input from the user */
/* Depending on the value enterd the system calls necessary logic to enter that particular menu system */
/* It loops untill the value enterd by the user is 0 */
void menuAgent();

/* The function recieves an intger value , address of the struct AccountTicketingData , an integer and address of an integer */
/* The function returns a value of type int */
/* The function loops over all the values of the struct and checks untill account number of the struct is equal to the account number sent to the function */
/* If found the function return correct value as the index of the account number found else it return -1 */
/* It loops untill the account number matches or the value of the loop is gretaer than a which is the max accounts in the struct */
int findAccountIndexByAccNum();

/* The function recieves address of the struct AccountticketingData and max size of the accounts */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print statements to call other functions to display records */
int displayAllAccountSummaryRecords();

/* The function recieves address of the struct AccountticketingData and max size of the accounts */
/* The function dosent return any value its of type void */
/* The purpose of this function is to print statements to call other functions to display records */
int displayAllAccountDetailsRecords();

/* The function dosent recieve any parameters its a void function */
/* The function dosent return any value its a void type */
/* The purpose of the function is to clear the input buffer print a statement anf wait untill user inputs the entet key */
void pauseExecution(void);

/* The function recieves parameters of struct AccountTicketingData and a particular account that we used to login to system */
/* The function return value of type of int */
/* The function displays a menu system and asks the user to input the an int of which he wants to enter */
/* Necessary logic is made to take valid input from the user */
/* Depending on the value enterd the system calls necessary logic to enter that particular menu system */
/* It loops untill the value enterd by the user is 0 */
int CustomerMenu();

/* The function recieves parameters of address for struct Account */
/* The function returns a value of type int */
/* The purpose of this function is to print out the value like account number, date of birth, account type, Income, name of country, userid, password, name of customer */
/* The function prints data of a particular account of that customer */
int displayCustomerDetails();

/* The function recieves address of the struct AccountTicketingData, address of the variable of type int and an integer */
/* The function returns a value of type int */
/* The purpose of the function is to promt user to enter the userlogin and password */
/* Necessary functions are called to take in valid input and other function is called to check for the userid and password in the stucts */
/* The function assigns the value 1 or -1 to the a depending on the value returned from other function */
int findusernamepassword();

/* The function dosent recieve any parameters its a void function */
/* The function returns the value of type int */
/* The purpose of the function is to display a few lines about the headings of the ticket */
int Ticketheader();

/*  The function recieves address of the struct AccountTicketingData */
/* The function return a value of type int */
/* The purpose of this function is to print the values of the ticket if the number of messages and the status is ==1 */
/* It loops over all the value and prints all the values that satisify the if statements */
/* It prints ticket number, account number, nameof the customer, ticketstatus, subject of the ticket and the number of the messages */
int TicketDisplaydetails();

/* The function dosent recieve any parameters its a void function */
/* The function returns a value of type 1 */
/* The purpose of the function is to print the output to display a message asking the user to input the ticket number */
int ticketentryheader();

/* The function dosent recieve any parameters its a void function */
/* The function returns a value of type int that us equal to the ticket number that user inputs if valid */
/* The purpose of the function is to take value from the user and check if the value is greater than 0 or not */
/* If true it returns the value else it will loop untill a valid value is enterd */
int getTicketnumber();

/* The parameters of the function are a value of type int that is the ticket number and address of the struct AccountTicketingData */
/* The function will return a value of type int that is the index at which the ticketnumber matches in the struct else it will return -1 if not found */
/* The function will loop over all the values of the ticket number in the struct and checks if it matches int a */
/* It loops untill it finds the matching value or the max size of the tickets */
int findticnumber();

/* The parameters of the function are sturct Ticket single index value */
/* The function returns a value of type int */
/* The purpose of the function is to print a heading with ticketnumber, Ticket status, subject of the ticket */
int foundticketheader();

/* The parameters of the function are sturct Ticket single index value */
/* The function returns a value of type int */
/* The purpose of this function is to loop over all the messages in the particular ticket passed to the function */
/* The function will display the wheather its a customer message or agent message and then name of the agent or customer who neterd the message and thent the message */
/* After every 5 messages we stop and ask user to input the enter value */
/* The for loops continues untill all the messages are comepleted displaying int the ticket */
int displaymessages();

/* The function dosent recieve any parameters its a void function */
/* The function return a value of type int */
/* The function is used to display the heading to display customer ticket details */
int customerticketheader();

/* The function recieves parameterf address of the struct ticket */
/* The function returns a value of type int */
/* The function loops over all the values of the ticket untill the for loop reaches the max tickets number */
/* The function displays the tickets that are active ticketstatus==1 */
/* The function displays account number, ticket number, ticket status, name of the customer, subject and the number of messages */
int displayallticketdetails();

/* The function recieves address of the struct AccountTicketingData and single account details as parameters */
/* The function returns a value of type int */
/* The function displays all the tickets that match the particualar account number to the account number in the tickets */
/* The function displays account number, ticket number, ticket status, name of the customer, subject and the number of messages */
int customerticketdetails();

/* The function recieves 2 strings username and password , address of the account struct, address of the value of type int and the index at which
   the accounts and username match */
   /* The function uses string library function strcmp to compare username and password in the account struct at the index d */
   /* If the values match then the values of c is 1 else the value is -1 */
int validateusernamepassword();

/* The function recieves parameters of a single member of the struct account */
/* The function return a value of type int */
/* The purpose of the function is to display the details of the particular account */
/* The purpose of this function is to print out the value like account number, date of birth, account type, Income, name of country, userid, password, name of customer */
int displayRemoveddetails();

/* The function recieves parameters as address of the struct ticket */
/* The function returns the value of type int */
/* The purpose of this function is to promt the user to change the subject of a particulat ticket passed to the struct */
/* Necessary functions are called to take a avlid input for the user */
int subjectmodification();

/* The function recieves parameters a address of the struct ticket */
/* The function returns the value of type int */
/* The function loops over all the vaues of the tickets and dislays details only if the ticket is closed tickernumber == 0 */
/* The functin displays ticketnumber, accountnumber, ticketstatus, subject, number of messages */
int displayclosedtickets();

/*  The function recieves parameters as address of the ticket struct and accounts stuct of a particular member */
/* The function returns a value of type int */
/* The function prompts the user to enter a message into the particular ticket */
/* The name of the customer and user type are used from the Account structs */
/* Necessary functions are called to enter the a valid message by the user and counter is incremented by 1 and message is stored in the struct */
int messagemodification();



#endif