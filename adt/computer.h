#ifndef COMPUTERADT_H // Include guard to prevent multiple inclusions
#define COMPUTERADT_H // Include guard to prevent multiple inclusions

#include <iostream>  // Include the iostream library
#include <fstream>   // Include the fstream library for file operations
#include <string>    // Include the string library
#include <vector>    // Include the vector library

#ifdef _WIN32        // If the operating system is Windows
#include <direct.h>  // Include the direct.h library for directory creation
#else                // If the operating system is not Windows
#include <sys/stat.h> // Include the sys/stat.h library for directory creation
#endif

using namespace std; // Use the standard namespace

// Define color codes for text
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Define a struct for Computer
struct Computer {
    int id;         // ID of the computer
    string name;    // Name of the computer
    string specs;   // Specifications of the computer
    string brand;   // Brand of the computer
    int units;      // Number of units available
};

// Define a class for ComputerADT
class ComputerADT {
public:
    void waitForInput() { // Function to wait for user input
        cout << YELLOW << "Press enter to continue..." << RESET; // Prompt the user
        cin.ignore(); // Ignore the input buffer
    }

    void addNewComputer() { // Function to add a new computer
        loadComputers(); // Load existing computers

        Computer computer; // Create a new Computer object
        computer.id = generateID(); // Generate a new ID for the computer

        cout << GREEN << "Add New Computer\nComputer Name: " << RESET; // Prompt for computer name
        cin.ignore(); // Ignore the input buffer
        getline(cin, computer.name); // Get the computer name from user input
        cout << GREEN << "Specifications: " << RESET; // Prompt for specifications
        getline(cin, computer.specs); // Get the specifications from user input
        cout << GREEN << "Brand: " << RESET; // Prompt for brand
        getline(cin, computer.brand); // Get the brand from user input
        cout << GREEN << "Number of Units: " << RESET; // Prompt for number of units
        cin >> computer.units; // Get the number of units from user input

        computers.push_back(computer); // Add the new computer to the list
        saveComputers(); // Save the updated list of computers
        cout << GREEN << "New Computer Added!" << RESET << endl; // Inform the user
        cin.ignore(); // Ignore the input buffer
    }

    void rentComputerByName(const string& name) { // Function to rent a computer by name
        loadComputers(); // Load existing computers

        for (auto& computer : computers) { // Iterate over the list of computers
            if (computer.name == name) { // Check if the computer name matches
                if (computer.units > 0) { // Check if there are available units
                    computer.units--; // Decrease the number of available units
                    saveComputers(); // Save the updated list of computers
                    return; // Exit the function
                }
            }
        }
    }

    void returnComputer() { // Function to return a rented computer
        loadComputers(); // Load existing computers

        string name; // Create a string for the computer name
        bool computerFound = false; // Flag to check if the computer is found
        cout << GREEN << "Return Computer\nComputer Name: " << RESET; // Prompt for computer name
        cin.ignore(); // Ignore the input buffer
        getline(cin, name); // Get the computer name from user input

        for (auto& computer : computers) { // Iterate over the list of computers
            if (computer.name == name) { // Check if the computer name matches
                computerFound = true; // Set the flag to true
                computer.units++; // Increase the number of available units
                saveComputers(); // Save the updated list of computers
                cout << GREEN << "Computer Returned!" << RESET << endl; // Inform the user
                waitForInput(); // Wait for user input
                return; // Exit the function
            }
        }
        if (!computerFound) { // Check if the computer was not found
            cout << RED << "Computer Name Not Found!" << RESET << endl; // Inform the user
            waitForInput(); // Wait for user input
        }
    }

    void showComputerDetails() { // Function to show details of a specific computer
        loadComputers(); // Load existing computers

        string name; // Create a string for the computer name
        cout << GREEN << "Show Computer Details\nComputer Name: " << RESET; // Prompt for computer name
        cin.ignore(); // Ignore the input buffer
        getline(cin, name); // Get the computer name from user input
        bool computerFound = false; // Flag to check if the computer is found

        for (const auto& computer : computers) { // Iterate over the list of computers
            if (computer.name == name) { // Check if the computer name matches
                computerFound = true; // Set the flag to true
                cout << GREEN << "ID: " << RESET << computer.id << "\n" 
                << GREEN << "Name: " << RESET << computer.name << "\n" 
                << GREEN << "Specifications: " << RESET << computer.specs << "\n" << GREEN << "Brand: " << RESET << computer.brand << "\n" 
                << GREEN << "Units: " << RESET << computer.units << endl; // Display computer details
                waitForInput(); // Wait for user input
                return; // Exit the function
            }
        }
        if (!computerFound) { // Check if the computer was not found
            cout << RED << "Computer Name Not Found!" << RESET << endl; // Inform the user
            waitForInput(); // Wait for user input
        }
    }

    void displayAllComputers() { // Function to display all computers
        loadComputers(); // Load existing computers

        for (const auto& computer : computers) { // Iterate over the list of computers
            cout << GREEN << "ID: " << RESET << computer.id << "\n" 
            << GREEN << "Name: " << RESET << computer.name << "\n" 
            << GREEN << "Specifications: " << RESET << computer.specs << "\n" 
            << GREEN << "Brand: " << RESET << computer.brand << "\n" 
            << GREEN << "Units: " << RESET << computer.units << endl; // Display computer details
        }
        waitForInput(); // Wait for user input
        cin.ignore(); // Ignore the input buffer
    }

    bool checkComputerAvailability(const string& name) { // Function to check computer availability
        loadComputers(); // Load existing computers

        for (const auto& computer : computers) { // Iterate over the list of computers
            if (computer.name == name && computer.units > 0) { // Check if the computer name matches and there are available units
                return true; // Return true if available
            }
        }
        return false; // Return false if not available
    }

    const vector<Computer>& getComputers() const { // Function to get the list of computers
        return computers; // Return the list of computers
    }

    void loadComputers() { // Function to load computers from file
        ifstream file(computerPath); // Open the file
        if (!file) { // Check if the file cannot be opened
            cout << RED << "Unable to open file." << RESET << endl; // Inform the user
            return; // Exit the function
        }

        computers.clear(); // Clear the current list of computers
        Computer computer; // Create a new Computer object
        string line; // Create a string for each line
        while (getline(file, line)) { // Read the file line by line
            if (line.find("ID: ") == 0) { // Check if the line contains an ID
                computer.id = stoi(line.substr(4)); // Extract and set the ID
            } else if (line.find("Name: ") == 0) { // Check if the line contains a name
                computer.name = line.substr(6); // Extract and set the name
            } else if (line.find("Specifications: ") == 0) { // Check if the line contains specifications
                computer.specs = line.substr(16); // Extract and set the specifications
            } else if (line.find("Brand: ") == 0) { // Check if the line contains a brand
                computer.brand = line.substr(7); // Extract and set the brand
            } else if (line.find("Units: ") == 0) { // Check if the line contains units
                computer.units = stoi(line.substr(7)); // Extract and set the units
            } else if (line == "---") { // Check if the line is a separator
                computers.push_back(computer); // Add the computer to the list
            }
        }
        file.close(); // Close the file
    }

private:
    const char* computerPath = "./data/computers.txt"; // Path to the computer data file
    vector<Computer> computers; // List of computers

    int generateID() { // Function to generate a new ID
        return computers.empty() ? 1 : computers.back().id + 1; // Return the next ID
    }

    void saveComputers() { // Function to save computers to file
        ofstream file(computerPath); // Open the file
        if (!file) { // Check if the file cannot be opened
            cout << RED << "Unable to open file." << RESET << endl; // Inform the user
            return; // Exit the function
        }

        for (const auto& computer : computers) { // Iterate over the list of computers
            file << "ID: " << computer.id << "\n" 
            << "Name: " << computer.name << "\n" 
            << "Specifications: " << computer.specs << "\n" 
            << "Brand: " << computer.brand << "\n" 
            << "Units: " << computer.units << "\n" << "---" << "\n"; // Write the computer details to the file
        }
        file.close(); // Close the file
    }
};

#endif // COMPUTERADT_H
