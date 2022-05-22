#include <iostream>
#include <string.h>
#include "Employee.h"
#include <fstream>
#include "varlen.h"
using namespace std;


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
	cin.getline(Name, 20);
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
	myfile.open("Employee.txt", ios::out||ios::binary);
	VariableLengthRecord record;
	//int index, char szType, char delimite
	InitRecord(record);
	Pack(record);
	record.Write(myfile);
	
}

void Employee::delete_employee()
{
}

void Employee::update_employee()
{
	VariableLengthRecord record;
	ifstream myfile;
	myfile.open("Employee.txt", ios::out || ios::in || ios::binary);
	if (search_employeeID()) {

		setID();
		setName();
		setNationalID();
		setPhone();
		Pack(record);
		record.Write(myfile);	
	}
	else {
		cout << "Non exist";
		return;
	}
}

bool Employee::search_employeeID()
{
	VariableLengthRecord record;
	ifstream myfile;
	myfile.open("Employee.txt", ios::in||ios::binary);
S:
	char decision;
	short searched_id;
	cout << "\aPlease Enter The ID To Search About The Employee \n";
	cin >> searched_id;
	if (myfile.is_open()) {
		do {record.ReadHeader(myfile);
		myfile.read((char*)&id, 2);
			if (id == searched_id) {
				myfile.getline(Name, '|');
				myfile.getline(national_ID, 14);
				myfile.getline(phone, 11);
				cout << "\aWe Have Found The Employee Data \n"
					<< "Name: " << Name << endl
					<< "ID : " << id << endl
					<< "National_id: " << national_ID << endl
					<< "Phone: " << phone; return true;
			}
			else
			{myfile.getline(Name, '|');
				myfile.seekg((sizeof(Name)) +14 + 11);
			}} while (!myfile.eof());
		
		
	}
	else {
		cout << "ERROR!";
	}
		cout << "\aYou don't have any contacts yet \n";
		do {
			cout << "Are you want to search again ? if yes Enter y else Enter n\n";
		} while (decision != 'y' && decision != 'n');
		cin >> decision;
		if (decision == 'y'||decision == 'Y')
			goto S;
		else
			return false;
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
	// 4 -> first field
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
	result = record.Unpack(0, (char*)&id)
		&& record.Unpack(1,(char*) Name, true)
		&& record.Unpack(2, national_ID, true)
			&& record.Unpack(3, phone, true);
	return result;
}

void Employee::PrintAll(ostream& stream)
{
	VariableLengthRecord record;
	ifstream myfile;
	myfile.open("Employee.txt", ios::in);
	if (myfile.is_open())
	{
		while (!myfile.eof()) {
			record.Read(myfile);
			Unpack(record);
			stream << "Person:"
				<< "\tId: " << id << "'\n"
				<< "\tName: " << Name << "'\n"
				<< "\tnational_ID: " << national_ID << "'\n"
				<< "\tphone: " << phone << "'\n";
			myfile.close();
		}
	}
}
