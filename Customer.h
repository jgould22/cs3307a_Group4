#include "User.h"
class Customer : public User
{
	friend class Manager;
private:
	double savings;
	double chequing;
	double creditLimit;
	double creditBalance;
	bool frozen;
	bool paymax;

public:
	Customer(string name, string ID);
	Customer(string name, string userID,double savings,double chequing,double creditBalance,double creditLimit, bool frozen);


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

	double getSavings();
	double getChequing();
	double getCreditLimit();
	void setNewLimit(double);
	double getCreditBalance();
	bool   isFrozen();
	bool payOffCredit();
	bool monthEnd();
	

};