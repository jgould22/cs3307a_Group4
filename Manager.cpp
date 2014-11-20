#include "Customer.cpp"

class Manager: public User
{
public:
	Manager(string name, string ID)
	{
		userName = name;
		userID = ID;
	}
public:
	void createUser(vector<User> *accounts)
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
				cout << "name-" << userName << endl;
				cout << "User's name is too short, must exceed 5 characters" << endl;
			}
			else
			{
				nameCheck = true;
			}
		}

		string userID = generateID(accounts);
		if (userType == 'c')
			accounts->push_back(Customer(userID, userName));
		else if (userType =='m')
			accounts->push_back(Manager(userID, userName));
			
		cout << "New user created!" << endl << "The new user's userID is: " << userID << endl;
	}

	//Opens the menu that allows a manager to alter or make accounts
//	void managerEdit(vector<User> *accounts)
//	{
//		//first the manager must choose which account to edit
//		string userID;
//		cout << "\nWhich account would you like to edit?" << endl
//			 << "Account: ";
//		cin >> userID;
//
//		Customer* chosenUser = Customer::getUser(accounts, userID);
//
//		//if there is a user with this userID
//		if (chosenUser != NULL)
//		{
//			string choice = "1";
//			while (choice != "0")
//			{
//				cout << "\nAccessing " << chosenUser->userName << "'s account" << endl;
//				cout << "What would you like to do?" << endl
//					 << "1: Open a chequing account" << endl
//					 << "2: Close chequing account" << endl
//					 << "3: Close this account" << endl
//					 << "0: Return to main menu" << endl;
//				cout << "Option:";
//				
//				cin >> choice;
//
//				if (choice == "0")
//					cout << "Signing out of " << chosenUser->userName << "'s account" << endl;
//				else if (choice == "1" && chosenUser->chequing == -1)
//				{
//					
//					chosenUser->chequing = 0;
//					cout << chosenUser->name << "'s chequing account has been created!" << endl;
//					
//				}
//				else if (choice == "1" && chosenUser->chequing != -1)
//					cout << chosenUser->name << " already has a chequing account..." << endl;
//				else if (choice == "2" && chosenUser->chequing == 0)
//				{
//					
//					chosenUser->chequing = -1;
//					cout << "Closing " << chosenUser->userName << "'s chequing account" << endl;
//					
//				}
//				else if (choice == "2" && chosenUser->chequing != 0)
//				{
//					
//					cout << "Unable to close chequing, money still deposited" << endl;
//					
//				}
//				//delete the user and return manager to the main menu
//				else if (choice == "3")
//				{
//					
//					wrap(closeAccount,accounts,chosenUser,tracefile, "closeAccount");
//					choice = "0";
//				}
//				else
//				{
//					cout << choice << " is not a valid option" << endl;
//				}   
//			}
//		}
//		
//		else cout << userID << " is not a valid ID" << endl;
//
//	}

//	void closeAccount(vector<User> *accounts, User* thisUser)
//	{
//		
//		if (thisUser->savings != 0)
//			cout << thisUser->name << " still has money in savings account." << endl;
//		else if (thisUser->savings == 0)
//		{
//			if (thisUser->chequing > 0)
//			{
//				cout << thisUser->name << " still has money in chequing account." << endl;
//			}
//			else
//			{
//				for (vector<User>::iterator it = accounts->begin(); it != accounts->end(); ++it)
//				{
//					if (&*(it) == thisUser) 
//					{
//						cout << "*UserID: " << thisUser->id << "\t Name: " << thisUser->name << "*" << endl;
//						cout << "The selected profile has been deleted from the database" << endl;
//						accounts->erase(it);
//						break;
//					}
//				}
//			}
//		}
//	}

	//will show the manager how much money is held by the bank
//	void managerTotals(vector<User> *accounts)
//	{
//		double totalSavings = 0;
//		double totalChequing = 0;
//		int customerCount = 0;
//		
//		for (vector<User>::iterator it = accounts->begin(); it != accounts->end(); ++it)
//		{
//			if ((*it).userType == 'c')
//			{
//				customerCount++;
//				totalSavings += (*it).savings;
//				
//				if ((*it).chequing != -1)
//					totalChequing += (*it).chequing;
//			}
//		}
//		
//		cout << "\nThe bank currently has " << customerCount << " customer(s) with accounts" << endl;
//		cout << "There is a total of $" << totalSavings << " in saving accounts" << endl;
//		cout << "There is a total of $" << totalChequing << " in chequing accounts" << endl;
//	}


//	void managerMainMenu()
//	{
//		string option;
//		cout << "\nHello " << userName << "," << endl;
//    
//		while (option != "0") {
//
//			cout << "\nHow can we help you today?" << endl;
//			cout << "1. Create a new user" << endl
//				<< "2. Edit a user's account" << endl
//				<< "3. View accounts" << endl
//				<< "4. View Bank Totals" << endl
//				<< "0. Logout" << endl;
//			cout << "Option: ";
//			
//			cin >> option;
//			
//			if (option == "1")
//			{
//				createUser();
//			}
//				//wrap(createUser,accounts,tracefile, "createUser");
//			else if (option == "2")
//			{
//				managerEdit(accounts);
//				//wrap(managerEdit,accounts,tracefile, "mangerEdit");
//				
//			}
//			else if (option == "3")
//			{
//				managerView(accounts);
//			}
////				wrap(managerView,accounts,tracefile,"managerView");
//			else if (option == "4")
//			{
//				managerTotals(accounts);
//				
//			}
//			else
//			{
//				cout << option << " is not a valid option." << endl;
//				
//			}
//		}
//	}
	
	//Generates ID
	//Uses rand to generate a user ID for new users between 1000 and 10000
	string generateID(vector<User> *accounts)
	{
		int xRan;
		ostringstream oss;
		srand(time(NULL));

		bool inUse = false;
		do
		{
			xRan = rand() % 10000 + 1000; // Randomizing the number between 1000-10000
			oss << xRan;
			for (vector<User>::iterator it = accounts->begin(); it != accounts->end(); ++it)
			{
				if ((*it).userID == oss.str())
				{
					inUse = true;
					break;
				}
			}
		}while (inUse);
		
		return oss.str();
		
	}
	
	//menu for viewing a User's (or all) accounts
	void managerView(vector<User> *accounts)
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
//				printAllAccounts(accounts);
			}
			else if (request != "0")
			{				
				if (getUser(accounts, request) != NULL)
				{
					//printAccount(chosenUser);
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

	
};