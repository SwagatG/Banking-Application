//*****************************************************************************************
//  Program Filename	: Checking Account Program
//  Version				: 1.0
//  Author				: Swagat Ghimire
//  Purpose				: To provide basic banking functions
//  Date				: October 8, 2015
//*****************************************************************************************

//Preprocessor Directives
#include <iostream>
#include <iomanip>
using namespace std;

//Name Constant Definitions
class checking_account
{
	private:
		int account_number;
		float account_balance;
	public:
		void input_transaction();
		void print_balance();
		checking_account()
		{
			cout << "What is your Account Number?";
			do 
			{
					cout << "\nEnter 1000 - 9999: ";
					cin >> account_number;		
			} while (account_number < 1000 || account_number > 9999);
			
			cout << "\nWhat is your initial Account Balance?\n$";
			cin >> account_balance;
		}
};

void checking_account::input_transaction()
{
	char transaction_type;
	float transaction_amount;
	cout << "Would you like to make a withdrawal or a deposit?";
	cout << "\n\t[D] Deposit\n\t[W] Withdrawal";
	do
	{
		cout << "\nEnter your choice: ";
		cin >> transaction_type;
	} while(tolower(transaction_type) != 'd' && tolower(transaction_type) != 'w');
	
	if (tolower(transaction_type) == 'd')
	{
		cout << "\nHow much would you like to Deposit?\nEnter amount: $";
		cin >> transaction_amount;
		account_balance += transaction_amount;
	}
	else
	{
		do
		{
			cout << "\nHow much would you like to Withdraw?\nEnter amount: $";
			cin >> transaction_amount;
			if (transaction_amount > account_balance)
			{
				cout << "Insufficient Funds!\n";
			}
		} while (transaction_amount > account_balance);
			account_balance -= transaction_amount;
	}
}
	
void checking_account::print_balance()
{
	cout << "Account Number:\t\t" << account_number << endl;
	cout << "Current Balance:\t$" <<  std::fixed << setprecision(2) << account_balance << endl;
	system("Pause");	
}

void Title()
{
	system ("CLS");
	cout << "The Banking Program\n" << string(80,'_') << endl;
}

char Menu()
{
	char userChoice;
	cout << "What would you like to do?\n";
	cout << "\t[1] Make Whithdrawal or Deposit\n";
	cout << "\t[2] Show your current Balance\n";
	cout << "\t[0] Exit the Program\n";
	
	do
	{
		cout << "\nEnter your Decision: ";
		cin >> userChoice;	
	} while(userChoice != '0' && userChoice != '1' && userChoice != '2');
	
	return userChoice;
}
int main()
{
    //Variable Declarations:
    char menuChoice;
    //Program Fucntions
	Title();
	checking_account userAccount;
	
	do
	{
		Title();
		menuChoice = Menu();
		switch (menuChoice)
		{
			case '1':	Title();
						userAccount.input_transaction();
						break;
			case '2':	Title();
						userAccount.print_balance();
						break;
		}
	} while (menuChoice != '0');
	
    system("PAUSE");
    return 0;
}
//end function main

