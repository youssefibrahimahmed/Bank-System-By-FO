#include <iostream>
#include <vector>
#include "Customer.h"
#include <algorithm>
#include "CustomerPrimaryIndex.h"
#include "CustomerSecondary.h"
#include "System.h"
#include "Account.h"
#include "AccountPrimary.h"
#include "AccountSecondary.h"
using namespace std;

int main()
{
	primaryCustomerIndex pci;
	secondaryCustomerIndex sci;
	accountPrimaryIndex api;
	secondaryAccountIndex sai;
	//backup the data 
	leadDataFromCustomerSecondaryFile(sci);
	leadDataFromCustomerPrimaryFile(pci);
	leadDataFromAccountPrimaryFile(api);
	leadDataFromAccountSecondaryFile(sai);
	intiateCustomerFile();
	intiateAccountFile();


	int mainChoice;

	while (true)
	{
		cout << "\n========== MAIN MENU ==========\n";
		cout << "1. Customer Menu\n";
		cout << "2. Account Menu\n";
		cout << "3. Exit\n";
		cout << "Enter Choice: ";
		cin >> mainChoice;

		system("cls");

		switch (mainChoice)
		{
		case 1:
		{
			int customerChoice;

			while (true)
			{
				cout << "\n========== CUSTOMER MENU ==========\n";
				cout << "1. Add New Customer\n";
				cout << "2. Display All Customers\n";
				cout << "3. Display Top 5 Customers\n";
				cout << "4. Delete Customer By ID\n";
				cout << "5. Search Customer By ID\n";
				cout << "6. Update Customer By ID\n";
				cout << "7. Search Customer By Name\n";
				cout << "8. Delete Customer By Name\n";
				cout << "9. Update Customer By Name\n";
				cout << "10. Back\n";
				cout << "Enter Choice: ";

				cin >> customerChoice;

				system("cls");

				if (customerChoice == 10)
					break;

				switch (customerChoice)
				{
				case 1: {
					cout << "\n====================================================\n";
					cout << "                 ADDING NEW CUSTOMER				     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}
					Customer c;

					addRecordToCustomerFile(file, c);

					file.close();

					break;
					system("cls");
				}case 2: {
					cout << "\n====================================================\n";
					cout << "                 DISPLAY ALL CUSTOMERS		     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					displayAllCustomerRecords(file);

					file.close();

					break;
					system("cls");
				}case 3: {
					cout << "\n====================================================\n";
					cout << "                 DISPLAY TOP 5 CUSTOMERS		     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					displayTopFiveRecords(file);

					file.close();

					break;
					system("cls");
				}
				case 4: {
					cout << "\n====================================================\n";
					cout << "                 DELETE CUSTOMERS BY ID		     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					Customer c;

					deleteCustomerRecordFromFileById(file, c);

					file.close();

					break;
					system("cls");
				}case 5: {
					cout << "\n====================================================\n";
					cout << "                 SEARCH CUSTOMER BY ID		     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					Customer c;

					searchCustomerById(file, c);

					file.close();
					break;
					system("cls");

				}case 6: {
					cout << "\n====================================================\n";
					cout << "                 UPDATE CUSTOMER BY ID		     ";
					cout << "\n====================================================\n";
					fstream file("customer.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					Customer c;

					updateCustomerById(file, c);

					file.close();

					break;
					system("cls");
				}case 7: {
					cout << "\n====================================================\n";
					cout << "                 SEARCH CUSTOMER BY NAME		     ";
					cout << "\n====================================================\n";


					fstream file("customer.txt", ios::in | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}
					Customer c;

					char name[20];

					cin.ignore();
					cout << "Enter Customer First Name: ";
					cin.getline(name, 20);

					searchCustomerByName(name, file, c);

					file.close();
					break;
					system("cls");

				}case 8: {
					cout << "\n====================================================\n";
					cout << "                 DELETE CUSTOMER BY NAME		     ";
					cout << "\n====================================================\n";

					fstream file("customer.txt", ios::in | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}
					Customer c;

					char name[20];

					cin.ignore();
					cout << "Enter Customer First Name: ";
					cin.getline(name, 20);

					deleteCustomerRecordFromFileByName(name, file, c);

					file.close();

					break;
					system("cls");
				}case 9: {
					cout << "\n====================================================\n";
					cout << "                 UPDATE CUSTOMER BY NAME		     ";
					cout << "\n====================================================\n";

					fstream file("customer.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening customer file.\n";
						break;
					}

					Customer c;

					updateCustomerByName(file, c);

					file.close();

					break;
					system("cls");

				}
				
				default:
					cout << "Invalid Choice.\n";

				}
			}

			break;
		}

		case 2:
		{
			int accountChoice;

			while (true)
			{
				cout << "\n========== ACCOUNT MENU ==========\n";
				cout << "1. Add New Account\n";
				cout << "2. Display Customer Accounts\n";
				cout << "3. Delete Account By ID\n";
				cout << "4. Search Account By ID\n";
				cout << "5. Update Account By ID\n";
				cout << "6. Back\n";
				cout << "Enter Choice: ";

				cin >> accountChoice;

				system("cls");

				if (accountChoice == 6)
					break;

				switch (accountChoice)
				{
				case 1: {
					cout << "\n====================================================\n";
					cout << "                 ADD NEW ACCOUNT		     ";
					cout << "\n====================================================\n";

					fstream file("account.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening account file.\n";
						break;
					}

					Customer c;

					addRecordToAccountFile(file, c);

					file.close();

					break;
					system("cls");
				}case 2: {
					cout << "\n====================================================\n";
					cout << "                 DISPLAY ALL CUSTOMER ACCOUNTS		     ";
					cout << "\n====================================================\n";

					fstream file("account.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening account file.\n";
						break;
					}

					Customer c;
					int id;
					cout << "Enter Your ID: "; cin >> id;
					displayAllCustomerAccountRecords(file, id);// => don't display the accounts

					file.close();

					break;
					system("cls");
				}case 3: {
					cout << "\n====================================================\n";
					cout << "                 DELETE ACCOUNT BY ACCOUNT ID		     ";
					cout << "\n====================================================\n";

					fstream file("account.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening account file.\n";
						break;
					}

					int accId;
					cout << "Enter Account ID: ";
					cin >> accId;

					deleteAccountRecordbyAccountId(file, accId);

					cout << "Account deleted successfully\n";

					file.close();

					break;
					system("cls");
				}case 4: {
					cout << "\n====================================================\n";
					cout << "           SEARCH ACCOUNT BY ACCOUNT ID		     ";
					cout << "\n====================================================\n";

					fstream file("account.txt", ios::in | ios::out | ios::binary);
					account acc;
					if (!file) {
						cerr << "Error opening account file.\n";
						break;
					}

					int accId;
					cout << "Enter Account ID: ";
					cin >> accId;

					searchAccountByAccountId(file, acc, accId);


					file.close();
					break;
					system("cls");

				}case 5: {
					cout << "\n====================================================\n";
					cout << "          UPDATE ACCOUNT BY ACCOUNT ID		     ";
					cout << "\n====================================================\n";

					fstream file("account.txt", ios::in | ios::out | ios::binary);

					if (!file) {
						cerr << "Error opening Account file.\n";
						break;
					}

					account a;

					updateAccountByAccountId(file, a);

					file.close();
					break;
					system("cls");

				}
				}
			}

			break;
		}

		case 3:
			cout << "Exiting program...\n";

			leadDataToCustomerPrimaryFile(pci);
			leadDataToCustomerSecondaryFile(sci);
			leadDataToAccountPrimaryFile(api);
			leadDataToAccountSecondaryFile(sai);

			return 0;

		default:
			cout << "Invalid Choice.\n";
		}
	}
	
	return 0;
}
