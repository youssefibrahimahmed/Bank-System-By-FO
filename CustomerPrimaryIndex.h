#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Customer.h"



// make struct to take customer id and offset as a data
struct primaryCustomerIndex
{
	int id, offset;

	void setData(short i, short o) {
		id = i;
		offset = o;
	}
	bool operator <(const primaryCustomerIndex& pci)const {
		return id < pci.id;
	}
};



//vector to store this data in
vector<primaryCustomerIndex> storeCustomerData;



//add function to add new data to the vector
void addCustomerToPrimary(Customer& c,int offset) {

	primaryCustomerIndex pci;
	
	pci.setData(c.id, offset);
	
	storeCustomerData.push_back(pci);
	
	sort(storeCustomerData.begin(), storeCustomerData.end());
}


//function to search about the customer into primary file by id and return its offset 
int searchById(int i) {

	//  l   r     r
	  //0 1 2 3 4 5 6      target =3 l=0 ,r=6 mid=3
	 // 1 2 3 4 5 7 10
	//binary search by id 
	int left = 0,
		right = storeCustomerData.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		
		// if the middle = our id return its offset
		if (storeCustomerData[mid].id == i) return storeCustomerData[mid].offset;
		
		//if middle less than id move the right hand
		else if (i> storeCustomerData[mid].id) left = mid+1;
		
		//if middle bigger than id move the left hand
		else right= mid-1;
	}
	return -1;
}



int searchByIdReturnIndex(int i) {

   
	int left = 0,
		right = storeCustomerData.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		// if the middle = our id return its offset
		if (storeCustomerData[mid].id == i) return mid;

		//if middle less than id move the right hand
		else if (i > storeCustomerData[mid].id) left = mid + 1;

		//if middle bigger than id move the left hand
		else right = mid - 1;
	}
	return -1;
}



// load data from vector to customer primary file
void leadDataToCustomerPrimaryFile(primaryCustomerIndex &pci) {

	ofstream file;file.open("customerprimary.txt", ios::binary |ios::out| ios::trunc);
	if (!file) {
		cout << "Error creating customerprimary.txt\n";
		return;
	}
	for (int i = 0; i < storeCustomerData.size(); i++)
	{
		pci.setData(storeCustomerData[i].id, storeCustomerData[i].offset);
		file.write((char*)&pci, sizeof(pci));
	}
	file.close();
}



// load data from  customer primary file to vector  file
void leadDataFromCustomerPrimaryFile(primaryCustomerIndex &pci) {
	storeCustomerData.clear();
	ifstream file;file.open("customerprimary.txt",ios::in| ios::binary);
	while (file.read((char*)&pci, sizeof(pci))) {
		
		storeCustomerData.push_back(pci);
	}
		sort(storeCustomerData.begin(), storeCustomerData.end());
		file.close();
}



void updateCustomerPrimaryOffset(Customer &c,short offset) {

	//delete the record from the vector
	int idx = searchByIdReturnIndex(c.id);
	storeCustomerData.erase(storeCustomerData.begin() + idx);

	addCustomerToPrimary(c, offset);

}

