#include "Customer.h"

Customer::Customer(string name, string ID)
{
	userName = name;
	userID = ID;
	userType = "Cust";
	savings = 0.0;
	chequing = -1;
	creditLimit = 1000;
	creditBalance = 0;
	payOffCredit = true;
	isFrozen = false;
}

void Customer::printAccount()
{
	ostringstream oss;

	string sav = "$";
	string cheq = "$";
	string cb = "$";
	oss << fixed << setprecision(2) << savings;
	sav += oss.str();
	oss.str("");
	oss << fixed << setprecision(2) << creditBalance;
	cb += oss.str();
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
	cout << "Savings: " << sav << setw(30 - sav.length()) << "Chequing: " << cheq<<endl<< "Credit Balance:" << cb << endl;
}
void Customer::printPurchases()
{
	fstream purchaseStream;
	string filename;
	char purchase[65];
	filename = userName + ".txt";
	purchaseStream.open(filename, fstream::in);//open purchase report
	while (!purchaseStream.eof())
	{
		purchaseStream.getline(purchase, 64);
		cout << purchase << endl;

	}
	cout << endl;
}
bool Customer::customerDeposit(int choice, float depositamount)
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
		if (chequing > creditBalance && isFrozen)
		{
			chequing -= creditBalance;
			creditBalance = 0;
			isFrozen = false;
			cout << "Credit Unfrozen" << endl;

		}

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
bool Customer::customerWithdrawal(int choice, float withdrawamount)
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
bool Customer::customerTransfer(int type, float amount)
{
	if (amount <= 0)//check validity
	{
		cout << "Invalid amount. Transaction aborted.\n" << endl;
		return false;
	}

	if (customerWithdrawal(type, amount))
	{
		if (customerDeposit(3 - type, amount))
		{
			return true;
		}
		else
			return false;//added this else to it always returns a value, not 100% sure about it though. Deposit shouldn't fail?
	}
	else
		return false;
}

void Customer::manualCreditPayment()
{
	cout << "Enter amount you wish to pay off: " << endl;
	float amount;
	cin >> amount;
	if (amount <= chequing)
	{
		if (amount > creditBalance)
		{
			cout << "You entered an amount that is higher than your credit balance" << endl;
		}
		else
		{
			chequing -= amount;
			creditBalance -= amount;
			if (isFrozen = true)
			{
				
				isFrozen = false;
				cout << "Your account is now unfrozen" << endl;
			}
			cout << "Your card is now paid off" << endl;
	
		}

	}
	else 
	{
		cout << "You do not have sufficient funds in chequing to pay off this much of your credit card balance." << endl;
	}
}

//main menu displayed only to customers ('c')
void Customer::customerMainMenu()
{
	cout << "\nHello " << userName << "," << endl;

	char choice;
	string optionNum;
	while (optionNum != "0")
	{
		printAccount();

		cout << "B or V?" << endl;
		cin >> choice;

		if (choice == 'V' || choice == 'v')
		{
			if (isFrozen == true)
			{
				cout << "Your credit card has been declined.";
				continue;
			}
			ofstream purchaseStream;
			string filename;
			time_t timer(0);
			srand(time(NULL));
			time(&timer);
			float price = rand() % 100;
			filename = userName + ".txt";
			purchaseStream.open(filename, fstream::out | fstream::app);//open purchase report
			cout << "Do you want to pay: $" << price << endl; // Randomizing a price between 0 and 100

			char choice;//util method here for y/n thing?
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				purchaseStream << "ITEM BOUGHT FOR: $" << price <<endl;//add to purchase
				creditBalance += price;//add to bank file
			}
			else
			{
				cout << "Transaction aborted" << endl;
			}
			cout << "Goodbye " << userName;
			purchaseStream.close();

		}
		else
		{
			cout << "\nHow can we help you today?" << endl;
			cout << "1: Make a deposit" << endl
				<< "2: Make a withdrawal" << endl
				<< "3: Transfer account funds" << endl
				<< "4: Display current balance(s)" << endl
				<< "5. Print Purchases" <<endl
				<< "6. Make Manual Credit Payment" <<endl
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
				cout << "\nHow much would you like to deposit?\n ";
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
				cout << "\nHow much would you like to withdraw?\n ";
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
			else if (optionNum == "5")
				printPurchases();
			else if (optionNum == "6")
				manualCreditPayment();
			//wrap(printAccount,*currentUser,tracefile, "printAccount");
			else
			{
				cout << optionNum << " is not a valid option.." << endl;
			}
		}

	}

}

