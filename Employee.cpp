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

void Employee::update_employee()
{
	
	VariableLengthRecord& record;
	string name;
	short choose;
	ifstream myfile;
	myfile.open("Employee.txt", ios::out || ios::in || ios::binary);
	if (search_employeeID()) {
		
		cout << "Enter 1 for update id" << endl << "2 for update Name" << endl << "3 for update national id" << endl << "4 for update phone Number" << endl;
		cin >> choose;
		switch (choose) {
		case 1:
			myfile.seekp(-2, ios::cur);
			setID();
			record.Pack(0, id, 2);
			myfile.seekp(-2, ios::cur);
			record.Write(myfile);
			break;
		case 2:
			cout << "name: \n";
			cin >> name;
			
			myfile.getline(Name, '|');
			if (strlen(name) > strlen(Name)) {
				record.Pack(1, Name, sizeof(Name));
				Pack(record);
				myfile.write(0, ios::end);
				record.Write(myfile);
			}
			break;
		case 3:
			setNationalID();
			record.Pack(2, national_ID, 14);
			myfile.seekp(2, ios::cur);
			myfile.getline(Name, '|');
			myfile.seekp(-((sizeof(Name))+2), ios::cur);
			record.Write(myfile);
			break;
		case 4:
			setPhone();
			record.Pack(3, phone, 11);
			myfile.seekp(2, ios::cur);
			myfile.getline(Name, '|');
			myfile.seekp(-((sizeof(Name)) + 2 + 14), ios::cur);
			record.Write(myfile);
			break;
		}
	}
	else {
		cout << "Non exist";
		return;
	}
}

void Employee::search_employee()
{
	ifstream myfile;
	myfile.open("Employee.txt", ios::in||ios::binary);
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
				myfile.getline(Name, '|');
				myfile.getline(national_ID, 14);
				myfile.getline(phone, 11);
				cout << "\aWe Have Found The account \n"
					<< "Name: " << Name << endl
					<< "ID : " << id << endl
					<< "National_id: " << national_ID << endl
					<< "Phone: " << phone;
				i = 0;
				break;
			}
			else
			{
				myfile.getline(Name, '|');
				myfile.seekg(14 + 11);
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
		if (decision == 'y'||decision == 'Y')
			goto S;
		else
			return;
	}
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
