# Banking System Using File Organization in C++

A C++ project that simulates core DBMS file organization concepts using binary files and indexing techniques.

## Overview

This project implements a simple Banking Management System with support for:

* Customer Management
* Account Management
* File-Based Storage
* Primary & Secondary Indexing
* Variable-Length Records
* Avail List for Deleted Records Reuse

The system demonstrates how database systems internally organize and manage records using file structures instead of traditional DBMS software.

---

## Features

### Customer Operations

* Add New Customer
* Display All Customers
* Display Top 5 Customers
* Search Customer by ID
* Search Customer by Name
* Update Customer
* Delete Customer

### Account Operations

* Add New Account
* Display Customer Accounts
* Search Account by ID
* Update Account
* Delete Account

---

## Concepts Implemented

### Primary Index

Fast searching using binary search on indexed customer/account IDs.

### Secondary Index

Search customers using non-primary attributes like customer names.

### Variable-Length Records

Records are stored using delimiters to reduce wasted storage space.

### Avail List

Deleted records are reused efficiently instead of wasting file space.

### Binary File Processing

Data is stored and retrieved directly from binary files.

---

## Technologies Used

* C++
* File Handling
* Data Structures
* Binary Search
* STL Vectors
* Object-Oriented Programming (OOP)

---

## Project Structure

```bash
ConsoleApplication1/
│
├── Account.h
├── AccountPrimary.h
├── AccountSecondary.h
├── Customer.h
├── CustomerPrimaryIndex.h
├── CustomerSecondary.h
├── System.h
├── ConsoleApplication1.cpp
```

---

## How to Run

1. Open the project using Visual Studio.
2. Build the solution.
3. Run the application.
4. Use the console menus to manage customers and accounts.

---

## Sample Functionalities

* Indexed searching using binary search
* Record deletion with avail list management
* Updating records while preserving indexing
* Relationship handling between customers and accounts

---

## Future Improvements

* GUI Version
* SQL Database Integration
* Authentication System
* Transaction Management
* Interest Calculation
* File Encryption

---

## Author

Youssef Ibrahim Ahmed
