#include "Manager.h"


Manager::Manager(string name, string ID)
	{
		userName = name;
		userID = ID;
		userType = "Man";
	}

	
void Manager::printAccount()
	{
		cout << "\nName: " << userName << setw(31 - userName.length()) << "UserID: " << userID << endl;
	}

void Manager::createUser(vector<User*> *accounts)
	{
		cout << "\nNew User Menu" << endl;
		char userType;
		bool invalidInput = true;
		string choice;

		while (invalidInput)
		{
			cout << "\nWhat type of user?" << endl
					<< "1. Customer" << endl
					<< "2. Manager" << endl
					<< "3. Maintenance" << endl
					<< "Choice: ";
        
			cin >> choice;
			
			invalidInput = false;
			
			if (choice == "1")
					userType = 'c';
			else if (choice == "2")
					userType = 'm';
			else if (choice == "3")
					userType = 'i';
			else
			{
				invalidInput = true;
				cout << choice << " is not a valid option..";
			}
		}

		string userName;
		bool nameCheck = false;

		while (!nameCheck)
		{
			cout << "What is the new user's name?" << endl
				 << "Name:";
			
			cin.ignore();
			getline(cin, userName);
			
			if (userName.length() <= 5)
			{
				//cout << "" << userName << endl;
				cout << "User's name is too short, must exceed 5 characters" << endl;
			}
			else
			{
				nameCheck = true;
			}
		}

		string userID = generateID(*accounts);
		if (userType == 'c')
			accounts->push_back(new Customer(userName, userID));
		else if (userType =='m')
			accounts->push_back(new Manager(userName, userID));
			
		cout << "New user created!" << endl << "The new user's userID is: " << userID << endl;
	}

	//Opens the menu that allows a manager to alter or make accounts
void Manager::managerEdit(vector<User*> *accounts)
	{
		//first the manager must choose which account to edit
		string userID;
		cout << "\nWhich account would you like to edit?" << endl
			 << "Account: ";
		cin >> userID;

		Customer* chosenUser =(Customer*) getUser(*accounts, userID);

		//if there is a user with this userID
		if (chosenUser != NULL)
		{
			string choice = "1";
			while (choice != "0")
			{
				cout << "\nAccessing " << chosenUser->userName << "'s account" << endl;
				cout << "What would you like to do?" << endl
					 << "1: Open a chequing account" << endl
					 << "2: Close chequing account" << endl
					 << "3: Close this account" << endl
					 << "4: Change credit limit" << endl
					 << "0: Return to main menu" << endl;
				cout << "Option:";
				
				cin >> choice;

				if (choice == "0")
					cout << "Signing out of " << chosenUser->userName << "'s account" << endl;
				else if (choice == "1" && chosenUser->chequing == -1)
				{
					
					chosenUser->chequing = 0;
					cout << chosenUser->userName << "'s chequing account has been created!" << endl;
					
				}
				else if (choice == "1" && chosenUser->chequing != -1)
					cout << chosenUser->userName << " already has a chequing account..." << endl;
				else if (choice == "2" && chosenUser->chequing == 0)
				{
					
					chosenUser->chequing = -1;
					cout << "Closing " << chosenUser->userName << "'s chequing account" << endl;
					
				}
				else if (choice == "2" && chosenUser->chequing != 0)
				{
					if (chosenUser->chequing > 0)
						cout << "Unable to close chequing, money still deposited" << endl;
					else
						cout << "That account is not open" << endl;
					
				}
				//delete the user and return manager to the main menu
				else if (choice == "3")
				{
					closeAccount(accounts, chosenUser);
				//	wrap(closeAccount,accounts,chosenUser,tracefile, "closeAccount");
					choice = "0";
				}
				else if (choice == "4")
				{
					cout << "Enter new credit limit:" << endl;
					float newLimit;
					cin >> newLimit;
					chosenUser->creditLimit = newLimit;
					cout << "New credit limit is " << newLimit << endl;
					choice = "0";
				}
				else
				{
					cout << choice << " is not a valid option" << endl;
				}   
			}
		}
		
		else cout << userID << " is not a valid ID" << endl;

	}

void Manager::closeAccount(vector<User*> *accounts, User* thisUser)
	{
		//This will crash if you try to close a manager or maintenance...
		Customer* toClose = (Customer*)thisUser;
		if (toClose->savings != 0)
			cout << toClose->userName << " still has money in savings account." << endl;
		else if (toClose->savings == 0)
		{
			if (toClose->chequing > 0)
			{
				cout << toClose->userName << " still has money in chequing account." << endl;
			}
			else
			{
				for (vector<User*>::iterator it = accounts->begin(); it != accounts->end(); ++it)
				{
					if ((*it) == thisUser) 
					{
						cout << "*UserID: " << toClose->userID << "\t Name: " << toClose->userName << "*" << endl;
						cout << "The selected profile has been deleted from the database" << endl;
						accounts->erase(it);
						break;
					}
				}
			}
		}
	}

	//will show the manager how much money is held by the bank
void Manager::managerTotals(vector<User*> accounts)
	{
		double totalSavings = 0;
		double totalChequing = 0;
		int customerCount = 0;
		
		for (vector<User*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
		{
			if ((*it)->userType == "Cust")
			{
				customerCount++;
				totalSavings += ((Customer*)(*it))->savings;
				
				if (((Customer*)(*it))->chequing != -1)
					totalChequing += ((Customer*)(*it))->chequing;
			}
		}
		
		cout << "\nThe bank currently has " << customerCount << " customer(s) with accounts" << endl;
		cout << "There is a total of $" << totalSavings << " in saving accounts" << endl;
		cout << "There is a total of $" << totalChequing << " in chequing accounts" << endl;
	}
void Manager::managerMonthEnd(vector<User*> *accounts)
{
	ofstream frozenStream;
	frozenStream.open("creditFrozen.txt", fstream::out | fstream::app);
	for (vector<User*>::iterator it = accounts->begin(); it != accounts->end(); ++it)
	{
		//For Each User
		//Check if they pay all or .10
		if ((*it)->userType != "Cust")
			continue;//if this user isn't a customer ignore them
		Customer *accountToCheck = ((Customer*)(*it));
		float paymentAmount;

		//
		if (accountToCheck->payOffCredit == true)
		{
			paymentAmount = accountToCheck->creditBalance;
		}
		else
		{
			paymentAmount = accountToCheck->creditBalance*.10;
		}
		//Check if they can pay it, if not freeze and exit the loop
		if (accountToCheck->chequing < paymentAmount)
		{
				accountToCheck->isFrozen = true;//may already be true
				frozenStream << accountToCheck->userName <<" failed to pay $"<<paymentAmount<< endl;//add to list of failed payments
		}
		else
		{
			accountToCheck->chequing -= paymentAmount;//transfer money from chequing to pay off credit
			accountToCheck->creditBalance -= paymentAmount;
		}
		accountToCheck->creditBalance *= 1.02;




	}
}
void Manager::managerFailedPayments()
{
	
	fstream frozenStream;
	string filename = "creditFrozen.txt";
	char purchase[65];
	frozenStream.open(filename, fstream::in);//open frozen report
	while (!frozenStream.eof())
	{
		frozenStream.getline(purchase, 64);
		cout << purchase << endl;

	}
	cout << endl;
}
void Manager::managerMainMenu(vector<User*> *accounts)
	{
		string option;
		cout << "\nHello " << userName << "," << endl;
    
		while (option != "0")
		{
			cout << "\nHow can we help you today?" << endl;
			cout << "1. Create a new user" << endl
				<< "2. Edit a user's account" << endl
				<< "3. View accounts" << endl
				<< "4. View Bank Totals" << endl
				<< "5. End the Month" <<endl
				<< "6. Display Failed Payments"<<endl
				<< "0. Logout" << endl;
			cout << "Option: ";
			
			cin >> option;
			
			if (option == "1")
			{
				createUser(accounts);
			}
				//wrap(createUser,accounts,tracefile, "createUser");
			else if (option == "2")
			{
				managerEdit(accounts);
				//wrap(managerEdit,accounts,tracefile, "mangerEdit");
				
			}
			else if (option == "3")
			{
				managerView(*accounts);
			}
//				wrap(managerView,accounts,tracefile,"managerView");
			else if (option == "4")
			{
				managerTotals(*accounts);
				
			}
			else if (option == "5")
			{
				managerMonthEnd(accounts);
			}
			else if (option == "6")
			{
				managerFailedPayments();
			}
			else
			{
				cout << option << " is not a valid option." << endl;
				
			}
		}
	}
	
void Manager::printAllAccounts(vector<User*> accounts)
	{
		if (!(accounts.empty()))
		{
			for (vector<User*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
			{
				if ((*it)->userType == "Cust")
					((Customer*)(*it))->printAccount();
			}
		}
		else
		{
			cout << "There are no customers in the database" << endl;
		}
	}
	
	//menu for viewing a User's (or all) accounts
void Manager::managerView(vector<User*> accounts)
	{
		string request;
		while (request != "0")
		{
			cout << "\nWhich user (userID) would you like to view?" << endl
				 << "Input the desired userID or " << endl
				 << "9: View all" << endl
				 << "0: Return to menu" << endl;
			cout << "Choice: ";
			
			cin >> request;

			if (request == "9")
			{
				printAllAccounts(accounts);
			}
			else if (request != "0")
			{				
				if (getUser(accounts, request) != NULL)
				{
					User *chosenUser = getUser(accounts, request);
					((Customer*)chosenUser)->printAccount();
				}
				else
					cout << request << " is not a valid ID" << endl;
				
			}
			else if (request == "0")
				cout << "Returning to main menu" << endl;
			else
				cout << request << " is not a valid option" << endl;
		}    
	}




