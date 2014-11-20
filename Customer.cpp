#include "User.cpp"

class Customer: public User
{
	public:
	double savings;
	double chequing;
	
	public:
	Customer(string name, string ID)
	{
		userName = name;
		userID = ID;
		userType = "Cust";
		savings = 0.0;
		chequing = -1;
	}
	
	void printAccount()
	{
		ostringstream oss;

		string sav = "$";
		string cheq = "$";

		oss << fixed << setprecision(2) << savings;
		sav += oss.str();
		oss.str("");
		
		//If the current user has an account  in the negatives list checking account as not available 
		if (chequing == -1)
		{
			cheq = "N/A";
		}
		else //if not N/A user must have checking, therefore print value
		{
			oss << fixed << setprecision(2) << chequing;
			cheq += oss.str();
			oss.str("");
		}

		cout << "\nName: " << userName << setw(31 - userName.length()) << "UserID: " << userID << endl;
		cout << "Savings: " << sav << setw(30 - sav.length()) << "Chequing: " << cheq << endl;  
	}
	
	bool customerDeposit(int choice, float depositamount)
	{
    depositamount = floorf(depositamount * 100) / 100;
    if (depositamount <= 0)
    {
        cout << "Invalid amount." << endl;
        return false;
    }

    if (choice == 1)
    {
        savings += depositamount;
    }
    else if (choice == 2 && chequing != -1)
    {
        chequing += depositamount;
    }
    else if (choice == 2 && chequing == -1)
    {
        cout << "You do not have access to a chequing account" << endl;
        return false;
    }
    return true;
}

	//runs the menu for withdrawal options
	//implements the WARNING message if chequing accounts do not meet the $1000 threshold
	bool customerWithdrawal(int choice, float withdrawamount)
	{
		withdrawamount = floorf(withdrawamount * 100) / 100;
		
		if (withdrawamount <= 0)
		{
			cout << "Invalid Amount." << endl;
			return false;
		}

		if (choice == 1)
		{
			if (withdrawamount > savings)
			{
				cout << "Insufficient funds." << endl;
				return false;
			}
			else
			{
				savings -= withdrawamount;    
			}
		}
		else if (choice == 2 && chequing == -1)
		{
			cout << "You do not have access to a chequing account" << endl;
			return false;
		}
		else if (choice == 2 && chequing != -1)
		{
			if (withdrawamount > chequing)
			{
				cout << "Insufficient funds." << endl;
				return false;
			}
			else if (chequing >= 1000 && (chequing - withdrawamount) < 1000)
			{
				
				cout << "\nWARNING: Your chequing account will be fall under the $1000 threshold." << endl
				<< "A service charge of $2 dollars will be applied." << endl
				<< "Press Y to proceed: ";//should be a 'you have an extra two dollars to pay that charge check' or withdrawal-2 thing
				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
				{               
						chequing -= (withdrawamount + 2);
				}
				else
				{
					cout << "Transaction aborted" << endl;
					return false;
				}
			}
			else
			{
				chequing -= withdrawamount;
			}
		}
		return true;
	}

	//runs the menu for transfer options
	bool customerTransfer(int type, float amount)
	{
		if (amount <= 0)//check validity
		{
			cout << "Invalid amount. Transaction aborted.\n" << endl;
			return false;              
		}
		
		if (customerWithdrawal(type, amount))
		{
			if (customerDeposit(3-type, amount))
			{ 
				return true;
			}
		}
		else
			return false;
	}


	//main menu displayed only to customers ('c')
	void customerMainMenu()
	{
		cout << "\nHello " << userName << "," << endl;

		char choice;
		string optionNum;
		while (optionNum != "0") 
		{        
			printAccount();

			cout << "\nHow can we help you today?" << endl;
			cout << "1: Make a deposit" << endl
					<< "2: Make a withdrawal" << endl
					<< "3: Transfer account funds" << endl
					<< "4: Display current balance(s)" << endl
					<< "0: Logout" << endl;
			cout << "Option: ";

			cin >> optionNum;

			if (optionNum == "0")
			{
				cout << "Goodbye " << userName << ", signing off" << endl;
			}
			else if (optionNum == "1")
			{
				float dAmount;
				cout << "\nWould you like to deposit to:" << endl << "1. Savings\n2. Chequing\nChoice: ";
				choice = safercinInt();
				cout << "\nHow much would you like to deposit?\n$: ";
				dAmount = safercinFloat();
				customerDeposit(choice, dAmount);
			//	wrap(customerDeposit,choice, dAmount, currentUser,tracefile, "customerDeposit");
				continue;

			}
			else if (optionNum == "2")//withdraw menu
			{

				float wAmount;
				cout << "\nWould you like to withdraw from:" << endl << "1. Savings\n2. Chequing\nChoice: ";
				choice = safercinInt();
				cout << "\nHow much would you like to withdraw?\n$: ";
				wAmount = safercinFloat();
				//wrap(customerWithdrawal,choice, wAmount, currentUser, tracefile, "customerWithdrawal");
				customerWithdrawal(choice, wAmount);
			}		
			else if (optionNum == "3")
			{

				float tAmount;
				if (chequing == -1)
				{
					cout << "You do not have multiple accounts" << endl;
				}
				else
				{
					cout << "\nWould you like to transfer from:" << endl << "1. Savings\n2. Chequing\n";
					choice = safercinInt();
					cout << "\nHow much would you like to transfer?\n";
					tAmount = safercinFloat();
					customerTransfer(choice, tAmount);
					//wrap(customerTransfer,choice, tAmount, currentUser, tracefile, "customerTransfer");
					continue;
				}

			}
			else if (optionNum == "4")
				printAccount();
				//wrap(printAccount,*currentUser,tracefile, "printAccount");
			else 
			{
				cout << optionNum << " is not a valid option.." << endl;
			}
		
		}
		
	}

};