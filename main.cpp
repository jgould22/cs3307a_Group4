#include "Manager.h"



void saveToDataBase(vector<User*> accounts);
vector<User*> openDataBase();
void createManager(vector<User*> *accounts);

int main(int argc, char **argv)
{
	//Declare variables required to hold program information
	vector<User*> vectorUser = openDataBase();
	//vector<User*> *accounts = &vectorUser;

	
	string userID;
	

	while (true)
	{
		system("cls");
		cout << "Welcome to the 1st National Bank" << endl;
		cout << "Please input your userID or 0 to quit: ";
		cin >> userID;

		//closes program
		if (userID == "0")
		{
			saveToDataBase(vectorUser);
			return 0;
		}
		else
		{
			//determine which menu to open
			User* currentUser = getUser(vectorUser, userID);
			if (currentUser != NULL)//check if that person exists
			{
				
					if (currentUser->userType == "Cust")
					{
						((Customer*)(currentUser))->customerMainMenu();
					}
					else if (currentUser->userType == "Man")
					{
						((Manager*)(currentUser))->managerMainMenu(&vectorUser);
					}
					else
					{

					}
				
			}
			else //Account ID is not in system, print warning 
			{
				cout << userID << " is not a recognized account ID." << endl;
				system("pause");
			}
		}
	}
}

//SaveToDataBase Function
//Saves the User accounts to a text file for program to load at later start up 
void saveToDataBase(vector<User*> accounts)
{
	ofstream myFile;
	myFile.open("userDB.txt");

	for (vector<User*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
	{
		if ((*it)->userType == "Cust")
		{
			myFile << (*it)->userName << "\n" << (*it)->userID << "\n" << (*it)->userType << "\n" << ((Customer*)(*it))->savings << "\n" << ((Customer*)(*it))->chequing << "\n"
				<< ((Customer*)(*it))->creditBalance << "\n" << ((Customer*)(*it))->creditLimit << "\n";;
		}
		else if ((*it)->userType == "Man")
		{
			myFile << (*it)->userName << "\n" << (*it)->userID << "\n" << (*it)->userType << "\n";
		}
		else
		{

		}
	}
	myFile.close();
}

//OpenDataBase Function
//Opens and loads saved users/accounts during program startup
vector<User*> openDataBase()
{
	ifstream myfile("userDB.txt");
	vector<User*> vectorUser;

	if (myfile)
	{
		string name;
		string userID;
		string userType;
		double savings;
		double chequing;
		double creditBalance;
		double creditLimit;

		string line;

		while (!myfile.eof())
		{
			getline(myfile, name);
			if (name != "")
			{
				getline(myfile, userID);
				myfile >> userType;

				if (userType == "Cust")
				{
					myfile >> savings
						>> chequing
						>> creditBalance
						>> creditLimit;

					Customer *user = new Customer(name, userID);
					user->savings = savings;
					user->chequing = chequing;
					user->creditBalance = creditBalance;
					user->creditLimit = creditLimit;
					vectorUser.push_back(user);

					getline(myfile, line);
				}
				else if (userType == "Man")
				{
					Manager *user = new Manager(name, userID);
					vectorUser.push_back(user);
				}
			}
		}
		//file can exist with no users
		if (vectorUser.empty())
		{
			cout << "There is no database.  A new manager is needed." << endl;
			system("pause");
			createManager(&vectorUser);
		}
		myfile.close();
		return vectorUser;
	}

	//file can exist with no users
	if (vectorUser.empty())
	{
		cout << "There is no database.  A new manager is needed." << endl;
		system("pause");
		createManager(&vectorUser);
	}

	myfile.close();

	return vectorUser;
}

//Creates Bank Manager
//Used when program start for first time or when Manager creates another user with manager privileges  
void createManager(vector<User*> *accounts)
{

	string userName;
	bool nameCheck = false;
	while (!nameCheck)

	{

		cout << "Manager's name: ";
		getline(cin, userName);

		if (userName.length() <= 5)
		{
			cout << "name-" << userName << endl;
			cout << "Manager's name is too short, must exceed 5 characters" << endl;
		}
		else
		{
			nameCheck = true;
		}

	}

	string userID = generateID(*accounts);
	accounts->push_back(new Manager(userName, userID));

	cout << "New manager created!" << endl << "The userID is: " << userID << endl;
	system("pause");
}

