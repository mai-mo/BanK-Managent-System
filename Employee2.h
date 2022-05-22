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
	char	Name[30];
	char  National_ID[30];
	char PhoneNumber[11];
public:
	//operations
	Employee();
	void setID();
	void setName();
	void setNationalID();
	void setPhoneNumber();

	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From ObjectPerson  to  Record =>  Write
	int Unpack(VariableLengthRecord&);  // From Record to  Object Person  => Read

	void Print(ostream&);

	void add_employee(fstream& f, VariableLengthRecord outRecor);
	void add_available(fstream& f, VariableLengthRecord outRecord);

	void Delete(fstream& f,short rrn);

	void update_employee(fstream& myfile);
	bool search_employee(fstream& myfile);

	void display_all();
};

Employee::Employee()
{
	id = 0;
	Name[0] = 0;
	National_ID[0] = 0;
	PhoneNumber[0] = 0;
}
void Employee::setID() {
	cout << "Employee ID: ";
	cin >> id;

}
void Employee::setName()
{
	cout << "Name: \n";
	cin.getline(Name, 30);
}
void Employee::setNationalID() {
	cout << "National_ID: ";
	cin.getline(National_ID, 13);
}
void Employee::setPhoneNumber() {
	cout << "Phone: ";
	cin.getline(PhoneNumber, 11);
}
void Employee::add_employee(fstream& f, VariableLengthRecord outRecord)

{
	short header;
	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	if (header == -1)
	{
		setID();
		setName();
		setNationalID();
		setPhoneNumber();

		Pack(outRecord);
		outRecord.Write(f);
	}
	else
		add_available(f, outRecord);

}

void Employee::Delete( fstream& f,short rrn)
{
	short header;
	int recordSize = 2 + strlen(National_ID) + strlen(Name) + strlen(PhoneNumber) + 3;
	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	f.seekp(2 + (rrn - 1) * recordSize, ios::beg);
	f.put('*');
	f.write((char*)&header, sizeof(header));

	f.seekp(0, ios::beg);
	f.write((char*)&rrn, sizeof(rrn));
}
void Employee::update_employee(fstream& myfile)
{

	VariableLengthRecord record;
	
	if (search_employee( myfile)) {

		setID();
		setName();
		setNationalID();
		setPhoneNumber();
		Pack(record);
		record.Write(myfile);
	}
	else {
		cout << "Non exist";
		return;
	}
}
bool Employee::search_employee(fstream& myfile)
{
	VariableLengthRecord record;
	
	int recordSize = 2 + strlen(National_ID) + strlen(Name) + strlen(PhoneNumber) + 3;
S:
	char decision;
	int i = 1;
	short searched_id;
	cout << "\aPlease Enter The ID To Search About The Employee \n";
	cin >> searched_id;
	if (myfile.is_open()) {
		do {
			myfile.ReadHeader(myfile);
			myfile.getline(id, 2);
			if (id == searched_id) {
				cin.ignore();
				myfile.getline(Name, 30);
				myfile.getline(National_ID, 13);
				myfile.getline(PhoneNumber, 11);
				cout << "\aWe Have Found The account \n"
					<< "Name: " << Name << endl
					<< "ID : " << id << endl
					<< "National_id: " << National_ID << endl
					<< "Phone: " << PhoneNumber;
				i = 0;
				break;
			}
			else
			{
				myfile.getline(Name, 30);
				myfile.seekg(recordSize);
			}

		} while (!myfile.eof());

	}
	else {
		cout << "ERROR!";
	}


	if (i)
	{
		cout << "\aYou don't have any contacts yet \n";
		do {
			cout << "Are you want to search again ? if yes Enter y else Enter n\n";
		} while (decision != 'y' && decision != 'n');
		cin >> decision;
		if (decision == 'y' || decision == 'Y')
			goto S;
		else
			return false;
	}
}
 initialize a VariableLengthRecord to be used for Employees
void Employee::InitRecord(VariableLengthRecord& record)
{
	record.init(4);
	record.AddField(0, 'F', 2);  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'D', '|');
	record.AddField(2, 'D', '|');
	record.AddField(3, 'D', '|');
}
int Employee::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7

	recordSize = 2 + strlen(National_ID) + strlen(Name) + strlen(PhoneNumber) + 3;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short)) && record.Pack(1, (void*)Name, strlen(Name))
		&& record.Pack(2, (void*)National_ID, strlen(National_ID))
		&& record.Pack(3, (void*)PhoneNumber, strlen(PhoneNumber));

	

	return result;
}
int Employee::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(1, Name, true)
		&& record.Unpack(2, National_ID, true)
		&& record.Unpack(3, PhoneNumber, true);
	result = result && record.Unpack(0, (char*)&id);
	return result;
}
void Employee::Print(ostream& stream)
{
	stream << "Person:"
		<< "\tId: " << id << "'\n"
		<< "\tName: " << Name << "'\n"
		<< "\tnational_ID: " << National_ID << "'\n"
		<< "\tphone: " << PhoneNumber << "'\n";
}
