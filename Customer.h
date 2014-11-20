#include "User.h"
class Customer : public User
{
public:
	double savings;
	double chequing;

public:
	Customer(string name, string ID);


	void printAccount();

	bool customerDeposit(int choice, float depositamount);

	//runs the menu for withdrawal options
	//implements the WARNING message if chequing accounts do not meet the $1000 threshold
	bool customerWithdrawal(int choice, float withdrawamount);

	//runs the menu for transfer options
	bool customerTransfer(int type, float amount);


	//main menu displayed only to customers ('c')
	void customerMainMenu();

};