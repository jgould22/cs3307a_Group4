#include "User.h"



    //Constructors
    User::User() {};
	

	int User::safercinInt()
{
    int choice;
    
	//Loop continues until valid entry is detected
    while (true)
    {
        
        if (!(cin >> choice))
        {
            cout << "Invalid input.  Try again: ";
            cin.clear();
            while (cin.get() != '\n') ; // empty loop     
        }
        else
		{
			break;	
		}
    }
    return choice;
}

	//Function to ensure safe float input 
	float User::safercinFloat()
	{
		
		float choice;
		
		//continues until a safe input is detected
		while (true)
		{
			
			if (!(cin >> choice))
			{
					cout << "Invalid input.  Try again: ";
					cin.clear();
					while (cin.get() != '\n') ; // empty loop
			}
			else 
					break;
						
		}

		return choice;
	}

	User* getUser(vector<User*> accounts, string id)
	{
		for (int i = 0; i< (int)accounts.size(); ++i)
		{
			if (accounts[i]->userID == id)
			{
				return accounts[i];
			}
		}
		return NULL;
	}
	string generateID(vector<User*> accounts)
	{
		int xRan;
		ostringstream oss;
		srand(time(NULL));

		bool inUse = false;
		do
		{
			xRan = rand() % 10000 + 1000; // Randomizing the number between 1000-10000
			oss << xRan;
			for (vector<User*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
			{
				if ((*it)->userID == oss.str())
				{
					inUse = true;
					break;
				}
			}
		} while (inUse);

		return oss.str();
	}