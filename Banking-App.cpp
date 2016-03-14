//*****************************************************************************************
//  Program Filename	: Checking Account Program
//  Version				: 3.1
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
#include <vector>
#include <time.h>
#define FILE_IN "Information.dat"	//easier to use infile
#define FILE_OUT "Information.dat"	//easier to use outfile

using namespace std;
const string Month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct MonthlyTransaction
{
	char description[20];
	double amount;
};

/*
	Account Number: 56897-2225678
	Password: W5tr@43 
*/

class checking_account
{
	protected:
		char account_number[14]; //User's Account number used for login and such.
		double account_balance; //The money in the account
		vector <MonthlyTransaction> Bills;
		vector <double> transactions; // used to store transactions over past month
		double lastBalance; //used to show start value of account prior to transactions of the month
		int month, year;
	public:
		void input_transaction(); //Used to make withdrawals or deposits
		void print_balance(); //Show the user the money currently in their account
		void title_date(); //output title with the date
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
		int correctInfo = 0, correctPass = 1, correctAccNum = 1; //used to check if the login info is correct
		void get_info(); //Reads all data from file (once login constructor is successful)
		void outputInfo(); //Outputs data to file after all transactions are compelted
		void editBills();
		void changeMonth();
		void showMonthBills();
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
					correctPass = 1;
					correctAccNum = 1;
					cout << "\tAccount Number: ";
					cin >> inputAccNum;
					cout << "\tPassword: ";
					cin >> inputPassword;
					for (int j = 0; j < 14; j++)
					{
						if (inputAccNum[j] != account_number[j])
						{
							correctAccNum = 0;
						}
					}

					for (int j = 0; j < 8; j++)
					{
						if (inputPassword[j] != password[j])
						{
							correctPass = 0;
						}
					}
					if (correctAccNum == 1 && correctPass == 1) //if all the info is correct
					{
						correctInfo = 1; //set this value to true (it is used in the main function)
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

void account_owners::editBills()
{
	MonthlyTransaction newBill;
	char isCorrect;
	int userChoice, editChoice;
	
	title_date();
	
	cout << "Editing Bills:\nPlease Select one of the below choices\n\t";
	cout << "[1] - Add A Transaction\n\t[2] - Edit/Remove An Existing Transaction\n\t[3] - Cancel";
	do
	{
		cout << "\nPlease enter your selection: ";
		cin >> userChoice;
	} while (userChoice != 1 && userChoice != 2);
	
	title_date();
	
	if (userChoice == 1)
	{
		cout << "\nNEW MONTHLY TRANSACTION:\n\n";
		do
		{
			cout << "\nPlease describe the transaction (20 Characters or less):\n";
			cin >> newBill.description;
			cout << "Please enter the value of the transaction (negative for payments):\n";
			cin >> newBill.amount;
			cout << "Is the above information correct?\n\t[y] - Yes, Continue\n\t[n] - No, Edit";
			do
			{
				cout << "\nPlease enter your selection: ";
				cin >> isCorrect;
			}while (isCorrect !='y' && isCorrect != 'n');
		} while (isCorrect != 'y');
		
		Bills.push_back(newBill);
		cout << "The transaction has been added to your list of transactions.\n";
		system("Pause");
	}
	else if (userChoice == 2)
	{
		title_date();
		
		cout <<  setiosflags(ios::left) << setw(10) << "Bill #" <<setw(30) << "Bill Name" << setw(20) << "Amount" << endl;
		for (int i = 0; i < Bills.size(); i++)
		{
			cout << setw(10) << i + 1 << setw(30) << Bills[i].description << setw(20) << Bills[i].amount << endl;
		}
		
		cout << endl << "To edit a transaction, enter it's number. To delete a bill, enter '0'\n";
		
		do
		{
			cout << "Enter your selection: ";
			cin >> userChoice;
		} while (userChoice < 0 || userChoice > Bills.size());
		
		if (userChoice == 0)
		{
			title_date();
		
			cout <<  setiosflags(ios::left) << setw(10) << "Bill #" <<setw(30) << "Bill Name" << setw(20) << "Amount" << endl;
			for (int i = 0; i < Bills.size(); i++)
			{
				cout << setw(10) << i + 1 << setw(30) << Bills[i].description << setw(20) << Bills[i].amount << endl;
			}
			
			cout << endl << "To delete a transaction, enter it's number. To delete all transactions, enter '0'\n";
		
			do
			{
				cout << "Enter your selection: ";
				cin >> userChoice;
			} while (userChoice < 0 || userChoice > Bills.size());
			
			if (userChoice == 0)
			{
				title_date();
				cout << "Are you sure you want to DELETE ALL TRANSACTIONS?\n";
				do
				{
					cout << "Enter 'y' to delete, or 'n' to cancel: ";
					cin >> isCorrect;
				} while (isCorrect != 'n' && isCorrect != 'y');
				if (isCorrect == 'y')
				{
					while (Bills.size() > 0)
					{
						Bills.pop_back();
					}
				}
			}
			else
			{
				newBill = Bills[userChoice-1];
				Bills[userChoice-1] = Bills[Bills.size() - 1];
				Bills[Bills.size() - 1] = newBill;
				Bills.pop_back();
			}	
		}
		else
		{
			title_date();
			cout << "EDITTING MONTHLY TRANSACTIONS\n\n";
			cout << "Transaction Description: " << Bills[userChoice-1].description << endl << "Amount: " << Bills[userChoice-1].amount << endl;
			cout << "\n What would you like to edit?\n\t[1] - Description\n\t[2] - Amount\n\t[3] - Cancel Edit";
			do
			{
				cout << "\nEnter Selection: ";
				cin >> isCorrect;
			}while (isCorrect != '1' && isCorrect != '2' && isCorrect != '3');
			if (isCorrect == '1')
			{
				cout << "Enter new Description (20 Characters): ";
				cin >> Bills[userChoice-1].description;
			}
			else if (isCorrect == '2')
			{
				cout << "Enter new Amount (Negative for Bills): $";
				cin >> Bills[userChoice-1].amount;
			}
		}
	}
}

void account_owners::changeMonth()
{
	int numMonths, numYears, remMonths;
	float savingsInterest = 0.001, debtInterest = 0.015;
	double MonthlyIncome = 0, newBalance;
	char seeInfo;
	
	while (transactions.size() > 0)
	{
		transactions.pop_back();
	}
	
	for (int i = 0; i < Bills.size(); i++)
	{
		MonthlyIncome += Bills[i].amount;
	}
		
	title_date();
	do
	{
		cout << "Enter the number of months that have passed (Positive): " << endl;
		cin >> numMonths;
	} while (numMonths < 0);
	remMonths = numMonths;
	cout << "Would you like to see a month by month summary of funds?" << endl;
	do
	{
		cout << "Enter 'y' to see a summary, or 'n' to skip ahead: ";
		cin >> seeInfo;
	} while (seeInfo != 'y' && seeInfo != 'n');
	if (seeInfo == 'y')
	{
		for (int i = 0; i < numMonths; i++)
		{
			month += 1;
			if (month == 12)
			{
				year += 1;
				month = 0;
			}
			title_date();
			cout <<"Monthly Income/Expense Summary:\n\n";
			cout << setw(30) << "Description" << setw(21) << "Amount" << endl;
			cout << setw(30) << "INITIAL BALANCE" << "$" << setw(20) << std::fixed << setprecision(2) << account_balance << endl;
			
			for (int j = 0 ; j < Bills.size(); j++)
			{
				cout << setw(30) << Bills[j].description << "$" << setw(20) << std::fixed << setprecision(2) << Bills[j].amount << endl;
			}
			newBalance = account_balance + MonthlyIncome;
			cout << endl << setw(30) << "AFTER MONTHLY TRANSACTIONS" << "$" << setw(20) << std::fixed << setprecision(2) << newBalance << endl;
			
			if (newBalance >= 0)
			{
				cout << setw(30) << "INTEREST ON SAVINGS" << "$" << setw(20) << std::fixed << setprecision(2) << newBalance * savingsInterest << endl;
				newBalance += (newBalance * savingsInterest);
			}
			else
			{
				cout << setw(30) << "INTEREST ON SAVINGS" << "$" << setw(20) << std::fixed << setprecision(2) << newBalance * debtInterest << endl;
				newBalance += (newBalance * debtInterest);	
			}
			cout << endl << setw(30) << "AFTER INTEREST" << "$" << setw(20) << std::fixed << setprecision(2) << newBalance << endl;			
			account_balance = newBalance;
			remMonths -= 1;
			if (remMonths > 0)
			{
				do
				{
					cout << "Enter 'y' to see next month's summary, or 'n' to skip to end: ";
					cin >> seeInfo;
				} while (seeInfo != 'y' && seeInfo != 'n');
				if (seeInfo == 'n')
				{
					i = numMonths + 1;
				}
			}
		}
	}
	if (remMonths > 0)
	{
		if ((month + remMonths) > 11)
		{
			numYears = (month + remMonths) / 12;
			year += numYears;
			month = (month + remMonths) % 12;
		}
		else
		{
			month += remMonths;
		}
		for (int i = 0; i < remMonths; i++)
		{
			newBalance = account_balance + MonthlyIncome;
			if (newBalance >= 0)
			{
				account_balance = newBalance * (1 + savingsInterest);
			}
			else
			{
				account_balance = newBalance * (1 + debtInterest);
			}
			lastBalance = account_balance;
		}
	}
	system("Pause");
}

void account_owners::showMonthBills()
{
	double monthlyIncome = 0, netDeposits = 0, runningBalance = lastBalance;
	title_date();
	cout << setiosflags(ios::left) << setw(30) << "Description" << " " << setw(20) << "Amount" << endl;
	cout << setw(30) << "STARTING BALANCE" << "$" << std::fixed << setprecision(2) << setw(20) << lastBalance << endl << endl;
	
	for (int i = 0; i < transactions.size(); i++)
	{
		if (transactions[i] < 0)
		{
			cout << setw(30) << "Withdrawal" << "$" << setw(20) << std::fixed << setprecision(2) << transactions[i] << endl;
		}
		else if (transactions[i] > 0)
		{
			cout << setw(30) << "Deposit" << "$" << setw(20) << std::fixed << setprecision(2) << transactions[i] << endl;
		}
		runningBalance += transactions[i];
		netDeposits += transactions[i];
	}
	cout << endl << setw(30) << "NET DEPOSITS/WITHDRAWALS" << "$" << std::fixed << setprecision(2) << setw(20) << netDeposits << endl;
	cout << setw(30) << "AFTER DEPOSITS/WITHDRAWALS" << "$" << std::fixed << setprecision(2) << setw(20) << runningBalance << endl << endl;
	
	for (int i = 0; i < Bills.size(); i++)
	{
		cout << setw(30) << Bills[i].description << "$" << setw(20) << std::fixed << setprecision(2) << Bills[i].amount << endl;
		runningBalance += Bills[i].amount;
		monthlyIncome += Bills[i].amount;
	}
	cout << endl << setw(30) << "TOTAL MONTHLY TRANSACTIONS" << "$" << std::fixed << setprecision(2) << setw(20) << monthlyIncome << endl;
	cout << setw(30) << "AFTER MONTHLY TRANSACTIONS" << "$" << std::fixed << setprecision(2) << setw(20) << runningBalance << endl << endl;
	
	system("Pause");
}

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
		transactions.push_back(transaction_amount);
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
			transactions.push_back(-1 * transaction_amount);
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
// Function Name: title_Date
// Purpose: to output a title with the date (fiticious date)
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: cout of information
//*****************************************************************************************	
void checking_account::title_date()
{
	system ("CLS"); //clear screen
	cout << "The Banking Program\n" << string(80,'_') << endl; //output a title
	cout << Month[month] << ", " << year << endl;	
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
	MonthlyTransaction tempBill;
	int numBills, numTransactions;
	double tempTransaction;
	inSecurity.open(FILE_IN, ios::in|ios::binary); //open the connection
	inSecurity.read((char *) &account_number, sizeof(account_number)); //read all the information on the file
	inSecurity.read((char *) &password, sizeof(password));
	inSecurity.read((char *) &owner_name, sizeof(owner_name));
	inSecurity.read((char *) &joint_owner_name, sizeof(joint_owner_name));
	inSecurity.read((char *) &owner_ssn, sizeof(owner_ssn));
	inSecurity.read((char *) &joint_owner_ssn, sizeof(joint_owner_ssn));
	inSecurity.read((char *) &account_balance, sizeof(account_balance));
	inSecurity.read((char *) &numBills, sizeof(numBills));
	if (!inSecurity.eof())
	{
		while (numBills > 0)
		{
			inSecurity.read((char *) &tempBill, sizeof(MonthlyTransaction));
			Bills.push_back(tempBill);
			numBills --;
		}
		inSecurity.read((char *) &numTransactions, sizeof(numTransactions));
		while (numTransactions > 0)
		{
			inSecurity.read((char *) &tempTransaction, sizeof(tempTransaction));
			transactions.push_back(tempTransaction);
			numTransactions --;
			cout << "Test\n";
		}
		cout << "Test\n";
		inSecurity.read((char *) &lastBalance, sizeof(lastBalance));
		inSecurity.read((char *) &month, sizeof(month));
		inSecurity.read((char *) &year, sizeof(year));				
		cout << "Test\n";
	}
	else
	{
		time_t currTime = time(NULL);
		struct tm *aTime = localtime(&currTime);
		month = aTime->tm_mon; // Month is 0 - 11
		year = aTime->tm_year + 1900; // Year is # years since 1900	
		lastBalance = account_balance;	
	}
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
	int sizeofBills = Bills.size();
	int sizeofTransactions = transactions.size();
	
	output.open(FILE_OUT, ios::out|ios::binary); //open connection
	output.write((char *) &account_number, sizeof(account_number)); //write all the data to the file for later use
	output.write((char *) &password, sizeof(password));
	output.write((char *) &owner_name, sizeof(owner_name));
	output.write((char *) &joint_owner_name, sizeof(joint_owner_name));
	output.write((char *) &owner_ssn, sizeof(owner_ssn));
	output.write((char *) &joint_owner_ssn, sizeof(joint_owner_ssn));
	output.write((char *) &account_balance, sizeof(account_balance));
	output.write((char *) &sizeofBills, sizeof(sizeofBills));
	for (int i = 0; i < Bills.size(); i++)
	{
		output.write((char *) &Bills[i], sizeof (MonthlyTransaction));
	}
	output.write((char *) &sizeofTransactions, sizeof(sizeofTransactions));
	for (int i = 0; i < transactions.size(); i++)
	{
		output.write((char *) &transactions[i], sizeof (double));
	}
	output.write((char *) &lastBalance, sizeof(lastBalance));
	output.write((char *) &month, sizeof(month));
	output.write((char *) &year, sizeof(year));	
	output.close(); //close connection
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
	cout << "\t[4] Show This Month's Transactions\n";
	cout << "\t[5] Show and Edit Monthly Transactions\n";
	cout << "\t[6] Leave for a few months\n";
	cout << "\t[0] Exit the Program\n";
	
	do
	{
		cout << "\nEnter your Decision: "; //prompt them to choose an option
		cin >> userChoice;	
	} while(userChoice != '0' && userChoice != '1' && userChoice != '2' && userChoice != '3' && userChoice != '4' && userChoice != '5' && userChoice != '6'); //ensure that their choice is valid
	
	return userChoice; //return the user's choice to the main function
}
int main()
{
    //Variable Declarations:
    char menuChoice;
    //Program Fucntions
	account_owners userAccount; //used to store all the information; this asks them for their login info right away
	if (userAccount.correctInfo == 1) //if their login information is correct
	{
		userAccount.get_info(); //Get their info from the file
		do
		{
			userAccount.title_date(); //after every loop clear screen and output title
			
			menuChoice = Menu(); //Get their choice from the menu
			switch (menuChoice) //Based off of their choice
			{
				case '1':	userAccount.title_date(); //If they chose 1, output the title again
							userAccount.input_transaction(); //Allow the user to deposit or withdraw a sum
							break;
				case '2':	userAccount.title_date(); //If they chose 2
							userAccount.print_balance();//Output their account balance
							break;
				case '3':	userAccount.title_date(); //if they chose 3
							userAccount.print_ssn(); //Show them their social security number.
							break;
				case '4':	userAccount.title_date(); //if they chose 4
							userAccount.showMonthBills(); //Show the month's Transactions
							break;
				case '5':	userAccount.title_date(); //if they chose 5
							userAccount.editBills(); //Show/Edit Monthly Transactions.
							break;
				case '6':	userAccount.title_date(); //if they chose 6
							userAccount.changeMonth(); //Allow them to move a few months into the future.
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

