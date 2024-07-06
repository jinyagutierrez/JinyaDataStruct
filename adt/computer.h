#ifndef COMPUTERADT_H
#define COMPUTERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

struct Computer {
    int id;
    string name;
    string specs;
    string brand;
    int units;
};

class ComputerADT {
public:
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }

    void newComputer() {
        loadComputers();

        Computer computer;
        computer.id = getNextID();

        cout << "Add New Computer\nComputer Name: ";
        cin.ignore();
        getline(cin, computer.name);
        cout << "Specifications: ";
        getline(cin, computer.specs);
        cout << "Brand: ";
        getline(cin, computer.brand);
        cout << "Number of Units: ";
        cin >> computer.units;

        computers.push_back(computer);
        saveComputers();
        cout << "New Computer Added!" << endl;
        cin.ignore();
    }

    void rentComputerByName(const string& name) {
        loadComputers();

        for (auto& computer : computers) {
            if (computer.name == name) {
                if (computer.units > 0) {
                    computer.units--;
                    saveComputers();
                    return;
                }
            }
        }
    }

    void returnComputer() {
        loadComputers();

        string name;
        bool computerFound = false;
        cout << "Return Computer\nComputer Name: ";
        cin.ignore();
        getline(cin, name);

        for (auto& computer : computers) {
            if (computer.name == name) {
                computerFound = true;
                computer.units++;
                saveComputers();
                cout << "Computer Returned!" << endl;
                waitForUserInput();
                return;
            }
        }
        if (!computerFound) {
            cout << "Computer Name Not Found!" << endl;
            waitForUserInput();
        }
    }

    void showComputerDetails() {
        loadComputers();

        string name;
        cout << "Show Computer Details\nComputer Name: ";
        cin.ignore();
        getline(cin, name);
        bool computerFound = false;

        for (const auto& computer : computers) {
            if (computer.name == name) {
                computerFound = true;
                cout << "ID: " << computer.id << "\nName: " << computer.name << "\nSpecifications: " << computer.specs << "\nBrand: " << computer.brand << "\nUnits: " << computer.units << endl;
                waitForUserInput();
                return;
            }
        }
        if (!computerFound) {
            cout << "Computer Name Not Found!" << endl;
            waitForUserInput();
        }
    }

    void displayAllComputers() {
        loadComputers();

        for (const auto& computer : computers) {
            cout << "ID: " << computer.id << "\nName: " << computer.name << "\nSpecifications: " << computer.specs << "\nBrand: " << computer.brand << "\nUnits: " << computer.units << endl;
        }
        waitForUserInput();
        cin.ignore();
    }

    bool checkComputerAvailability(const string& name) {
        loadComputers();

        for (const auto& computer : computers) {
            if (computer.name == name && computer.units > 0) {
                return true;
            }
        }
        return false;
    }

    const vector<Computer>& getComputers() const {
        return computers;
    }

    void loadComputers() {
        ifstream file(computerPath);
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        computers.clear();
        Computer computer;
        string line;
        while (getline(file, line)) {
            if (line.find("ID: ") == 0) {
                computer.id = stoi(line.substr(4));
            } else if (line.find("Name: ") == 0) {
                computer.name = line.substr(6);
            } else if (line.find("Specifications: ") == 0) {
                computer.specs = line.substr(16);
            } else if (line.find("Brand: ") == 0) {
                computer.brand = line.substr(7);
            } else if (line.find("Units: ") == 0) {
                computer.units = stoi(line.substr(7));
            } else if (line == "---") {
                computers.push_back(computer);
            }
        }
        file.close();
    }

private:
    const char* computerPath = "./data/computers.txt";
    vector<Computer> computers;

    int getNextID() {
        return computers.empty() ? 1 : computers.back().id + 1;
    }

    void saveComputers() {
        #ifdef _WIN32
        _mkdir("./data");
        #else
        mkdir("./data", 0777);
        #endif

        ofstream file(computerPath);
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        for (const auto& computer : computers) {
            file << "ID: " << computer.id << '\n'
                 << "Name: " << computer.name << '\n'
                 << "Specifications: " << computer.specs << '\n'
                 << "Brand: " << computer.brand << '\n'
                 << "Units: " << computer.units << '\n'
                 << "---\n";
        }

        file.close();
    }
};

#endif
