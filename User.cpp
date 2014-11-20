#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
#include <math.h>
#include <sstream>
#include <vector>

using namespace std;

class User
{	
    //Class attributes
public:
	virtual ~User() { }; 
    string userID;
    string userName;
	string userType;

    //Constructors
    User() {};
	
public:
	int safercinInt()
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
	float safercinFloat()
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
};