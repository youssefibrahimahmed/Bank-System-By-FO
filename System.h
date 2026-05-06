	#pragma once

	#include "Customer.h"
	#include "CustomerPrimaryIndex.h"
	#include "CustomerSecondary.h"
	#include "Account.h"
	#include "AccountPrimary.h"
	#include "AccountSecondary.h"
	#include "Algorithm"
	//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
	//====================================== ADD SECTION ======================================\\
                             
								  /*-----Add Customer Section------*/
								  
	//function to Add At Deleted Record
	void addCustomerAtDeletedRecord(fstream& file, Customer& c) {

		short head, oldhead, size;

		Customer deletedCustomer;

		//Go to last Deleted Record
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(head));

		// read the deleted one to calculate the size
		file.seekg(head + sizeof(int) + 2 * sizeof(char) + sizeof(short), ios::beg);
		file.read((char*)&size, sizeof(size));
		// id|* offset size	


		// if the deleted record bigger than old one 
		if (size >= c.sizeofRecord()) {

			//go to the start of the record to read the old head
			file.seekg(head + sizeof(int) + 2 * sizeof(char), ios::beg);

			//read the old head
			file.read((char*)&oldhead, sizeof(oldhead));

			//write the data at the deleted record
			file.seekp(head, ios::beg);
			
			int offset = file.tellp();
			//add customer data to both primary and secondary index
			addCustomerToPrimary(c, offset);
			addCustomerToSecondary(c);
			writeCusRecord(file, c);
			short diff = size - c.sizeofRecord();
			if (diff >= 10) {
				short posOfWasteSpace = file.tellp();
				file.seekp(posOfWasteSpace+sizeof(int) + 1, ios::beg);
				file.put('*');// unique char
				file.write((char*)&oldhead, sizeof(oldhead));//write the oldhead
				file.write((char*)&diff, sizeof(diff));//write the size

				//update the head
				file.seekp(0, ios::beg);
				file.write((char*)&posOfWasteSpace, sizeof(posOfWasteSpace));
				return;
			}
			else
			{
				//back to the start of the file to store the offset of the last deleted record
				file.seekp(0, ios::beg);
				file.write((char*)&oldhead, sizeof(oldhead));
				return;
			}
		}
		else {

			short cur, prev;
			file.seekg(0, ios::beg);

			file.read((char*)&cur, sizeof(cur));
			prev = -1;

			while (cur != -1) {

				//go to read the last deleted record to compare between size and last one
				file.seekg(cur, ios::beg);
				file.seekg(cur + sizeof(int) + 2 * sizeof(char) + sizeof(short), ios::beg);
				file.read((char*)&size, sizeof(size));

				//in case the deleted one not suitable
				if (size < c.sizeofRecord()) {
					prev = cur;
					file.seekg(cur + sizeof(int) + 2, ios::beg);
					file.read((char*)&cur, sizeof(cur));
				}
				else {

					// read the oldhead to update the previous deleted record
					file.seekg(cur + sizeof(int) + 2, ios::beg);

					//store the old offset of the head AT  HEAD ->
					file.read((char*)&head, sizeof(head));

					//write the new record instead of deleted one
					file.seekp(cur);
					writeCusRecord(file, c);
					short diff = size - c.sizeofRecord();
					if (diff >= 10) {
						short posOfWasteSpace = file.tellp();

						//add customer data to both primary and secondary index
						addCustomerToPrimary(c,cur);
						addCustomerToSecondary(c);

						file.seekp(posOfWasteSpace+sizeof(int) + 1, ios::beg);
						file.put('*');// unique char
						file.write((char*)&head, sizeof(head));//write the oldhead
						file.write((char*)&diff, sizeof(diff));//write the size
						file.seekp(0, ios::beg);

						//update the head
						file.write((char*)&posOfWasteSpace, sizeof(posOfWasteSpace));
						return;
					}


					//go to update the last deleted record with offset

					file.seekp(prev + sizeof(int) + 2);
					file.write((char*)&head, sizeof(head));
					return;
				}
			}
			if (cur == -1) {
				file.seekp(0, ios::end);
				int offset = file.tellp();
				addCustomerToPrimary(c, offset);
				addCustomerToSecondary(c);
				writeCusRecord(file, c);
				return;
			}
		}
	}

	// function to add record to the Customer file and vector
	void addRecordToCustomerFile(fstream& file, Customer& c) {
		int check;
		c.setData();
		while (true)
		{
		check = searchById(c.id);
		if (check != -1) {
			cout << "This id already exists, please enter another one: "; cin >> c.id;
			continue;
		}
		break;
		}
		short head;
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(head));

		//if there is not deleted records -> add to eof
		if (head == -1) {
			file.seekp(0, ios::end);
			int offset = file.tellp();
			addCustomerToPrimary(c, offset);
			addCustomerToSecondary(c);
			writeCusRecord(file, c);
			return;
		}
		else {
			addCustomerAtDeletedRecord(file, c);
		}


	}
		
									/*-----Add Account Section------*/

	//function to Add At Deleted Record
	void addAccountAtDeletedRecord(fstream& file, account& a) {

		short head, oldhead, size;

		account deletedCustomer;

		//Go to last Deleted Record
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(head));

		// read the deleted one to calculate the size
		file.seekg(head + sizeof(int) + 2 * sizeof(char) + sizeof(short), ios::beg);
		file.read((char*)&size, sizeof(size));
		// id|* offset size	


		// if the deleted record bigger than old one 
		if (size >= a.sizeofRecord()) {

			//go to the start of the record to read the old head
			file.seekg(head + sizeof(int) + 2 * sizeof(char), ios::beg);

			//read the old head
			file.read((char*)&oldhead, sizeof(oldhead));

			//write the data at the deleted record
			file.seekp(head, ios::beg);
			
			int offset = file.tellp();
			//add customer data to both primary and secondary index
			addAccountToPrimary(a, offset);
			addAccountToSecondary(a);
			writeAccountRecord(file,a);
			short diff = size - a.sizeofRecord();
			if (diff >= 10) {
				short posOfWasteSpace = file.tellp();
				file.seekp(posOfWasteSpace + sizeof(int) + 1, ios::beg);
				file.put('*');// unique char
				file.write((char*)&oldhead, sizeof(oldhead));//write the oldhead
				file.write((char*)&diff, sizeof(diff));//write the size

				//update the head
				file.seekp(0, ios::beg);
				file.write((char*)&posOfWasteSpace, sizeof(posOfWasteSpace));
				return;
			}
			else
			{
				//back to the start of the file to store the offset of the last deleted record
				file.seekp(0, ios::beg);
				file.write((char*)&oldhead, sizeof(oldhead));
				return;
			}
		}
		else {

			short cur, prev;
			file.seekg(0, ios::beg);

			file.read((char*)&cur, sizeof(cur));
			prev = -1;

			while (cur != -1) {

				//go to read the last deleted record to compare between size and last one
				file.seekg(cur, ios::beg);
				file.seekg(cur + sizeof(int) + 2 * sizeof(char) + sizeof(short), ios::beg);
				file.read((char*)&size, sizeof(size));

				//in case the deleted one not suitable
				if (size < a.sizeofRecord()) {
					prev = cur;
					file.seekg(cur + sizeof(int) + 2, ios::beg);
					file.read((char*)&cur, sizeof(cur));
				}
				else {

					// read the oldhead to update the previous deleted record
					file.seekg(cur + sizeof(int) + 2, ios::beg);

					//store the old offset of the head AT  HEAD ->
					file.read((char*)&head, sizeof(head));

					//write the new record instead of deleted one
					file.seekp(cur);
					writeAccountRecord(file, a);
					short diff = size - a.sizeofRecord();
					if (diff >= 10) {
						short posOfWasteSpace = file.tellp();

						//add customer data to both primary and secondary index
						addAccountToPrimary(a, cur);
						addAccountToSecondary(a);

						file.seekp(posOfWasteSpace + sizeof(int) + 1, ios::beg);
						file.put('*');// unique char
						file.write((char*)&head, sizeof(head));//write the oldhead
						file.write((char*)&diff, sizeof(diff));//write the size
						file.seekp(0, ios::beg);

						//update the head
						file.write((char*)&posOfWasteSpace, sizeof(posOfWasteSpace));
						return;
					}


					//go to update the last deleted record with offset

					file.seekp(prev + sizeof(int) + 2);
					file.write((char*)&head, sizeof(head));
					return;
				}
			}
			if (cur == -1) {
				file.seekp(0, ios::end);
				int offset = file.tellp();
				addAccountToPrimary(a, offset);
				addAccountToSecondary(a);
				writeAccountRecord(file, a);
				return;
			}
		}
	}

	// function to add record to the Account file and vector
	void addRecordToAccountFile(fstream& file, Customer& c,bool skipid=false) {
		int id; 
		account acc;
		// first check if the user has an account or no
		if (!skipid)
		{
			cout << "Enter Your ID To Check If You Have An Account Or No: "; cin >> id;
			c.id = id;
		}
		else {
			id = c.id;
		}
	int check =	searchById(id);
	if (check == -1) {
		cout << "Not Exist, Make An Account First\n";
		return;
		}
	else {
		setAccountData(c, acc);
		short head;
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(head));

		//if there is not deleted records -> add to eof
		if (head == -1) {
			file.seekp(0, ios::end);
			int offset = file.tellp();
			addAccountToPrimary(acc, offset);
			addAccountToSecondary(acc);
			
			writeAccountRecord(file, acc);
			return;
		}
		else {
			addAccountAtDeletedRecord(file, acc);
		}

	}
	}


	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
	//====================================== SEARCH SECTION ======================================\\

									/*-----Search Customer Section------*/
	
	void searchCustomerById(fstream& file, Customer& c) {
		int id;
		cout << "Enter Customer ID: "; cin >> id;
		int cOffset = searchById(id);
		if (cOffset == -1) {
			cout << "This Customer Is Not Found\n";
			return;
		}
		else {
			file.seekg(cOffset);
			readFromCustomerFile(c, file);
			c.showData();
			return;
		}
	}
	void searchCustomerByName(char n[],fstream&file,Customer &c) {
		bool flag = false;
		int counter = 1;

		// display all names matches the target-?
		for (size_t i = 0; i < storeCustomerSecondaryData.size(); i++)
		{
			int  cmp = strcmp(storeCustomerSecondaryData[i].name, n);
			if (cmp == 0) {
				cout << counter << " ) ID: " << storeCustomerSecondaryData[i].id << endl;
				flag = true;
				counter++;
			}
		}
		if (flag) {
			cout << "All IDs Matches This Names\n";
			cout << "Choose Your Account\n";
			searchCustomerById(file, c);
			return;
		}
		else {
			cout << "There Is No Exist For This Name\n";
			return;
		}
	}

									/*-----Search Account Section------*/
	void searchAccountByAccountId(fstream& accfile, account& acc, int id) {
		int offset = searchAccountById(id); 

			if (offset != -1) {
				accfile.seekg(offset);
				readFromAccountFile(acc, accfile);
				acc.showAccount();
				return;
			}
			else {
				cout << "Can't Find This Account\n";
			}
	}

	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
	//======================================Display SECTION======================================\\

								  /*=======Display Customer Section=======*/  

	// function to display all records from the Customer file
	void displayAllCustomerRecords(fstream& file) {

		Customer c;
		if (!file) {
			cerr << "Empty File\n";
			return;
		}

	  
		for (int i = 0; i < storeCustomerData.size(); i++)
		{

			file.seekg(storeCustomerData[i].offset,ios::beg);
			readFromCustomerFile(c, file);
			if (file.fail()) break;
				c.showData();
			cout << "----------------------------------------\n";
		}


	}

								 /*-----Display Account Section------*/

	// function to display all records from the Account file
	void displayAllCustomerAccountRecords(fstream& accfile,int id) {
		account acc;
		Customer c;
		bool flag = false;
		if (!accfile) {
			cerr << "Empty File\n";
			return;
		}
		
		for (size_t i = 0; i < storeSecondaryAccountIndex.size(); i++)
		{
			if (storeSecondaryAccountIndex[i].cusId == id) {
				flag = true;
				int offset=	searchAccountById(storeSecondaryAccountIndex[i].accId);
				accfile.seekg(offset);
				readFromAccountFile(acc, accfile);
				acc.showAccount();
			}
		}
		if (!flag) {
			cout << "This Customer Don't Have Any Account Yet\n"; return;
		}


	}

	void displayTopFiveRecords(fstream& file) {
		Customer c;
		if (!file) {
			cerr << "Empty File\n";
			return;
		}
		int limit= min((int)storeCustomerData.size(), 5);
		for (int i = 0; i <limit; i++)
		{
			file.seekg(storeCustomerData[i].offset, ios::beg);
			readFromCustomerFile(c, file);
			if (file.fail()) break;
			c.showData();
			cout << "----------------------------------------\n";
		}
	}

	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
	//====================================== DELETE SECTION ======================================\\

								/*------Delete Customer Section-----------*/
	void deleteCustomerRecordFromFileById(fstream& file, Customer& c,int i=-1) {
			short head, size;
			int id;
		
		if(i==-1)
		{
			cout << "Enter Customer Id: "; cin >> id;
		}
		else {
			id = i;
		}
		//store the head data
		file.seekg(0, ios::beg);
		file.read((char*)&head, sizeof(head));

		//look for the id 
		short pos = searchById(id);

		if(pos!=-1)
		{
			//calculate the size of the record
			short size;
		
			//go to record offset
			file.seekg(pos,ios::beg);
			readFromCustomerFile(c, file);
			size = c.sizeofRecord();

			//mark the deleted record id|* oldhead size
			file.seekp(pos + sizeof(int) + 1);
			file.put('*');
			file.write((char*)&head, sizeof(head));
			file.write((char*)&size, sizeof(size));

			//update the head
			file.seekp(0,ios::beg);
			file.write((char*)&pos, sizeof(pos));

			//delete the record from the primary vector
			int idx = searchByIdReturnIndex(id);
			storeCustomerData.erase(storeCustomerData.begin() + idx);

			//delete the record from the secondary vector
			int idx2 = searchByIdInSecondaruReturnIndex(id);
			storeCustomerSecondaryData.erase(storeCustomerSecondaryData.begin() + idx2);

			cout << "Record with ID " << id << " has been marked as deleted." << endl;
			
			
			
			//======================================================================
			//Delete this customer accounts from account file ,primary&secondary

			fstream accfile("account.txt", ios::in | ios::out | ios::binary);
			account acc;
			
			/*
			1- first we will loop on secondary vector 
			2- go to primary vector if id ==cusid
			3- go to Account file mark  as deleted 
			4- back to primary vector and remove the element
			5- back to secondary vector and remove the element
			*/
			for (int i = storeSecondaryAccountIndex.size()-1; i >=0; i--)
			{
				//if we found the customer record 
				if (storeSecondaryAccountIndex[i].cusId == id) {

					// go search the 
					int offset=searchAccountById(storeSecondaryAccountIndex[i].accId);
					if(offset!=-1)
					{
						//delete the record from the main account file 
						markAccountRecordAsDeleted(acc, accfile, offset);
					}


					//delete the record from the primary vector of the account file
					int idx = searchAccountByIdReturnIndex(storeSecondaryAccountIndex[i].accId);
					if (idx != -1) {
						storeAccountData.erase(storeAccountData.begin() + idx);
					}

					//delete the record from the secondary vector of the account file
					storeSecondaryAccountIndex.erase(storeSecondaryAccountIndex.begin() + i);
				}




			}


			cout << "And his accounts has been deleted\n";
			return;
		}
	
		cout << "Record with ID " << id << " not found." << endl;
		return;
	}
	void deleteCustomerRecordFromFileByName(char n[], fstream& file, Customer& c) {
		//searchCustomerByName(n, file, c);
			bool flag = false;
			int counter = 1;
	
			// display all names matches the target-?
			for (size_t i = 0; i < storeCustomerSecondaryData.size(); i++)
			{
				int  cmp = strcmp(storeCustomerSecondaryData[i].name, n);
				if (cmp == 0) {
					cout << counter << " ) ID: " << storeCustomerSecondaryData[i].id << endl;
					flag = true;
					counter++;
				}
			}
			if (flag) {
				int id;
				cout << "All IDs Matches This Names\n";
				cout << "Chooce Your Account\n"; cin >> id;
				deleteCustomerRecordFromFileById(file, c,id);
				return;
			}
			else {
				cout << "There Is No Exist For This Name\n";
				return;
			}
		}
							
							/*------Delete Account Section-----------*/
		void deleteAccountRecordbyAccountId(fstream& accfile, int accId) {
		account acc;
		//search about the account by account id 
		int offset = searchAccountById(accId);
		//mark account from main file as deleted
		if (offset != -1) {
			markAccountRecordAsDeleted(acc, accfile, offset);
		}
		//delete the record from both primary and secondary 

		// 1- delete from the primary
		int idx = searchAccountByIdReturnIndex(accId);
		if (idx != -1) {
			storeAccountData.erase(storeAccountData.begin() + idx);
		}
		// 2- delete from the secondary

		for (int i = storeSecondaryAccountIndex.size()-1; i>=0; i--)
		{
			if (storeSecondaryAccountIndex[i].accId == accId)
			{
				storeSecondaryAccountIndex.erase(storeSecondaryAccountIndex.begin() + i);
			}
		}
	}

	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
	//====================================== UPDATE SECTION ======================================\\


								/*------Update Customer Section-----------*/

	void updateCustomerById(fstream& file, Customer& c) {
		Customer NewCustomer;
		cout << "Enter Customer ID: "; cin >> c.id;
		short found = searchById(c.id);
		if (found == -1) {
			cout << "This Customer Is Not Found\n";
			return;
		}
		else {
			file.seekg(found, ios::beg);
			readFromCustomerFile(c, file);
			NewCustomer.setData(true);
			NewCustomer.id = c.id;
		
			// if new Customer size less than or equal old one->update in the same place
			if (NewCustomer.sizeofRecord() <= c.sizeofRecord()) {
				file.seekp(found, ios::beg);
				writeCusRecord(file, NewCustomer);
				short pos = file.tellp();
		
				// if the waste space is bigger than 10 bytes add it to the deleted list
				short diff = c.sizeofRecord() - NewCustomer.sizeofRecord();	
				if (diff >= 10) {
					short oldhead;
				
					//read the head to write at the waste space
					file.seekg(0, ios::beg);
					file.read((char*)&oldhead, sizeof(oldhead));
				
					//store the waste space position and add the waste space to the deleted list |* oldhead size
					file.seekp(pos+ sizeof(int) + 1, ios::beg);
					file.put('*');// unique char
					file.write((char*)&oldhead, sizeof(oldhead));//write the oldhead
					file.write((char*)&diff, sizeof(diff));//write the size

					//update the head
					file.seekp(0, ios::beg);
					file.write((char*)&pos, sizeof(pos));

				}
				cout << "Customer Has Been Updated Successfully\n";

				int cmp = strcmp(c.fname, NewCustomer.fname);
				if (cmp != 0) {
					int idx = searchByIdInSecondaruReturnIndex(c.id);
					if (idx != -1) {
						storeCustomerSecondaryData.erase(storeCustomerSecondaryData.begin() + idx);
						addCustomerToSecondary(NewCustomer);
					}
				}

				return;
			
			}
		

			//if old record is smaller then the new add at the end
			else {

				//go to end of the file
				file.seekp(0, ios::end);

				//store the last offset of the file
				int newoffset = file.tellp();

				//add the updated record
				writeCusRecord(file, NewCustomer);

				//delete the old one and add to avial List
				markRecordAsDeleted(NewCustomer, file, found);

				//update the offset at primary customer index 
				updateCustomerPrimaryOffset(NewCustomer, newoffset);
				
				
				cout << "Customer Has Been Updated Successfully\n";

				int cmp = strcmp(c.fname, NewCustomer.fname);
				if (cmp != 0) {
					int idx = searchByIdInSecondaruReturnIndex(c.id);
					if (idx != -1) {
						storeCustomerSecondaryData.erase(storeCustomerSecondaryData.begin() + idx);
						addCustomerToSecondary(NewCustomer);
					}
				}

				return;

			}
		}
	}
	void updateCustomerByName(fstream& file, Customer& c) {
		char n[20];
		cin.ignore();
		cout << "Enter Your Name: ";
		cin.getline(n, 20);
		bool flag = false;
		int counter = 1;

		// display all names matches the target-?
		for (size_t i = 0; i < storeCustomerSecondaryData.size(); i++)
		{
			int  cmp = strcmp(storeCustomerSecondaryData[i].name, n);
			if (cmp == 0) {
				cout << counter << " ) ID: " << storeCustomerSecondaryData[i].id << endl;
				flag = true;
				counter++;
			}
		}
		if (flag) {


			updateCustomerById(file, c);
		
		
		
		}
		else
		{
			cout << "This Customer Is Not Found\n";
			return;
		}
	}
	
								/*------Update Account Section-----------*/

	void updateAccountByAccountId(fstream& accfile, account& a) {
		account newAccount;
		cout << "Enter Account ID: "; cin >> a.accountId;
		short found = searchAccountById(a.accountId);
		if (found == -1) {
			cout << "This Customer Is Not Found\n";
			return;
		}
		else {
			Customer c;
			accfile.seekg(found, ios::beg);
			readFromAccountFile(a, accfile);
			
			setAccountData(c, newAccount, true);
			newAccount.accountId = a.accountId;
			newAccount.customerId = a.customerId;

			// if new Customer size less than or equal old one->update in the same place
			if (newAccount.sizeofRecord() <= a.sizeofRecord()) {
				accfile.seekp(found, ios::beg);
				writeAccountRecord(accfile, newAccount);
				short pos = accfile.tellp();

				// if the waste space is bigger than 10 bytes add it to the deleted list
				short diff = a.sizeofRecord() - newAccount.sizeofRecord();
				if (diff >= 10) {
					short oldhead;

					//read the head to write at the waste space
					accfile.seekg(0, ios::beg);
					accfile.read((char*)&oldhead, sizeof(oldhead));

					//store the waste space position and add the waste space to the deleted list |* oldhead size
					accfile.seekp(pos + sizeof(int) + 1, ios::beg);
					accfile.put('*');// unique char
					accfile.write((char*)&oldhead, sizeof(oldhead));//write the oldhead
					accfile.write((char*)&diff, sizeof(diff));//write the size

					//update the head
					accfile.seekp(0, ios::beg);
					accfile.write((char*)&pos, sizeof(pos));

				}
				cout << "Account Has Been Updated Successfully\n";
				return;

			}


			//if old record is smaller then the new add at the end
			else {

				//go to end of the file
				accfile.seekp(0, ios::end);

				//store the last offset of the file
				int newoffset = accfile.tellp();

				//add the updated record
				writeAccountRecord(accfile, newAccount);

				//delete the old one and add to avial List
				markAccountRecordAsDeleted(newAccount, accfile, found);

				//update the offset at primary customer index 
				updateAccountPrimaryOffset(newAccount, newoffset);
				cout << "Customer Has Been Updated Successfully\n";
				return;

			}
		}
	}

	
	
	// [ 1 ] -  end add record at end and at deleted at customer file
	// [ 2 ] -  end add record at end and at deleted at account file
	// [ 3 ] -  end Delete record From account file primary & Secondary false
	// [ 4 ] -  end Update record By Account ID file and update it at primary index
