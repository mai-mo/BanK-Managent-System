#include <string.h>
#include<fstream>

#include "varlen.h"
#include "customer.h"
customer::customer()
{//2
	id = 0;
	name[0] = 0;
}

customer::customer(short cid, char cname[], char ctype, int cpassword, int cbalance, int cphone, int caccont_number)
{ //1
	id = cid;
	strcpy(name, name);
	password = cpassword;
	balance = cbalance;
	phone = cphone;
	accont_number = caccont_number;
}


// initialize a VariableLengthRecord to be used for Persons
void customer::InitRecord(VariableLengthRecord & record)
{
	//3
	record.init(7);
	record.AddField(0, 'F', 2);  // Fixed :  F , Length Indicator : L , Delimited  D
	record.AddField(1, 'D', '|');
	record.AddField(2, 'D', '|');
	record.AddField(3, 'D', '|');
	record.AddField(4, 'D', '|');
	record.AddField(5, 'D', '|');
	record.AddField(6, 'D', '|');

}

int customer::Pack(VariableLengthRecord &record)
{
	// pack the fields into a VariableLengthRecord, return  ( 1 )TRUE if all succeed, FALSE o/w
	int result, recordSize = 0;   // Lenght Indicator  id(short) = 120 , name = AMES , Delimiter = 1 = > 7
	//4
	recordSize = 22 + strlen(name) + 7;

	record.Clear(recordSize);

	result = record.Pack(0, (void*)&id, sizeof(short))

		&& record.Pack(1, (void*)name, strlen(name))

		&&record.Pack(2, (void*)&password, sizeof(int))

		&&record.Pack(3, (void*)&balance, sizeof(double))

		&&record.Pack(4, (void*)&phone, sizeof(int))


		&&record.Pack(5, (void*)&accont_number, sizeof(int));

	return result;
}

int customer::Unpack(VariableLengthRecord& record)
{
	int result;
	result = record.Unpack(0, (char*)&id)
	&& record.Unpack(1, name, true)
	&&record.Unpack(2, (char*)&password)
	&&record.Unpack(3, (char*)&balance)
	&& record.Unpack(4, (char*)&phone)
	
	&& record.Unpack(5, (char*)&accont_number);

	return result;
}

void customer::Print(ostream& stream)
{
	stream << "customer:"
		<< "\tId '" << id << "'\n"
		<< "\tName '" << name << "'\n"
	 "\tpassword '" << password << "'\n"
	 "\tbalance '" << balance << "'\n"
	 "\tphone " << phone << "'\n"
	"\taccount number '" << accont_number << "'\n";
}
void customer::create_account(fstream& stream) {
	
		cout << "enter your name \n"; cin.getline(name, 11);
		cout << "enter your ID\n"; cin >> id;
		cout << "enter your password \n"; cin >> password;
		cout << "enter your balance\n"; cin >> balance;
		cout << "enter your phone \n "; cin >> phone;
		cout << "enter your accont_number \n"; cin >> accont_number;
		stream.write(name, strlen(name)); stream.put('|');
		stream.write((char*)&id, 2); stream.put('|');
		stream.write((char*)&password, 4); stream.put('|');
		stream.write((char*)&balance, 8); stream.put('|');
		stream.write((char*)&phone, 4); stream.put('|');
		stream.write((char*)&accont_number, 4); stream.put('|');
	
}

void customer::deposit_withdraw(int n)
{
	int amt;
	int found = 0;
	customer client;
	fstream File;
	File.open("customer.dat", ios::binary | ios::in | ios::out);
	while (File.read((char*)&client, sizeof(customer)) && found == 0)
	{
		if (client.accont_number == n)
		{
			client.show_account(File);
			cout << "Enter 1 for depsit OR 2 for withdraw:" << endl;
			cin >> option;
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				client.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = client.retdeposit() - amt;
				if (bal > client.balance)
					cout << "Insufficience balance";
				else
					client.draw(amt);
			}
			int pos = -1 * sizeof(client);
			File.seekp(pos, ios::cur);
			File.write((char*)&client, sizeof(customer));
			cout << "Record Updated \n";
			found = 1;
		}
	}
	File.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";


}
void customer::dep(int x)
{
	int deposit = 0;
	  deposit += x;
}

void customer::draw(int x)
{
	int draw;
	draw -= x;
}


int customer::retdeposit()
{
	return operation_tybe;
}
void customer::show_account(fstream &in)
{

	customer c1;
	in.seekg(0, ios::beg);
	in.read((char*)&c1, sizeof(c1));
	do {

		cout << "\nAccount Nnyber is:. : " << c1.accont_number;
		cout << "\nAccount  Name = : " << c1.name;
		cout << "\nBalance is : " << c1.balance;
		cout << "\nid is " << c1.id;
	} while (!in.eof());
	in.clear();

}
