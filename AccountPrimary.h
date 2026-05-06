#pragma once
#include "Account.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Customer.h"

using namespace std;
//primary index for account
struct accountPrimaryIndex {
	int accId, offSet;

	void setData(int ai, int os) {
		accId = ai;
		offSet = os;
	}
	bool operator<(const accountPrimaryIndex& api)const {
		return accId < api.accId;
	}
};


// vector to store this data in
vector<accountPrimaryIndex> storeAccountData;


//function to set account data 
void setAccountData(Customer& c, account &acc,bool skip=false) {
	
	
	if (!skip) {

		if (storeAccountData.empty()) {
			acc.accountId = 1001;
		}
		else
			acc.accountId = storeAccountData[storeAccountData.size() - 1].accId + 1;
	}
	acc.setAccount(c.id,acc.accountId ,skip);
}


//add function to add new data to the vector
void addAccountToPrimary(account& a, int offset) {

	accountPrimaryIndex api;

	api.setData(a.accountId, offset);

	storeAccountData.push_back(api);

	sort(storeAccountData.begin(), storeAccountData.end());

}


//function to search about the account into primary file by id and return its offset 
int searchAccountById(int i) {
	// 1 2 3 4 5 
   //binary search by id 
	int left = 0,
		right = storeAccountData.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		// if the middle = our id return its offset
		if (storeAccountData[mid].accId == i) return storeAccountData[mid].offSet;

		//if middle less than id move the right hand
		else if (i > storeAccountData[mid].accId) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}

//function to search about the account into primary file by id and return its index at vector  
int searchAccountByIdReturnIndex(int i) {


	int left = 0,
		right = storeAccountData.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		// if the middle = our id return its offset
		if (storeAccountData[mid].accId == i) return mid;

		//if middle less than id move the right hand
		else if (i > storeAccountData[mid].accId) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}

// load data from vector to account primary file
void leadDataToAccountPrimaryFile(accountPrimaryIndex& pci) {

	ofstream file; file.open("accountprimary.txt", ios::binary | ios::out | ios::trunc);
	if (!file) {
		cout << "Error creating accountprimary.txt\n";
		return;
	}
	for (int i = 0; i < storeAccountData.size(); i++)
	{
		pci.setData(storeAccountData[i].accId, storeAccountData[i].offSet);
		file.write((char*)&pci, sizeof(pci));
	}
	file.close();
}

// load data from  customer primary file to vector  file
void leadDataFromAccountPrimaryFile(accountPrimaryIndex& api) {
	storeAccountData.clear();
	ifstream file; file.open("accountprimary.txt", ios::in | ios::binary);
	while (file.read((char*)&api, sizeof(api))) {

		storeAccountData.push_back(api);
	}
	sort(storeAccountData.begin(), storeAccountData.end());
	file.close();
}

void updateAccountPrimaryOffset(account& a, short offset) {

	//delete the record from the vector
	int idx = searchAccountByIdReturnIndex(a.accountId);
	storeAccountData.erase(storeAccountData.begin() + idx);

	addAccountToPrimary(a, offset);

}

