/*  -----------------------------------------------------------------
    Class:
        Name:           Main
        Definition:     main.cpp
        Header:         N/A

    Description:    Acts as the launcher and QA tester.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
------------------------------------------------------------------- */
#include <iostream>
#include <string>
#include <fstream>
#include "Client.h"
#include "SalesRep.h"
#include "Product.h"
#include "Sale.h"
#include "Test.h"

using namespace std;

bool ApplicationRunning = true;

void enterPause(bool ignore = true) {
    cout << endl << endl << "Press enter to continue.";
    if (ignore) {
        cin.ignore();
    }
    cin.get();
}

void PrintMenu_Client() {
    system("cls");
    cout << "===== Arbor Eight | Client Menu =====" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
    cout << "0) Back to Main Menu" << endl;
    cout << "1) View All Clients" << endl;
    cout << "2) View Specific Client" << endl;
    cout << "3) Add New Client" << endl;
    cout << "4) Update Client" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
}

void HandleSelection_Client(string s) {
    system("cls");
    string userInput = "";
    if (s == "0") {
        // Main menu
    } else if (s == "1") {
        Client::PrintClientList();
        enterPause();
    } else if (s == "2") {
        cout << "Enter a client's name: ";
        cin.ignore();
        getline(cin, userInput);
        Client::PrintSingleClient(userInput);
        enterPause(false);
    } else if (s == "3") {
        string nName;
        string nAddress;
        string nNumber;
        string nEmail;
        cout << "Enter new client's name: ";
        cin.ignore();
        getline(cin, nName);
        cout << "Enter new client's address: ";
        getline(cin, nAddress);
        cout << "Enter new client's phone number: ";
        getline(cin, nNumber);
        cout << "Enter new client's email: ";
        getline(cin, nEmail);
        Client c = Client();
        if (c.QuickAdd(nName, nAddress, 0, nNumber, nEmail)) {
            cout << endl << nName << " has been added as a client." << endl;
        }
        else {
            cout << endl << "Error adding " << nName << " as a client." << endl;
        }
        enterPause(false);
    } else if (s == "4") {
        string uName;
        string uAddress;
        string uNumber;
        string uEmail;

        cout << "Enter a client's name to update: ";
        cin.ignore();
        getline(cin, userInput);
        Client c = Client::LoadSingleClient(userInput);

        cout << "Enter client's updated name: ";
        getline(cin, uName);
        cout << "Enter client's updated address: ";
        getline(cin, uAddress);
        cout << "Enter client's updated phone number: ";
        getline(cin, uNumber);
        cout << "Enter client's updated email: ";
        getline(cin, uEmail);

        cout << "Old Name: " << c.GetName() << " | New Name: " << uName << endl;
        cout << "Old Address: " << c.GetAddress() << " | New Name: " << uAddress << endl;
        cout << "Old Phone Number: " << c.GetPhoneNumber() << " | New Name: " << uNumber << endl;
        cout << "Old Email: " << c.GetEmail() << " | New Name: " << uEmail << endl;

        c.SetName(uName);
        c.SetAddress(uAddress);
        c.SetPhoneNumber(uNumber);
        c.SetEmail(uEmail);
        c.SaveClientUpdates();

        enterPause(false);
    }
}

void PrintMenu_Main() {
    system("cls");
    cout << "===== Arbor Eight | Main Menu =====" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
    cout << "0) Exit Application" << endl;
    cout << "1) Manage Clients" << endl;
    cout << "2) Manage Sales Representatives" << endl;
    cout << "3) Manage Products" << endl;
    cout << "4) Manage Sales" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
}

void HandleSelection_Main(string s) {
    string userInput = "";
    if (s == "0") {
        ApplicationRunning = false;
    } else if (s == "1") {
        PrintMenu_Client();
        while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {
            cout << "Please select an option: ";
            cin >> userInput;
        }
        HandleSelection_Client(userInput);
    }
}

void Initialize() {
    Client::InitializeDatabase();
    Client::LoadClients();
    SalesRep::InitializeDatabase();
    SalesRep::LoadSalesReps();
    Product::InitializeDatabase();
    Product::LoadProducts();
    Sale::InitializeDatabase();
    Sale::LoadSales();
}

int main(int argc, char** argv) {
    Global::SetCurrentDirectory(argv);

    /*
        [TBomer]
            Test::PopulateDatabases() can be used to populate test data into the DBs.
            If the DB files exist, nothing will happen. If they do not exist,
            they will be created and popualted with data.

            You can disable individual databases by setting the property BEFORE
            the PopulateDatabases call. They are all enabled by default.

            Disable Client DB Population:       Test::populateClients = false;
            Disable Product DB Population:      Test::populateProducts = false;
            Disable Sales Rep DB Population:    Test::populateSalesReps = false;
            Disable Sales DB Population:        Test::populateSales = false;

    */

    // [START] Program
    Test::PopulateDatabases();
    Initialize();
    while (ApplicationRunning) {
        string userInput = "";
        PrintMenu_Main();
        while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {
            cout << "Please select an option: ";
            cin >> userInput;
        }
        HandleSelection_Main(userInput);
    }
    
    // [END] Program

    
    //cout << endl << endl << "End of Program. Press enter to exit.";
    //cin.ignore();
    //cin.get(); // Used to halt the program before shutting down
    //cout << endl << endl << endl << endl << endl << endl; // Adding extra padding at bottom
}