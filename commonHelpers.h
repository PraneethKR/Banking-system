#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

/* The function dosent recieve any parameters its a void function */
/* The function returns an integer of value current year */
/* It used system function to caluculate the current time and year and then return that value */
int currentYear(void);

/* The function dosent recieve any parameters its a void function */
/* The function dosent return any value its a void type */
/* The purpose of this function is to clear the keyboard buffer and print a message */
/* Wait for the user untill he press the enter key ad exit the function */
void clearStandardInputBuffer(void);

/* The function dosent recieve any parameters its a void function */
/* The function return an integer type of value that is enterd by the use if it meets all the specifications */
/* The purpose of the function is to check if the enterd value is an integer or not if true it returns the value */
/* If not true it will keep on the do loop untill user enters the correct value */
int getInteger();

/* The function dosent recieve any parameters its a void function */
/* The function return an integer type of value that is enterd by the use if it meets all the specifications */
/* The purpose of the function is to check if the enterd value is an integer or not */
/* It then checks if the enter value is greater than 0 or not if true returns value */
/* If not true it will keep on the do loop untill user enters the correct value */
int getPositiveInteger();

/* The function dosent recieve any parameters its a void function */
/* The function return an double type of value that is enterd by the use if it meets all the specifications */
/* The purpose of the function is to check if the enterd value is an decimal pont value or not if true it returns the value */
/* If not true it will keep on the do loop untill user enters the correct value */
double getDouble();

/* The function dosent recieve any parameters its a void function */
/* The function return an double type of value that is enterd by the use if it meets all the specifications */
/* The purpose of the function is to check if the enterd value is a decimal or not */
/* It then checks if the enter value is greater than 0 or not if true returns value */
/* If not true it will keep on the do loop untill user enters the correct value */
double getPositiveDouble();

/* The function recieves 2 parameters of type int then specify the range at which the fucntion is set */
/* The function return an integer if the value that is entered by the user if it meets all the specifications */
/* The purpose of this function is to check if the entered value is in the given range or not  if true return the value */
/*  If not true it will keep on the do loop untill user enters the correct value */
int getIntFromRange();

/* The function recieves a pointer to the variable of type char.The function checks if the user entered variable is in the given range of charaters */
/* The function returns a character if the input meets the speific requirements */
/* The function take in input only if the user input is a single charater and type char */
/* The purpose of this function is to check if the entered value is in the given range or not  if true return the value */
/*  If not true it will keep on the do loop untill user enters the correct value */
char getCharOption();

/* The function recieves a string.The function checks if the user entered charaters length is in the given range or not */
/* The function will return a value 1 */
/* The function take in input from the user and checks if the entered value length */
/* The purpose of this function is to check if the entered string is in the length given range or not  if true return the value */
/* If not true it will keep on the do loop untill user enters the correct value */
char getCString();

/* The function recieves a string.The function checks if the user entered string has any spaces or not ASCII integer value is 32 */
/* The function returns an integer value. The function will return -1 if it finds any space or 1 if there are no spaces */
/* The function loops over every charater in the string untill it finds '\0' and checks if it is a space and displays an error message and exits he function */
int getnoSpace();

/* The function recieves a string and address of the 4 integer values */
/* The function does not return any value return 1 on exit */
/* The function checks if the given string is has exactly 2 upper case letters, 2 lower case letters, 2 integers that are positve and 2 special
   charaters that are in the given range of charaters */
   /* The function increments the value every time it matches a condition and when all the charaters in the string are checked it assigns the values to the integers
	  In the parameters */
int getsecuritypassword();

/* The function recieves 4 parameters of type int that are passed by value */
/* the funtion return 1 if true and -1 if false */
/* The purpose of this function is to check if all the passed int values are equal to 2 */
/* If true then 1 will be returned and exits the function else -1 will be returns and exits the function */
int errorpassword();

#endif  