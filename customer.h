#include <iostream>
//#include "fixtext.h"
//#include "lentext.h"
#include "varlen.h"
#include <fstream>

using namespace std;

class customer
{
public:
	// fields
	short	id;
	char	Name[30];
	char accnum[13];
	char balance[10];
	char password[5];
	char PhoneNumber[11];
	char operation_tybe[2];

	//operations
	customer();

	void InitRecord(VariableLengthRecord&); //set Record  Configuration

	int Pack(VariableLengthRecord&);	//  From ObjectEmployee  to  Record =>  Write


	int Unpack(VariableLengthRecord&);  // From Record to  Object Employee  => Read


	void Print(ostream&);

	void Add(fstream& f, VariableLengthRecord outRecord);

	void add_available(fstream& f, VariableLengthRecord outRecord);

	void Delete(fstream& f,short rrn );
	void update_customer(fstream myfile,VariableLengthRecord record);
	bool search_customerID(fstream myfile,VariableLengthRecord record);

};

customer::customer()
{
	id = 0;
	Name[0];
	accnum[0];
	balance[0];
	password[0];
	PhoneNumber[0];
	operation_tybe[0];

}


// initialize a VariableLengthRecord to be used for Employees
void customer::InitRecord(VariableLengthRecord& record)
{
	record.init(7);
	record.AddField(0, 'F', 2);  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'D', '|');
	record.AddField(2, 'F', 30);
	record.AddField(3, 'F', 13);
	record.AddField(4, 'F', 5);
	record.AddField(5, 'F', 2);
	record.AddField(6, 'F', 10);
}

int customer::Pack(VariableLengthRecord& record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result{}, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7

	recordSize = 2 + strlen(Name) + 13 + 10 + 5 + 11 + 2 + 1;

	record.Clear(recordSize);
	result = result && record.Pack(0, (void*)&id, sizeof(short))
		&&
		record.Pack(1, (void*)Name, strlen(Name))
		&& record.Pack(2, (void*)accnum, strlen(accnum))
		&& record.Pack(3, (void*)PhoneNumber, strlen(PhoneNumber))
		&& record.Pack(4, (void*)balance, strlen(balance))
		&& record.Pack(5, (void*)password, strlen(password))
		&& record.Pack(6, (void*)operation_tybe, strlen(operation_tybe))
		;



	return result;
}

int customer::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, (char*)&id)
		&& record.Unpack(1, Name, true)
		&& record.Unpack(2, accnum, true)
		&& record.Unpack(3, PhoneNumber, true)
		&& record.Unpack(4, balance, true)
		&& record.Unpack(5, password, true)
		&& record.Unpack(6, operation_tybe, true);

	return result;
}

void customer::Print(ostream& stream)
{
	stream << "CUSTOMER:"
		<< "\tName '" << Name << "'\n"
		<< "\tNational_ID '" << accnum << "'\n"
		<< "\tPhoneNumber '" << PhoneNumber << "'\n"
		<< "\tId '" << id << "'\n"
		<< "\tbalance" << balance << "\n"
		<< "\tpassword" << password << "\n"
		<< "\toperation_type" << operation_tybe << "\n";
}
void customer::Add(fstream& f, VariableLengthRecord outRecord)

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
		cin.getline(accnum, 13);
		cout << "Enter PhoneNumber:  " << endl;
		cin.getline(PhoneNumber, 11);
		cout << "Enter balance" << endl;
		cin.getline(balance, 10);
		cout << "Enter password" << endl;
		cin.getline(password, 5);
		cout << "operation_type" << endl;
		cin.getline(operation_tybe, 2);
                cout << "Enter id:  " << endl;
		cin >> id;
		Pack(outRecord);
		outRecord.Write(f);
	}
	else
		add_available(f, outRecord);
	f.close()
}
void customer::Delete(fstream& f,short rrn )
{
	short header;
	int recordSize = 2 + strlen(Name) + 13 + 10 + 5 + 11 + 2 + 1;
	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	f.seekp(2 + (rrn - 1) * recordSize, ios::beg);
	f.put('*');
	f.write((char*)&header, sizeof(header));

	f.seekp(0, ios::beg);
	f.write((char*)&rrn, sizeof(rrn));
	f.close();
}
void customer::add_available(fstream& f, VariableLengthRecord outRecord)
{
	short header, next_del;
	char del_flag;
	int recordSize = 2 + strlen(accnum) + strlen(Name) + strlen(PhoneNumber) + strlen(balance) + strlen(password) + strlen(operation_tybe) + 6;

	f.seekg(0, ios::beg);
	f.read((char*)&header, sizeof(header));

	f.seekg(2 + (header - 1) * recordSize, ios::beg);
	f.get(del_flag);
	f.read((char*)&next_del, sizeof(next_del));

	f.seekp(0, ios::end);
	cout << "Enter Name:  " << endl;
	cin.getline(Name, 30);
	cout << "Enter National_ID:  " << endl;
	cin.getline(accnum, 13);
	cout << "Enter PhoneNumber:  " << endl;
	cin.getline(PhoneNumber, 11);
	cout << "Enter id:  " << endl;
	cin >> id;
	cout << "Enter balance" << endl;
	cin.getline(balance, 10);
	cout << "Enter password" << endl;
	cin.getline(password, 5);
	cout << "operation_type" << endl;
	cin.getline(operation_tybe, 2);

	Pack(outRecord);
	outRecord.Write(f);

	f.seekp(0, ios::beg);
	f.write((char*)&next_del, sizeof(next_del));
	f.close();
}
void customer::update_customer(fstream myfile,VariableLengthRecord record)
{
	
	if (search_customerID()) {

		cout << "Enter Name:  " << endl;
		cin.getline(Name, 30);
		cout << "Enter National_ID:  " << endl;
		cin.getline(accnum, 13);
		cout << "Enter PhoneNumber:  " << endl;
		cin.getline(PhoneNumber, 11);
		cout << "Enter balance" << endl;
		cin.getline(balance, 10);
		cout << "Enter password" << endl;
		cin.getline(password, 5);
		cout << "operation_type" << endl;
		cin.getline(operation_tybe, 2);
		cout << "Enter id:  " << endl;
		cin >> id;

		Pack(record);
		record.Write(myfile);
	}
	else {
		cout << "Non exist";
		return;
	}
	myfile.close();
}

bool customer::search_customerID(fstream myfile,VariableLengthRecord record)
{
	myfile.open("customer.txt", ios::in || ios::binary);
S:
	char decision;
	short searched_id;
	cout << "\aPlease Enter The ID To Search About The Employee \n";
	cin >> searched_id;
	if (myfile.is_open()) {
		do {
			record.ReadHeader(myfile);
			myfile.read((char*)&id, 2);
			if (id == searched_id) {
				myfile.getline(Name, '|');
				myfile.getline(accnum, 13);
				myfile.getline(balance, 10);
				myfile.getline(password, 5);
				myfile.getline(PhoneNumber, 11);
				myfile.getline(operation_tybe, 2);
				cout << "\aWe Have Found The Employee Data \n"
					<< "Name: " << Name << endl
					<< "ID : " << id << endl
					<< "account Nubmer: " << accnum << endl
					<< "balance: " << balance
					<< "password: " << password << endl
					<< "PhoneNumber : " << PhoneNumber << endl
					<< "operation_tybe: " << operation_tybe << endl;
				return true;
			}
			else
			{
				myfile.getline(Name, '|');
				myfile.seekg((sizeof(Name)) + 44);
			}
		} while (!myfile.eof());


	}
	else {
		cout << "ERROR!";
	}
	cout << "\aYou don't have any contacts yet \n";
	do {
		cout << "Are you want to search again ? if yes Enter y else Enter n\n";
	} while (decision != 'y' && decision != 'n');
	cin >> decision;
	if (decision == 'y' || decision == 'Y')
		goto S;
	else
		return false;
	myfile.close();
}
