#include "Customer.h"
class Manager : public User
{
public:
	Manager(string name, string ID);
	
	void printAccount();
	
	void createUser(vector<User*> *accounts);

	//Opens the menu that allows a manager to alter or make accounts
	void managerEdit(vector<User*> *accounts);

	void closeAccount(vector<User*> *accounts, User* thisUser);

	//will show the manager how much money is held by the bank
	void managerTotals(vector<User*> accounts);

	void managerMainMenu(vector<User*> *accounts);

	void printAllAccounts(vector<User*> accounts);

	//menu for viewing a User's (or all) accounts
	void managerView(vector<User*> accounts);

	void managerMonthEnd(vector<User*> *accounts);

	void managerFailedPayments();


};