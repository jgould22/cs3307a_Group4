
#include <Manager.cpp>

int main(int argc, char **argv)
{
	//Declare variables required to hold program information
	vector<User*> vectorUser; 
//    bool flag;
//= openDataBase(flag);
//   vector<User> *accounts = &vectorUser;
//  time_t timer(0);
    string userID;
	
	while (true)
    {
   //     system("cls");
        cout << "Welcome to the 1st National Bank" << endl;
        cout << "Please input your userID or 0 to quit: ";
        cin >> userID;
	
		 //closes program
        if (userID == "0")
        {
        //    saveToDataBase(accounts, flag);
            return 0;
        }
		else
        {
            //determine which menu to open
			User* currentUser = getUser(&vectorUser, userID);
			if (currentUser != NULL)
			{
				if (currentUser->userType == "Cust")
				{
					(dynamic_cast<Customer*>(currentUser))->customerMainMenu();
				}
				else if (currentUser->userType == "Man")
				{
					(dynamic_cast<Manager*>(currentUser))->managerMainMenu();
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
    
		   
		   Customer* c = new Customer("ack","123");
			vectorUser.push_back(c);
			//vectorUser.push_back(new Manager("hill", "567"));
			
			cout << (dynamic_cast<Customer*> (vectorUser[0]))->savings<<endl;
		}
}

//OpenDataBase Function
//Opens and loads saved users/accounts during program startup
//vector<User> openDataBase(bool& flag)
//{
//	ifstream myfile("userDB.txt");
//    vector<User> vectorUser;
//    
//    if (myfile)
//    {
//        string name;
//        string userID;
//        char userType;
//        double savings;
//        double chequing;
//        string line;
//        
//        getline(myfile, line);
//        
//        if(line == "1")
//			flag=1;
//        else
//            flag=0;
//        
//        while (!myfile.eof())
//        {
//			getline(myfile, name);
//			if (name != "")
//            {
//				getline(myfile, userID);
//				myfile >> userType
//					   >> savings
//                       >> chequing;
//				vectorUser.push_back(Customer(name, userID));
//                getline(myfile, line);
//			}
//        }
//		//file can exist with no users
//		if(vectorUser.empty())
//		{
//			cout << "There is no database.  A new manager is needed." << endl;
//			system("pause");
//			createManager(&vectorUser);
//		}
//		
//		myfile.close();
//		
//		return vectorUser;
//    }
//    
//	//file can exist with no users
//    if(vectorUser.empty())
//    {
//        cout << "There is no database.  A new manager is needed." << endl;
//        system("pause");
//        createManager(&vectorUser);
//    }
//    
//    myfile.close();
//    
//    return vectorUser;
//    
//}


