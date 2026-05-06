#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;



// struct to enter customer data 
struct Customer
{
	int id, age;
	char fname[20], lname[20], city[15];

	short sizeofRecord() {
		short fixedSize = sizeof(id) + sizeof(age);
		short variableSize = strlen(fname) + strlen(lname) + strlen(city);
		short dilimeterSize = 5; // Assuming we use a delimiter (e.g., comma) between fields
		return fixedSize + variableSize + dilimeterSize;
	}

	void setData(bool skipId=false) {


		if (!skipId) {
			cout << "Enter id: "; cin >> id;
		}
		cin.ignore(); // Ignore the newline character left in the buffer
		
		cout << "Enter first name: "; cin.getline(fname, 20);
		cout << "Enter last name: "; cin.getline(lname, 20);
		cout << "Enter age: "; cin >> age;
		cin.ignore(); // Ignore the newline character left in the buffer
		cout << "Enter city: "; cin.getline(city, 15);
	}

	void showData() {
		cout << "\n------------- Customer Data --------------\n";
		cout << "ID         : " << id << endl;
		cout << "First Name : " << fname << endl;
		cout << "Last Name  : " << lname << endl;
		cout << "city       : " << city << endl;
		cout << "Age        : " << age << endl;
	}
};



// function to read each record from the file and display it
bool readFromCustomerFile(Customer& c, fstream& file) {
	if (!file) {
		return false;
	}

	// Read binary Customer records until EOF
	file.read((char*)&c.id, sizeof(c.id));
	file.get();
	file.getline(c.fname, 20, '|');
	file.getline(c.lname, 20, '|');
	file.getline(c.city, 15, '|');
	file.read((char*)&c.age, sizeof(c.age));
	file.get();

	if (!file) {
		return false;
	}


	return true;
}



// function to write record
void writeCusRecord(fstream& file, Customer& c) {
	file.write((char*)&c.id, sizeof(c.id)); file.put('|');
	file.write(c.fname, strlen(c.fname)); file.put('|');
	file.write(c.lname, strlen(c.lname)); file.put('|');
	file.write(c.city, strlen(c.city)); file.put('|');
	file.write((char*)&c.age, sizeof(c.age)); file.put('|');
}



// function to intiate the head to the first of the file
void intiateCustomerFile() {
	// Try to open existing file for reading; if it fails, create it and write the head
	fstream file("customer.txt", ios::in | ios::binary);
	short head = -1; // Initialize head to -1 to indicate an empty file
	if (!file) {
		file.open("customer.txt", ios::out | ios::binary);
		file.write((char*)&head, sizeof(head));
	}
	file.close();
}



//function to mark the record as deleted
void markRecordAsDeleted(Customer&c,fstream&file, short offset) {
	//store the head data
	short head;
	file.seekg(0, ios::beg);
	file.read((char*)&head, sizeof(head));


		//calculate the size of the record
		short size;
		//go to record offset
		file.seekg(offset, ios::beg);
		readFromCustomerFile(c, file);
		size = c.sizeofRecord();

		//mark the deleted record id|* oldhead size
		file.seekp(offset+ sizeof(int) + 1);
		file.put('*');
		file.write((char*)&head, sizeof(head));
		file.write((char*)&size, sizeof(size));

		//update the head
		file.seekp(0, ios::beg);
		file.write((char*)&offset, sizeof(offset));

		return;

}

