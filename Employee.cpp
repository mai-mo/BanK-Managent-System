#include <string.h>
#include "Employee.h"
#include <fstream>




Employee::Employee()
{
	setID();
	setName();
	setNationalID();
	setPhone();
}

void Employee::setID() {
	cout << "Employee ID: ";
	cin >> id;
	
}

void Employee::setName()
{
	cout << "Name: \n";
	cin >> Name;
}

void Employee::setNationalID() {
	cout << "ID: ";
	for(int i = 0; i < 14; i++)
		cin >> national_ID[i];
}

void Employee::setPhone() {
	cout << "Phone: ";
	for (int i = 0; i < 11; i++)
		cin >> phone[i];
}

void Employee::add_employee()
{
	//mai
	setID();
	setName();
	setNationalID();
	setPhone();
	
	fstream myfile;
	myfile.open("Employee.txt", ios::out);
	VariableLengthRecord& record();
	//int index, char szType, char delimite
	InitRecord(record);
	Pack(record);
}

void Employee::delete_employee()
{

}

void Employee::edit_employee(int)
{

}

void Employee::search_employee()
{
	

}


// initialize a VariableLengthRecord to be used for Employees
void Employee::InitRecord(VariableLengthRecord& record)
{
	record.init(4);
	record.AddField(0, 'F', 2);  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'D', '|');
	record.AddField(2, 'F', 14);
	record.AddField(3, 'F', 11);

}

int Employee::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7
	// 2 -> first field
	recordSize = 2 + strlen(Name) + 1 + 14 + 11;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short))
	
	&& record.Pack(1, (void*)Name, strlen(Name))

	 && record.Pack(2, (void*)national_ID, strlen(national_ID))

	 && record.Pack(3, (void*)phone, strlen(phone));

	return result;
}

int Employee::Unpack(VariableLengthRecord& record)
{
	int result; 
	result = record.Unpack(0, (char*)&id) && record.Unpack(1, Name, true) && record.Unpack(2, national_ID, true)&& record.Unpack(3, phone, true);
	return result;
}

void Employee::Print(ostream& stream)
{
	stream << "Person:"
		<< "\tId: " << id << "'\n"
		<< "\tName: " << Name << "'\n"
		<< "\tnational_ID: " << national_ID << "'\n"
		<< "\tphone: " << phone <<"'\n";
}
