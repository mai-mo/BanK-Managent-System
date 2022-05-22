#include<iostream>
#include<fstream>
#include<string>
#include"varlen.h"
//#include"Employee.h"
//#include"Customer.h"

using namespace std;

int main()
{

	VariableLengthRecord outRecord, inRecord;

	int X , Y;

	cout<<"*** Bank Management System ***"<<endl<<endl<<endl;
	

	cout<<"Select The File : "<<endl;
	cout<<"1.Customer"<<endl;
	cout<<"2.Employee"<<endl<<endl;
	cout<<"Please, Enter Your Choice : ";
	cin>>X; 
	
	
	if(X==1)
	{
	fstream File;
	Customer customer;

		File.open("Customer.txt",ios::in | ios::out | ios::binary | ios::app );

		cout<<"\n\n Select One Option Below : "<<endl;
		cout<<"1.Add a New Record "<<endl;
		cout<<"2.Deposit With Draw "<<endl;
		cout<<"3.Show a Record "<<endl;
		cout<<"4.Delete a Record "<<endl;
		cout<<"5.Search For a Record "<<endl;
		cout<<"6.Update a Record "<<endl<<endl;
		cout<<"Please, Enter Your Choice : ";
		cin>>Y;
		cout<<endl<<endl;

		

		switch(Y)
		{

		case 1:
			customer.create_account(File);
			break;

		case 2:
			
			int NUM;
			cout<<"please, Enter Your Account Number :";
			cin>>NUM;

			customer.deposit_withdraw(NUM);
			break;

		case 3:
			customer.show_account(File);
			break;

		case 4:
			customer.Delete();
			break;

		case 5:
			customer.Search();
			break;

		case 6:
			customer.Update();
			break;

			default :
				cout<<"\n ERROR! .. Invalid Choice"<<endl;

		}
		
	}

	else if(X==2) 
	{
	
	fstream File;
	Employee employee;

		File.open("Employee.txt",ios::in | ios::out | ios::binary | ios::app );

		cout<<"\n\n Select One Option Below : "<<endl;
		cout<<"1.Add an Employee "<<endl;
		cout<<"2.Delete an Employee "<<endl;
		cout<<"3.Update an Employee "<<endl;
		cout<<"4.Search For an Employee "<<endl;
		cout<<"5.Display All "<<endl<<endl;
		cout<<"please, Enter Your Choice : ";
		cin>>Y;
		cout<<endl<<endl;


		switch(Y)
		{

		case 1:
			employee.add_employee(File,outRecord);
			break;

		case 2:
			
			short RRN;
			cout<<" please, Enter Your ID :";
			cin>>RRN;

			employee.Delete(File,RRN);
			break;

		case 3:
			employee.update_employee(File);
			break;

		case 4:
			employee.search_employee(File);
			break;

		case 5:
			employee.display_all();
			break;

			default :
				cout<<"\n ERROR! .. Invalid Choice "<<endl;

		}
	
	}

	else
		cout<<"\n ERROR! .. Invalid Choice "<<endl;

	cout<<"THANK YOU"<<endl;



}