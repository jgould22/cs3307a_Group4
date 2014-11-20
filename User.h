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
	User();

public:
	int safercinInt();


	//Function to ensure safe float input 
	float safercinFloat();

};
User* getUser(vector<User*> accounts, string id);
string generateID(vector<User*> accounts);