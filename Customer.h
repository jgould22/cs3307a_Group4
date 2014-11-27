#include "User.h"
class Customer : public User
{
public:
	double savings;
	double chequing;
	double creditLimit;
	double creditBalance;
	bool isFrozen;
	bool payOffCredit;

public:
	Customer(string name, string ID);
	


	void printAccount();
	void printPurchases();

	bool customerDeposit(int choice, float depositamount);

	//runs the menu for withdrawal options
	//implements the WARNING message if chequing accounts do not meet the $1000 threshold
	bool customerWithdrawal(int choice, float withdrawamount);

	//runs the menu for transfer options
	bool customerTransfer(int type, float amount);
	
	//option to manually pay off credit card balance
	void manualCreditPayment();

	//main menu displayed only to customers ('c')
	void customerMainMenu();

};