# Banking System — File Organization in C++

A console-based banking management system developed in **C++** to demonstrate how records can be stored, searched, updated, and deleted using binary files and in-memory indexes.

Instead of relying on a traditional database engine, the project manages customer and account records directly through files and indexing structures.

## Features

### Customer Management

- Add a new customer.
- Display all customers.
- Display the first five customers in the primary index order.
- Search for a customer by ID.
- Search for customers by first name.
- Update customer information by ID or first name.
- Delete a customer by ID or first name.

### Account Management

- Create an account for an existing customer.
- Display all accounts belonging to a customer.
- Search for an account by account ID.
- Update an account by ID.
- Delete an account by ID.

### File Organization Concepts

- **Binary File Storage:** Customer and account records are stored in binary files.
- **Variable-Length Records:** Text fields are stored with delimiters, allowing records to have different lengths.
- **Primary Indexing:** Sorted in-memory indexes map customer/account IDs to their record offsets. Binary search is used for ID lookup.
- **Secondary Indexing:** Secondary indexes support customer lookup by first name and account lookup by customer ID.
- **Avail List:** Deleted record spaces are linked and can be reused when a new record is inserted.
- **Record Updates:** When an updated record no longer fits in its old space, it can be written at the end of the file and the index offset is updated.

## Technologies and Concepts

- C++
- Object-Oriented Programming and structs
- File handling (`fstream`, `ifstream`, `ofstream`)
- Binary file I/O
- STL `vector` and sorting
- Binary Search
- Primary and secondary indexes
- Variable-length records and avail lists

## Data Files

The application uses local files in its working directory, including:

| File | Purpose |
|---|---|
| `customer.txt` | Customer records |
| `account.txt` | Account records |
| `customerprimary.txt` | Saved customer primary index |
| `customersecondary.txt` | Saved customer secondary index |
| `accountprimary.txt` | Saved account primary index |
| `accountsecondary.txt` | Saved account secondary index |

These files are used by the application to persist records and index information between runs.

## Project Structure

```text
Bank-System-By-FO/
├── Account.h
├── AccountPrimary.h
├── AccountSecondary.h
├── Customer.h
├── CustomerPrimaryIndex.h
├── CustomerSecondary.h
├── System.h
├── ConsoleApplication1.cpp
└── README.md
```

## How to Run

This project is organized as a C++ console application and uses Visual Studio-compatible code.

1. Clone the repository:

   ```bash
   git clone https://github.com/youssefibrahimahmed/Bank-System-By-FO.git
   ```

2. Open the source files in Visual Studio and create/open a C++ Console Application.
3. Add the repository's `.cpp` and header files to the project.
4. Build and run the application.
5. Use the console menus to manage customers and accounts.

> The repository currently contains the source files rather than a ready-made Visual Studio solution file.

## Learning Goals

This project provides practical experience with:

- Designing and maintaining file-based records.
- Mapping record IDs to byte offsets.
- Implementing primary and secondary indexes.
- Using binary search over sorted index data.
- Reusing deleted record space through an avail list.
- Keeping customer and account data related.

## Author

**Youssef Ibrahim Ahmed**

- [GitHub](https://github.com/youssefibrahimahmed)
- [LinkedIn](https://www.linkedin.com/in/youssef-ibrahim-048961286/)
