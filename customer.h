#include <iostream>
//#include "fixtext.h"
//#include "lentext.h"
#include "varlen.h"
using namespace std;

class customer
{
public:
	// fields
	short	id = 0;
	char	name[11];
	double balance = 0;
	
	int accont_number = 0;
	int password = 0;
	int phone = 0;
	int operation_tybe =0;
	

	//operations
	customer();
	customer(short cid, char cname[], char ctype, int cpassword, int cbalance, int cphone, int caccont_number);
	customer(short id, char name[],  int password, double balance, int phone, int accont_number);

	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From ObjectPerson  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Person  => Read



	void Print(ostream&);

	void create_account(fstream& stream);

	
	void deposit_withdraw(int n);
	
	void dep(int x);
	void draw(int x);
	int retdeposit();
	void show_account(fstream& in);
	
};

