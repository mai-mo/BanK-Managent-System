#include <iostream>
//#include "fixtext.h"
//#include "lentext.h"
#include "varlen.h"
#include <string.h>
using namespace std;

class Employee
{
private:
	// fields
	short	id;
	string Name;
	char national_ID[14];
	char phone[11];

public:
	//operations
	Employee();
	void setID();
	void setName();
	void setNationalID();
	void setPhone();
	


	void InitRecord(VariableLengthRecord&); //set Record  Configuration
	
	int Pack(VariableLengthRecord&);	//  From ObjectPerson  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Person  => Read

	
	void Print(ostream&);

	//hager
	void add_employee();
	//hager
	void delete_employee();
	void edit_employee(int);
	void search_employee();
	void display_all();
};