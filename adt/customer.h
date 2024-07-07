#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>     // For standard I/O operations
#include <fstream>      // For file I/O operations
#include <string>       // For string operations
#include <vector>       // For using the vector container
#include "computer.h"   // Include the ComputerADT class
#include "rent.h"       // Include the RentADT class

#ifdef _WIN32
#include <direct.h>     // For creating directories on Windows
#else
#include <sys/stat.h>   // For creating directories on Unix-based systems
#endif

using namespace std;

// Define color codes for terminal text formatting
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// CustomerADT class for managing customer operations
class CustomerADT {
public:
    void addCustomer();          // Method to add a new customer
    void showCustomerDetails();  // Method to show details of a specific customer
    void printAllCustomers();    // Method to print all customer details

private:
    // Struct representing a Customer
    struct Customer {
        int id;                  // Customer ID
        string name;             // Customer name
        string address;          // Customer address
    };

    const char* customerPath = "./data/customers.txt"; // Path to the customer data file
    vector<Customer> customers;                        // Vector to hold all customers

    int getNextID();           // Method to get the next available customer ID
    bool loadCustomers();      // Method to load customers from the file
    void saveCustomers();      // Method to save customers to the file
    void appendCustomer(const Customer& customer); // Method to append a customer to the vector

    // Helper method to print error messages
    void printError(const string& msg) {
        cerr << RED << "Error: " << RESET << msg << endl;
    }
};

// Method to add a new customer
void CustomerADT::addCustomer() {
    if (!loadCustomers()) return;  // Load existing customers, return if failed

    Customer customer;
    customer.id = getNextID();     // Assign the next available ID

    cout << GREEN << "Enter Customer Name: " << RESET;
    cin.ignore();                  // Clear the input buffer
    getline(cin, customer.name);   // Get the customer's name
    cout << GREEN << "Enter Customer Address: " << RESET;
    getline(cin, customer.address); // Get the customer's address

    customers.push_back(customer); // Add the customer to the vector
    saveCustomers();               // Save the updated customer list to the file
    cout << GREEN << "New Customer Added!" << RESET << endl;
    cin.ignore();                  // Wait for user input
}

// Method to show details of a specific customer
void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) return;  // Load existing customers, return if failed

    int id;
    cout << GREEN << "Enter Customer ID: " << RESET;
    cin >> id;                     // Get the customer ID

    for (const auto& customer : customers) {
        if (customer.id == id) {   // Find the customer with the matching ID
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            cin.ignore();          // Wait for user input
            return;
        }
    }
    cout << RED << "Customer ID Not Found!" << RESET << endl;
    cin.ignore();                  // Wait for user input
}

// Method to print all customer details
void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) return;  // Load existing customers, return if failed

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
    cin.ignore();                  // Wait for user input
}

// Method to get the next available customer ID
int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1; // If no customers, return 1, else return last ID + 1
}

// Method to load customers from the file
bool CustomerADT::loadCustomers() {
    ifstream file(customerPath);   // Open the customer file
    if (!file) {
        printError("Unable to open file.");
        return false;              // Return false if the file could not be opened
    }

    customers.clear();             // Clear the existing customer vector
    Customer customer;
    string line;
    while (getline(file, line)) {  // Read the file line by line
        if (line.find("ID: ") == 0) {
            customer.id = stoi(line.substr(4));  // Extract and set customer ID
        } else if (line.find("Name: ") == 0) {
            customer.name = line.substr(6);      // Extract and set customer name
        } else if (line.find("Address: ") == 0) {
            customer.address = line.substr(9);   // Extract and set customer address
        } else if (line == "---") {
            customers.push_back(customer);       // Add the customer to the vector
        }
    }
    file.close();
    return true;                    // Return true if loading was successful
}

// Method to save customers to the file
void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data");               // Create the data directory on Windows
#else
    mkdir("./data", 0777);          // Create the data directory on Unix-based systems
#endif

    ofstream file(customerPath);    // Open the customer file for writing
    if (!file) {
        printError("Unable to open file.");
        return;                     // Return if the file could not be opened
    }

    for (const auto& customer : customers) {
        file << "ID: " << customer.id << '\n'
             << "Name: " << customer.name << '\n'
             << "Address: " << customer.address << '\n'
             << "---\n";            // Write customer details to the file
    }

    file.close();
}

#endif // CUSTOMERADT_H
