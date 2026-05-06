#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "Customer.h"
using namespace std;
// make struct to take customer name and id as a data
struct secondaryCustomerIndex
{
	int id;
	char name[20];

	void setData(short i, char n[]) {
		id = i;
		strcpy_s(name,sizeof(name), n);
	}
	bool operator <(const secondaryCustomerIndex& sci)const {
		int cmp = strcmp(name, sci.name);
		if (cmp == 0) {
			return id < sci.id;
	}
		return cmp < 0;
	}
};



//vector to store this data in
vector<secondaryCustomerIndex> storeCustomerSecondaryData;



//add function to add new data to the vector
void addCustomerToSecondary(Customer &c) {
	secondaryCustomerIndex sci;

	sci.setData(c.id,c.fname);

	storeCustomerSecondaryData.push_back(sci);

	sort(storeCustomerSecondaryData.begin(), storeCustomerSecondaryData.end());
}



// load data from vector to customer secondary file
void leadDataToCustomerSecondaryFile(secondaryCustomerIndex& sci) {

	ofstream file; file.open("customersecondary.txt", ios::binary | ios::out | ios::trunc);
	if (!file) {
		cout << "Error creating customersecondary.txt\n";
		return;
	}
	for (int i = 0; i < storeCustomerSecondaryData.size(); i++)
	{

		sci.setData(storeCustomerSecondaryData[i].id, storeCustomerSecondaryData[i].name);
		file.write((char*)&sci, sizeof(sci));
	}
	file.close();
}



// load data from  customer secondary file to vector  file
void leadDataFromCustomerSecondaryFile(secondaryCustomerIndex& sci) {
	storeCustomerSecondaryData.clear();
	ifstream file; file.open("customersecondary.txt", ios::in | ios::binary);
	while (file.read((char*)&sci, sizeof(sci))) {

		storeCustomerSecondaryData.push_back(sci);
	}
	sort(storeCustomerSecondaryData.begin(), storeCustomerSecondaryData.end());
	file.close();
}



//search about the customer by name
int searchByIdInSecondaruReturnIndex(int id) {
	for (size_t i = 0; i < storeCustomerSecondaryData.size(); i++)
	{
		if (storeCustomerSecondaryData[i].id == id) return i;
	}
	return -1;
	
}



int searchByCustomerNameReturnID(char n[]) {
	// 1 2 3 4 5 
   //binary search by id 
	int left = 0,
		right = storeCustomerSecondaryData.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		int cmp = strcmp(n, storeCustomerSecondaryData[mid].name);
		// if the middle = our id return its offset
		if (cmp==0) return storeCustomerSecondaryData[mid].id;

		//if middle less than id move the right hand
		else if (cmp >0) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}




