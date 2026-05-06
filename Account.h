#pragma once
#include "Customer.h"
#include <algorithm>



// struct to insert the account data with 
struct account
{
	int balance,accountId,customerId;
	char type[15];

	// function to set account data
	void setAccount(int ci,int ai,bool skip=false) {
		if(!skip)
		{
			customerId = ci;
			accountId = ai;
		}
		cout << "Enter Account Balance: "; cin >> balance;
		cin.ignore();
		cout << "Enter Account Type: "; cin.getline(type, 15);
	}
	void showAccount() {
		cout << "\n-----------Account Details:------------\n";
		cout << "Account ID      : " << accountId << endl;
		cout << "Customer ID     : " << customerId << endl;
		cout << "Account Balance : " << balance<< endl;
		cout << "Account Type    : " << type << endl;
		cout << "----------------------------------------\n";
	}
	short sizeofRecord() {
		short sizeOfFixed = sizeof(balance) + sizeof(accountId)+sizeof(customerId);
		short sizeOfChanged = strlen(type);
		short sizeOfDelimiters = 4;
		return (sizeOfChanged + sizeOfDelimiters + sizeOfFixed);
 	}
};
// function to read record from file
bool readFromAccountFile(account& a, fstream& file) {
	if (!file) {
		return false;
	}
	// id|type|cusid|balance
	// Read binary Customer records until EOF
	file.read((char*)&a.accountId, sizeof(a.accountId)); file.get();
	file.getline(a.type, 15, '|');
	file.read((char*)&a.customerId, sizeof(a.customerId)); file.get();
	file.read((char*)&a.balance, sizeof(a.balance)); file.get();
	if (!file) {
		return false;
	}


	return true;
}


// function to write record
void writeAccountRecord(fstream& file, account& a) {
	cout << "The OFFSET Of The New Record: " << file.tellp() << endl;
	file.write((char*)&a.accountId, sizeof(a.accountId)); file.put('|');
	file.write(a.type, strlen(a.type)); file.put('|');
	file.write((char*)&a.customerId, sizeof(a.customerId)); file.put('|');
	file.write((char*)&a.balance, sizeof(a.balance)); file.put('|');
}


// function to intiate the head to the first of the file
void intiateAccountFile() {
	// Try to open existing file for reading; if it fails, create it and write the head
	fstream file("account.txt", ios::in | ios::binary);
	short head = -1; // Initialize head to -1 to indicate an empty file
	if (!file) {
		file.open("account.txt", ios::out | ios::binary);
		file.write((char*)&head, sizeof(head));
	}
	file.close();
}


//function to mark the record as deleted
void markAccountRecordAsDeleted(account& a, fstream& file, short offset) {
	//store the head data
	short head;
	file.seekg(0, ios::beg);
	file.read((char*)&head, sizeof(head));


	//calculate the size of the record
	short size;
	//go to record offset
	file.seekg(offset, ios::beg);
	readFromAccountFile(a, file);
	size = a.sizeofRecord();

	//mark the deleted record id|* oldhead size
	file.seekp(offset + sizeof(int) + 1);
	file.put('*');
	file.write((char*)&head, sizeof(head));
	file.write((char*)&size, sizeof(size));

	//update the head
	file.seekp(0, ios::beg);
	file.write((char*)&offset, sizeof(offset));

	return;

}

