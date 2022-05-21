#include <iostream>
//#include "fixtext.h"
//#include "lentext.h"
#include "varlen.h"

using namespace std;

class Employee
{
public:
	// fields
	short	id;
	char	Name[30];
	char National_ID[13];
	char PhoneNumber[11];

	//operations
	Employee();

	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From ObjectEmployee  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Employee  => Read


	void Print(ostream&);

	void Add(fstream& f, VariableLengthRecord outRecord);

	void add_available(fstream& f, VariableLengthRecord outRecord);

	void Delete(short rrn, fstream& f);


};

Employee::Employee()
{
	id = 0;
	Name[0] = 0;
	National_ID[0] = 0;
	PhoneNumber[0] = 0;
}


// initialize a VariableLengthRecord to be used for Employees
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

	result = record.Pack(1, (void*)Name, strlen(Name))
		&& record.Pack(2, (void*)National_ID, strlen(National_ID))
		&& record.Pack(3, (void*)PhoneNumber, strlen(PhoneNumber));

	result = result && record.Pack(0, (void*)&id, sizeof(short));

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
	stream << "Employee:"
		<< "\tName '" << Name << "'\n"
		<< "\tNational_ID '" << National_ID << "'\n"
		<< "\tPhoneNumber '" << PhoneNumber << "'\n"
		<< "\tId '" << id << "'\n";
}
void Employee::Add(fstream& f, VariableLengthRecord outRecord)

{
	short header;
	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	if (header == -1)
	{
		f.seekp(0, ios::end);
		cout << "Enter Name:  " << endl;
		cin.getline(Name, 30);
		cout << "Enter National_ID:  " << endl;
		cin.getline(National_ID, 13);
		cout << "Enter PhoneNumber:  " << endl;
		cin.getline(PhoneNumber, 11);
		cout << "Enter id:  " << endl;
		cin >> id;

		Pack(outRecord);
		outRecord.Write(f);
	}
	else
		add_available(f, outRecord);
}
void Employee::Delete(short rrn, fstream& f)
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
void Employee::add_available(fstream& f, VariableLengthRecord outRecord)
{
	short header, next_del;
	char del_flag;
	int recordSize = 2 + strlen(National_ID) + strlen(Name) + strlen(PhoneNumber) + 3;

	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	f.seekg(2 + (header - 1) * recordSize, ios::beg);
	f.get(del_flag);
	f.read((char*)&next_del, sizeof(next_del));

	f.seekp(0, ios::end);
	cout << "Enter Name:  " << endl;
	cin.getline(Name, 30);
	cout << "Enter National_ID:  " << endl;
	cin.getline(National_ID, 13);
	cout << "Enter PhoneNumber:  " << endl;
	cin.getline(PhoneNumber, 11);
	cout << "Enter id:  " << endl;
	cin >> id;

	Pack(outRecord);
	outRecord.Write(f);

	f.seekp(0, ios::beg);
	f.write((char*)&next_del, sizeof(next_del));
}


