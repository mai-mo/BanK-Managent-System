#include "Employee.h"
#include <iostream>
#include <fstream>
#include <string>
#include "varlen.h"
using namespace std;

void main()
{
	Employee person;
	short	id;
	string Name;
	string national_ID;
	string phone;

	VariableLengthRecord outRecord, inRecord;

	

	person.InitRecord(outRecord);//
	
	cout << "pack person " << person.Pack(outRecord) << endl;//


	#pragma region Writing (Packing)

	//read from object and write to record

	ofstream TestOut("deltext.dat", ios::out | ios::binary);

	outRecord.WriteHeader(TestOut);  // Only Once.//
	
	outRecord.Write(TestOut);//
	person.Print(cout);

	person.id = 130;
	strcpy_s(person.Name, "Ahmed");
	
	person.Pack(outRecord);  // Precord  => array  of  char   120Ames| , 130Ahmed|

	outRecord.Write(TestOut);

	person.Print(cout);

	TestOut.close();

	#pragma endregion

	#pragma region Reading (UnPacking)
	//read from record and read to object

	ifstream TestIn ("deltext.dat", ios::in | ios::binary);
	inRecord.ReadHeader(TestIn);
	
	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<person.Unpack(inRecord)<<endl;	
	person.Print(cout);


	cout <<"read "<<inRecord.Read(TestIn)<<endl;
	cout <<"unpack "<<person.Unpack(inRecord)<<endl;
	person.Print(cout);
	#pragma endregion

	TestIn.close();
}
