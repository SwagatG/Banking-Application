//*****************************************************************************************
//  Program Filename	: Checking Account Program
//  Version				: 2.0
//  Author				: Swagat Ghimire
//  Purpose				: To provide basic banking functions
//  Date				: October 13 , 2015
//*****************************************************************************************

//Preprocessor Directives
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cstring>
#define FILE_IN "King.dat"	//easier to use infile
#define FILE_OUT "King.dat"	//easier to use outfile

using namespace std;
/*
	Account Number: 56897-2225678
	Password: W5tr@43 
*/

//Name Constant Definitions
class checking_account
{
	protected:
		char account_number[14]; //User's Account number used for login and such.
		double account_balance; //The money in the account
	public:
		void input_transaction(); //Used to make withdrawals or deposits
		void print_balance(); //Show the user the money currently in their account
};

class joint_account : public checking_account
{
	protected:
		char owner_ssn[12], joint_owner_ssn[12]; //Stores the users' ssn
	public:
	void print_ssn(); // show the user the owner and joint owner ssn
};

class account_owners : public joint_account
{
	private:
		char owner_name[20], joint_owner_name[20], password[8], inputAccNum[14], inputPassword[8]; // names, and login information
		ifstream inSecurity; // used to read from the binary file
		ofstream output; // used to write to the file
	public:
		bool correctInfo = false, correctPass = true, correctAccNum = true; //used to check if the login info is correct
		void get_info(); //Reads all data from file (once login constructor is successful)
		void outputInfo(); //Outputs data to file after all transactions are compelted
		
		//*****************************************************************************************
		// Function Name: account_owners
		// Purpose: constructor to gather login information.
		// Inputs to Function: None
		// Outputs from Function: None
		// External Inputs to Function: File: "King.dat"; cin of user's pass and acc num
		// External Outputs from Function: cout of prompts
		//*****************************************************************************************
		account_owners() //constructor
		{

			inSecurity.open(FILE_IN, ios::in|ios::binary); //open the connection
			if(!inSecurity ) //Ensure that the file is opened
			{
				cout << "Can't find input file " << FILE_IN << ".\n"; //If not, tell them there is no info
				exit;
			}
			else //If there is a file with data
			{ 
				inSecurity.read((char *) &account_number, sizeof(account_number)); //get account number and password
				inSecurity.read((char *) &password, sizeof(password));
				cout << "Welcome to Marauders Bank of Canada!\n"; // introductary statemetn
				for (int i = 4; i > 0; i --) //Give the user three tries after the first failed atttempt
				{
					"\nPlease enter your login information:\n"; //prompt for login info
					correctPass = true;
					correctAccNum = true;
					cout << "\tAccount Number: ";
					cin >> inputAccNum;
					cout << "\tPassword: ";
					cin >> inputPassword;
					for (int i = 0; i < 14; i++)
					{
						if (inputAccNum[i] != account_number[i])
						{
							correctAccNum = false;
						}
					}
					for (int i = 0; i < 8; i++)
					{
						if (inputPassword[i] != password[i])
						{
							correctPass = false;
						}
					}
					if (correctAccNum == true && correctPass == true) //if all the info is correct
					{
						correctInfo = true; //set this value to true (it is used in the main function)
						break; //exit this loop
					}
					else // if the login info they entered is incorrect
					{
						cout << "\nYour account number or password is incorrect.\n"; // tell them
						if (i > 2)
						{
							cout << "You have " << i - 1 << " tries remaining.\n"; // let them know how many tries they have left
						}
						else
						{
							cout << "You have 1 try remaining\n"; //singular "try" if there is 1 try left
						}
						system("Pause");
						system("CLS");
					}
				}
			}
			inSecurity.close(); //close connection
		}		
};

//*****************************************************************************************
// Function Name: print_ssn
// Purpose: To output the owner and joint owner ssn
// Inputs to Function: none
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: cout of prompts
//*****************************************************************************************
void joint_account::print_ssn()
{
	cout << "The Owner's SSN is:\t\t" << owner_ssn << endl; //show the owner's SSN
	cout << "The Joint Owner's SSN is:\t" << joint_owner_ssn << endl; //show the joint owner's SSN
	system ("Pause"); // pause the program so they can see until they wish to continue
}

//*****************************************************************************************
// Function Name: input_transaction
// Purpose: to allow the user to withdraw or deposit money
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: cin of user's choices
// External Outputs from Function: cout of prompts
//*****************************************************************************************
void checking_account::input_transaction()
{
	char transaction_type; //used to determine whether they want to deposit or whithdraw
	float transaction_amount; //amount to be withdrawn or deposited
	cout << "Would you like to make a withdrawal or a deposit?"; //prmopt for transaction type
	cout << "\n\t[D] Deposit\n\t[W] Withdrawal";
	do //ensure that the answer is valid
	{
		cout << "\nEnter your choice: "; //ask them for a choice
		cin >> transaction_type;
	} while(tolower(transaction_type) != 'd' && tolower(transaction_type) != 'w'); //until they choose a valid
	
	if (tolower(transaction_type) == 'd') //if they chose to deposit
	{
		cout << "\nHow much would you like to Deposit?\nEnter amount: $"; //ask for the amount to deposit
		cin >> transaction_amount;
		account_balance += transaction_amount; //add input amount to the balance
	}
	else //if they chose to withdraw
	{
		do
		{
			cout << "\nHow much would you like to Withdraw?\nEnter amount: $"; //ask for the amount to withdraw
			cin >> transaction_amount;
			if (transaction_amount > account_balance) //ensure that they have enough money to make the withdrawal
			{
				cout << "Insufficient Funds!\nYou have $" << std::fixed << setprecision(2) << account_balance << " in your account.";
				// if they don't have enough money, tell them and ask for a lower value
			}
		} while (transaction_amount > account_balance);// keep asking until they input a valid number
			account_balance -= transaction_amount; //whena  valid number is input, subtract it from the account balance
	}
}

//*****************************************************************************************
// Function Name: print_balance
// Purpose: to show the user their account number and bank balance
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: cout of information
//*****************************************************************************************	
void checking_account::print_balance()
{
	cout << "Account Number:\t\t" << account_number << endl; //Output their account number
	cout << "Current Balance:\t$" <<  std::fixed << setprecision(2) << account_balance << endl; //Output their account balance
	system("Pause"); //allow them to read this until they wish to continue
}

//*****************************************************************************************
// Function Name: get_info
// Purpose: To read information from the file
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: File: "King.dat"
// External Outputs from Function: None
//*****************************************************************************************
void account_owners::get_info()
{
	inSecurity.open(FILE_IN, ios::in|ios::binary); //open the connection
	inSecurity.read((char *) &account_number, sizeof(account_number)); //read all the information on the file
	inSecurity.read((char *) &password, sizeof(password));
	inSecurity.read((char *) &owner_name, sizeof(owner_name));
	inSecurity.read((char *) &joint_owner_name, sizeof(joint_owner_name));
	inSecurity.read((char *) &owner_ssn, sizeof(owner_ssn));
	inSecurity.read((char *) &joint_owner_ssn, sizeof(joint_owner_ssn));
	inSecurity.read((char *) &account_balance, sizeof(account_balance));
	inSecurity.close(); //close connection
}

//*****************************************************************************************
// Function Name: outputInfo
// Purpose: To store information in the "King.dat" records
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: output to file: "King.dat"
// External Outputs from Function: None
//*****************************************************************************************
void account_owners::outputInfo()
{
	output.open(FILE_OUT, ios::out|ios::binary); //open connection
	output.write((char *) &account_number, sizeof(account_number)); //write all the data to the file for later use
	output.write((char *) &password, sizeof(password));
	output.write((char *) &owner_name, sizeof(owner_name));
	output.write((char *) &joint_owner_name, sizeof(joint_owner_name));
	output.write((char *) &owner_ssn, sizeof(owner_ssn));
	output.write((char *) &joint_owner_ssn, sizeof(joint_owner_ssn));
	output.write((char *) &account_balance, sizeof(account_balance));
	output.close(); //close connection
}

//*****************************************************************************************
// Function Name: Title
// Purpose: To output a title after clearing the screen
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: output of the title
//*****************************************************************************************
void Title()
{
	system ("CLS"); //clear screen
	cout << "The Banking Program\n" << string(80,'_') << endl; //output a title
}

//*****************************************************************************************
// Function Name: Menu
// Purpose: To allow the user to choose between various options
// Inputs to Function: None
// Outputs from Function: char userChoice (to figure out what the user wants to do)
// External Inputs to Function: cin of the char userChoice
// External Outputs from Function: prompts to the user
//*****************************************************************************************
char Menu()
{
	char userChoice; //used to take in user's choice
	cout << "What would you like to do?\n"; //prompt user to choose what they wish to do
	cout << "\t[1] Make Whithdrawal or Deposit\n"; //list options
	cout << "\t[2] Show your current Balance\n";
	cout << "\t[3] Show the owners' SSN numbers\n";
	cout << "\t[0] Exit the Program\n";
	
	do
	{
		cout << "\nEnter your Decision: "; //prompt them to choose an option
		cin >> userChoice;	
	} while(userChoice != '0' && userChoice != '1' && userChoice != '2' && userChoice != '3'); //ensure that their choice is valid
	
	return userChoice; //return the user's choice to the main function
}
int main()
{
    //Variable Declarations:
    char menuChoice;
    //Program Fucntions
	account_owners userAccount; //used to store all the information; this asks them for their login info right away
	if (userAccount.correctInfo == true) //if their login information is correct
	{
		userAccount.get_info(); //Get their info from the file
		do
		{
			Title(); //after every loop clear screen and output title
			
			menuChoice = Menu(); //Get their choice from the menu
			switch (menuChoice) //Based off of their choice
			{
				case '1':	Title(); //If they chose 1, output the title again
							userAccount.input_transaction(); //Allow the user to deposit or withdraw a sum
							break;
				case '2':	Title(); //If they chose 2
							userAccount.print_balance();//Output their account balance
							break;
				case '3':	Title(); //if they chose 3
							userAccount.print_ssn(); //Show them their social security number.
							break;
			}
		} while (menuChoice != '0'); //Keep going until they choose 0 in the menu (exit case)
		userAccount.outputInfo();//write data to the file
	}
	else// if they fail to log in
	{
		cout << "You have been locked out of your account.\nPlease call your bank to gain access.\n"; //inform them
	}
    system("PAUSE");
    return 0;
}
//end function main

