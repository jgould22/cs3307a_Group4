
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
	
	
		//Get User
	//Returns a pointer to a user after searching the user vector
	User* getUser(vector<User*> *accounts, string id)
	{
		for (int i = 0; i< (int)accounts->size(); ++i)
		{
			if ((*accounts)[i]->userID == id)
			{
				return (*accounts)[i];
			}
		}
		return NULL;
	}