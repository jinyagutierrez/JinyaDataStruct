#ifndef RENTADT_H
#define RENTADT_H

#include <iostream>    // For standard I/O operations
#include <vector>      // For using the vector container
#include <string>      // For string operations
#include <ctime>       // For time-related functions
#include <iomanip>     // For stream manipulation
#include "computer.h"  // Include the ComputerADT class
#include "customer.h"  // Include the CustomerADT class

#ifdef _WIN32
#include <direct.h>    // For creating directories on Windows
#else
#include <sys/stat.h>  // For creating directories on Unix-based systems
#endif

using namespace std;

// Define color codes for terminal text formatting
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// RentADT class for managing rental operations
class RentADT {
public:
    // Method to rent a computer to a customer
    void rentComputer(ComputerADT& computerADT, int customerId, const string& computerName) {
        computerADT.loadComputers();                 // Load the list of computers
        const vector<Computer>& computers = computerADT.getComputers(); // Get the list of computers

        bool computerAvailable = false;              // Flag to check computer availability
        for (const auto& computer : computers) {     // Iterate over the list of computers
            if (computer.name == computerName && computer.units > 0) {
                computerAvailable = true;            // Set flag if computer is available
                break;                               // Exit the loop
            }
        }

        if (!computerAvailable) {                    // If the computer is not available
            cout << RED << "Computer Not Available!" << RESET << endl; // Print error message
            waitForUserInput();                      // Wait for user input
            return;                                  // Exit the method
        }

        loadRents();                                 // Load the list of rents
        Rent rent;                                   // Create a new Rent object
        rent.id = getNextID();                       // Assign the next available ID
        rent.customerId = customerId;                // Set the customer ID
        rent.computerName = computerName;            // Set the computer name
        rent.rentDate = getCurrentDate();            // Set the current date as the rent date
        rent.returnDate = "Not Returned";            // Set the return date to "Not Returned"

        rents.push_back(rent);                       // Add the rent to the vector
        saveRents();                                 // Save the updated rent list to the file
        computerADT.rentComputerByName(computerName); // Mark the computer as rented
        cout << GREEN << "Computer Rented!" << RESET << endl; // Print success message
        waitForUserInput();                          // Wait for user input
    }

private:
    // Struct representing a Rent
    struct Rent {
        int id;                  // Rent ID
        int customerId;          // Customer ID
        string computerName;     // Computer name
        string rentDate;         // Rent date
        string returnDate;       // Return date
    };

    const char* rentPath = "./data/rents.txt"; // Path to the rent data file
    vector<Rent> rents;                        // Vector to hold all rents

    int getNextID() {
        return rents.empty() ? 1 : rents.back().id + 1; // If no rents, return 1, else return last ID + 1
    }

    void loadRents() {
        ifstream file(rentPath);   // Open the rent file
        if (!file) {               // Check if the file was opened successfully
            cout << RED << "Unable to open file." << RESET << endl; // Print error message
            return;                // Return if the file could not be opened
        }

        rents.clear();             // Clear the existing rent vector
        Rent rent;                 // Create a temporary Rent object
        string line;               // String to hold each line from the file
        while (getline(file, line)) { // Read the file line by line
            if (line.find("ID: ") == 0) {
                rent.id = stoi(line.substr(4));         // Extract and set rent ID
            } else if (line.find("CustomerID: ") == 0) {
                rent.customerId = stoi(line.substr(12)); // Extract and set customer ID
            } else if (line.find("ComputerName: ") == 0) {
                rent.computerName = line.substr(14);    // Extract and set computer name
            } else if (line.find("RentDate: ") == 0) {
                rent.rentDate = line.substr(10);        // Extract and set rent date
            } else if (line.find("ReturnDate: ") == 0) {
                rent.returnDate = line.substr(12);      // Extract and set return date
            } else if (line == "---") {
                rents.push_back(rent);                  // Add the rent to the vector
            }
        }
        file.close();               // Close the file
    }

    void saveRents() {
#ifdef _WIN32
        _mkdir("./data");          // Create the data directory on Windows
#else
        mkdir("./data", 0777);     // Create the data directory on Unix-based systems
#endif

        ofstream file(rentPath);   // Open the rent file for writing
        if (!file) {               // Check if the file was opened successfully
            cout << RED << "Unable to open file." << RESET << endl; // Print error message
            return;                // Return if the file could not be opened
        }

        for (const auto& rent : rents) { // Iterate over the list of rents
            file << "ID: " << rent.id << '\n'
                 << "CustomerID: " << rent.customerId << '\n'
                 << "ComputerName: " << rent.computerName << '\n'
                 << "RentDate: " << rent.rentDate << '\n'
                 << "ReturnDate: " << rent.returnDate << '\n'
                 << "---\n";       // Write rent details to the file
        }

        file.close();               // Close the file
    }

    // Helper method to get the current date in YYYY-MM-DD format
    string getCurrentDate() {
        time_t now = time(0);  // Get the current time
        tm* ltm = localtime(&now); // Convert the time to local time
        stringstream ss;       // Create a stringstream to format the date
        ss << 1900 + ltm->tm_year << "-"
           << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
           << setfill('0') << setw(2) << ltm->tm_mday;
        return ss.str();       // Return the formatted date string
    }

    // Helper method to wait for user input
    void waitForUserInput() {
        cout << YELLOW << "Press enter to continue..." << RESET;
        cin.ignore();          // Ignore any remaining input
        cin.get();             // Wait for user to press enter
    }
};

#endif // RENTADT_H
