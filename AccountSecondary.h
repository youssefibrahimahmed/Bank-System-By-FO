#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "Account.h"
using namespace std;

//struct to store customer id and account id in 
struct secondaryAccountIndex {
	int accId, cusId;
	void setData(int ai, int ci) {
		accId = ai;
		cusId = ci;
	}

	bool operator <(const secondaryAccountIndex& sai)const {
		
		if (cusId == sai.cusId)
			return accId < sai.accId;
			return cusId < sai.cusId;
	}
};


//vector to load data on 
vector<secondaryAccountIndex> storeSecondaryAccountIndex;




//add function to add new data to the vector
void addAccountToSecondary(account& a) {
	
	for (size_t i = 0; i < storeSecondaryAccountIndex.size(); i++)
	{
		if (storeSecondaryAccountIndex[i].accId == a.accountId)return;
	}
	
	secondaryAccountIndex sai;

	sai.setData(a.accountId, a.customerId);

	storeSecondaryAccountIndex.push_back(sai);

	sort(storeSecondaryAccountIndex.begin(), storeSecondaryAccountIndex.end());
}



// load data from vector to account secondary file
void leadDataToAccountSecondaryFile(secondaryAccountIndex& sai) {

	ofstream file; file.open("accountsecondary.txt", ios::binary | ios::out | ios::trunc);
	if (!file) {
		cout << "Error creating accountsecondary.txt\n";
		return;
	}
	for (int i = 0; i < storeSecondaryAccountIndex.size(); i++)
	{

		sai.setData(storeSecondaryAccountIndex[i].accId, storeSecondaryAccountIndex[i].cusId);
		file.write((char*)&sai, sizeof(sai));
	}
	file.close();
}



// load data from  customer secondary file to vector  file
void leadDataFromAccountSecondaryFile(secondaryAccountIndex& sai) {
	storeSecondaryAccountIndex.clear();
	ifstream file; file.open("accountsecondary.txt", ios::in | ios::binary);
	while (file.read((char*)&sai, sizeof(sai))) {

		storeSecondaryAccountIndex.push_back(sai);
	}
	sort(storeSecondaryAccountIndex.begin(), storeSecondaryAccountIndex.end());
	file.close();
}


//search about the customer by customer id into secondary vector and return its index at vector
int searchByCustomerIdReturnIndex(int i) {


	int left = 0,
		right = storeSecondaryAccountIndex.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		// if the middle = our id return its offset
		if (storeSecondaryAccountIndex[mid].cusId == i) return mid;

		//if middle less than id move the right hand
		else if (i > storeSecondaryAccountIndex[mid].cusId) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}


//function to search about the account  into secondary file  by id and return its index at vector  
// error because wwe sort  it depending on accid not cusid
int searchAccountSecondaryById(int i) {
	// 1 2 3 4 5 
   //binary search by id 
	int left = 0,
		right = storeSecondaryAccountIndex.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		// if the middle = our id return its offset
		if (storeSecondaryAccountIndex[mid].accId == i) return mid;

		//if middle less than id move the right hand
		else if (i > storeSecondaryAccountIndex[mid].accId) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}

