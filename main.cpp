// main.cpp
#include <iostream>  // Include the input-output stream library
#include "adt/computer.h"  // Include the header file for the computer ADT
#include "adt/customer.h"  // Include the header file for the customer ADT
#include "adt/rent.h"  // Include the header file for the rent ADT

using namespace std;  // Use the standard namespace

#define RED "\033[31m"  // Define the color code for red text
#define GREEN "\033[32m"  // Define the color code for green text
#define YELLOW "\033[33m"  // Define the color code for yellow text
#define RESET "\033[0m"  // Define the color code to reset text color

// Function to clear the screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";  // Escape sequence to clear the screen and move the cursor to the home position
}

int main() {
    int userChoice;  // Variable to store the user's menu choice
    ComputerADT computerData;  // Object to manage computer data
    CustomerADT customerData;  // Object to manage customer data
    RentADT rentalData;  // Object to manage rental data

    do 
    {
        clearScreen();  // Clear the screen
        cout << YELLOW << "------------------------------------------------------------" << endl;
        cout << "|                    Computer Rental System                 |" << endl;
        cout << "------------------------------------------------------------" << RESET << endl;
        cout << GREEN << "[1] Add New Computer" << endl;
        cout << "[2] Rent a Computer" << endl;
        cout << "[3] Return a Computer" << endl;
        cout << "[4] Show Computer Details" << endl;
        cout << "[5] Display All Computers" << endl;
        cout << "[6] Check Computer Availability" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << RESET << endl;
        cout << YELLOW << "------------------------------------------------------------" << endl;
        cout << "Enter your choice (1-8): ";  // Prompt user for input
        cin >> userChoice;  // Read user's choice

        switch (userChoice) 
        {
            case 1: {
                clearScreen();  // Clear the screen
                computerData.addNewComputer();  // Add a new computer
                break;  // Break out of the switch-case
            }
            case 2: {
                clearScreen();  // Clear the screen
                int customerID;  // Variable to store customer ID
                string computerName;  // Variable to store computer name
                cout << "Enter Customer ID: ";  // Prompt user for customer ID
                cin >> customerID;  // Read customer ID
                cout << "Enter Computer Name: ";  // Prompt user for computer name
                cin.ignore();  // Ignore the newline character from previous input
                getline(cin, computerName);  // Read the full line for computer name
                rentalData.rentComputer(computerData, customerID, computerName);  // Rent the computer
                break;  // Break out of the switch-case
            }
            case 3: {
                clearScreen();  // Clear the screen
                computerData.returnComputer();  // Return the computer
                break;  // Break out of the switch-case
            }
            case 4: {
                clearScreen();  // Clear the screen
                computerData.showComputerDetails();  // Show computer details
                break;  // Break out of the switch-case
            }
            case 5: {
                clearScreen();  // Clear the screen
                computerData.displayAllComputers();  // Display all computers
                break;  // Break out of the switch-case
            }
            case 6: {
                clearScreen();  // Clear the screen
                cout << "Check Computer Availability\nComputer Name: ";  // Prompt user for computer name
                cin.ignore();  // Ignore the newline character from previous input
                string name;  // Variable to store computer name
                getline(cin, name);  // Read the full line for computer name
                if (computerData.checkComputerAvailability(name)) {  // Check computer availability
                    cout << GREEN << "Computer Available!" << RESET << endl;  // Print available message
                } else {
                    cout << RED << "Computer Not Available!" << RESET << endl;  // Print not available message
                }
                cout << "Press enter to continue...";  // Prompt user to press enter to continue
                cin.ignore();  // Wait for user input
                break;  // Break out of the switch-case
            }
            case 7: {
                int userChoice;  // Variable to store user's choice for customer maintenance
                do {
                    clearScreen();  // Clear the screen
                    cout << YELLOW << "------------------------------------------------------------" << endl;
                    cout << "|                   Customer Maintenance                   |" << endl;
                    cout << "------------------------------------------------------------" << RESET << endl;
                    cout << GREEN << "[1] Add Customer" << endl;
                    cout << "[2] Show Customer Details" << endl;
                    cout << "[3] Print All Customers" << endl;
                    cout << "[4] Return to Main Menu" << endl;
                    cout << "Please make a selection: " << RESET;  // Prompt user for input
                    cin >> userChoice;  // Read user's choice

                    switch (userChoice) {
                        case 1: {
                            clearScreen();  // Clear the screen
                            customerData.addCustomer();  // Add a customer
                            cin.ignore();  // Ignore the newline character from previous input
                            cout << "Press enter to continue...";  // Prompt user to press enter to continue
                            cin.get();  // Wait for user input
                            break;  // Break out of the switch-case
                        }
                        case 2: {
                            clearScreen();  // Clear the screen
                            customerData.showCustomerDetails();  // Show customer details
                            cin.ignore();  // Ignore the newline character from previous input
                            cout << "Press enter to continue...";  // Prompt user to press enter to continue
                            cin.get();  // Wait for user input
                            break;  // Break out of the switch-case
                        }
                        case 3: {
                            clearScreen();  // Clear the screen
                            customerData.printAllCustomers();  // Print all customers
                            cin.ignore();  // Ignore the newline character from previous input
                            cout << "Press enter to continue...";  // Prompt user to press enter to continue
                            cin.get();  // Wait for user input
                            break;  // Break out of the switch-case
                        }
                        case 4: {
                            break;  // Break out of the switch-case
                        }
                        default: {
                            cout << RED << "Invalid selection. Try again." << RESET << endl;  // Print invalid selection message
                            cin.ignore();  // Ignore the newline character from previous input
                            cout << "Press enter to continue...";  // Prompt user to press enter to continue
                            cin.get();  // Wait for user input
                            break;  // Break out of the switch-case
                        }
                    }
                } while (userChoice != 4);  // Repeat until user chooses to return to main menu
                break;  // Break out of the switch-case
            }
            case 8: {
                clearScreen();  // Clear the screen
                cout << YELLOW << "Exiting Program." << RESET << endl;  // Print exiting message
                break;  // Break out of the switch-case
            }
            default: {
                cout << RED << "Invalid input. Please try again." << RESET << endl;  // Print invalid input message
                cin.ignore();  // Ignore the newline character from previous input
                cout << "Press enter to continue...";  // Prompt user to press enter to continue
                cin.get();  // Wait for user input
                break;  // Break out of the switch-case
            }
        }
    } while (userChoice != 8);  // Repeat until user chooses to exit
}
