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
#include <ctime>
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

void PrintMenu_Sales() {
    system("cls");
    cout << "===== Arbor Eight | Sales Menu =====" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
    cout << "0) Back to Main Menu" << endl;
    cout << "1) Purchase Item" << endl;
    cout << "2) Annual Sales Report" << endl;
    cout << "3) Annual Sales Report - By Client" << endl;
    cout << "4) Update Sale" << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
}

void HandleSelection_Sales(string s) {
    system("cls");
    string userInput = "";
    if (s == "1") {
        string clientName = "";
        cout << "Enter client name: ";
        cin.ignore();
        getline(cin, clientName);
        system("cls");
        Product::PrintProductList();

        string nDate;
        string nClient;
        string nRep;
        string nProduct;
        int nQty;

        // Global::GetFormattedDate();

        Sale s = Sale();
        //s.QuickAdd("date","client","rep", "product", 0, 0.00);

        cout << endl << endl;
        cout << "Please enter the name of the product you would like to purchase: ";
        cin.ignore();



        enterPause();
    }
    else if (s == "2") {
        cout << "Enter a product name: ";
        cin.ignore();
        getline(cin, userInput);
        system("cls");
        Product::PrintSingleProduct(userInput);
        cout << endl << endl << endl << endl;
        Sale::PrintSalesByProduct(userInput);
        enterPause(false);
    }
    else if (s == "3") {
        string nName;
        string nDesc;
        double nPrice;
        int nStock;

        cout << "Enter new product's name: ";
        cin.ignore();
        getline(cin, nName);
        cout << "Enter new product's description: ";
        getline(cin, nDesc);
        cout << "Enter new product's price: ";
        cin >> nPrice;
        cout << "Enter new product's stock: ";
        cin >> nStock;

        Product p = Product();
        if (p.QuickAdd(nName, nDesc, nPrice, nStock)) {
            cout << endl << nName << " has been added as a product." << endl;
            Product::LoadProducts();
        }
        else {
            cout << endl << "Error adding " << nName << " as a product." << endl;
        }
        enterPause(false);
    }
    else if (s == "4") {
        string uName;
        string uDesc;
        double uPrice;
        int uStock;

        cout << "Enter a product's name to update: ";
        cin.ignore();
        getline(cin, userInput);
        Product p = Product::LoadSingleProduct(userInput);

        cout << "Enter product's new name: ";
        getline(cin, uName);
        cout << "Enter product's new description: ";
        getline(cin, uDesc);
        cout << "Enter product's new price: ";
        cin >> uPrice;
        cout << "Enter product's new stock: ";
        cin >> uStock;

        cout << endl << endl << "Old Name: " << p.GetName() << " | New Name: " << uName << endl;
        cout << "Old Description: " << p.GetDescription() << " | New Description: " << uDesc << endl;
        cout << fixed << setprecision(2) << "Old Price: $" << p.GetPrice() << " | New Price: $" << uPrice << endl;
        cout << "Old Stock: " << p.GetStock() << " | New Stock: " << uStock << endl;

        p.SetName(uName);
        p.SetDescription(uDesc);
        p.SetPrice(uPrice);
        p.SetStock(uStock);
        p.SaveProductUpdates();

        Product::LoadProducts();
        enterPause(false);

    }
    else if (s == "5") {
        int year;
        int month;

        cout << "Enter the sales report year: ";
        cin >> year;
        cout << "Enter the sales report month:";
        cin >> month;
        cin.ignore();
        system("cls");
        Sale::PrintMonthlyReport(year, month);

        enterPause(false);
    }
}

void PrintMenu_Products() {
    system("cls");
    cout << "===== Arbor Eight | Products Menu =====" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
    cout << "0) Back to Main Menu" << endl;
    cout << "1) View All Products & Services" << endl;
    cout << "2) View Specific Product or Service" << endl;
    cout << "3) Add New Product or Service" << endl;
    cout << "4) Update Product or Service" << endl;
    cout << "5) View Monthly Sales Report" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
}

void HandleSelection_Products(string s) {
    system("cls");
    string userInput = "";
    if (s == "1") {
        Product::PrintProductList();
        cout << endl << endl << endl << endl;
        Sale::PrintSaleList();
        enterPause();
    }
    else if (s == "2") {
        cout << "Enter a product name: ";
        cin.ignore();
        getline(cin, userInput);
        system("cls");
        Product::PrintSingleProduct(userInput);
        cout << endl << endl << endl << endl;
        Sale::PrintSalesByProduct(userInput);
        enterPause(false);
    }
    else if (s == "3") {
        string nName;
        string nDesc;
        double nPrice;
        int nStock;

        cout << "Enter new product's name: ";
        cin.ignore();
        getline(cin, nName);
        cout << "Enter new product's description: ";
        getline(cin, nDesc);
        cout << "Enter new product's price: ";
        cin >> nPrice;
        cout << "Enter new product's stock: ";
        cin >> nStock;

        Product p = Product();
        if (p.QuickAdd(nName, nDesc, nPrice, nStock)) {
            cout << endl << nName << " has been added as a product." << endl;
            Product::LoadProducts();
        }
        else {
            cout << endl << "Error adding " << nName << " as a product." << endl;
        }
        enterPause(false);
    }
    else if (s == "4") {
        string uName;
        string uDesc;
        double uPrice;
        int uStock;

        cout << "Enter a product's name to update: ";
        cin.ignore();
        getline(cin, userInput);
        Product p = Product::LoadSingleProduct(userInput);

        cout << "Enter product's new name: ";
        getline(cin, uName);
        cout << "Enter product's new description: ";
        getline(cin, uDesc);
        cout << "Enter product's new price: ";
        cin >> uPrice;
        cout << "Enter product's new stock: ";
        cin >> uStock;

        cout << endl << endl << "Old Name: " << p.GetName() << " | New Name: " << uName << endl;
        cout << "Old Description: " << p.GetDescription() << " | New Description: " << uDesc << endl;
        cout << fixed << setprecision(2) << "Old Price: $" << p.GetPrice() << " | New Price: $" << uPrice << endl;
        cout << "Old Stock: " << p.GetStock() << " | New Stock: " << uStock << endl;

        p.SetName(uName);
        p.SetDescription(uDesc);
        p.SetPrice(uPrice);
        p.SetStock(uStock);
        p.SaveProductUpdates();

        Product::LoadProducts();
        enterPause(false);

    }
    else if (s == "5") {
        int year;
        int month;

        cout << "Enter the sales report year: ";
        cin >> year;
        cout << "Enter the sales report month:";
        cin >> month;
        cin.ignore();
        system("cls");
        Sale::PrintMonthlyReport(year, month);

        enterPause(false);
    }
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

void PrintMenu_SalesRep() {
    system("cls");
    cout << "===== Arbor Eight | Sales Rep Menu =====" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
    cout << "0) Back to Main Menu" << endl;
    cout << "1) View All Sales Reps" << endl;
    cout << "2) View Specific Sales Rep" << endl;
    cout << "3) Add New Sales Rep" << endl;
    cout << "4) Update Sales Rep" << endl;
    cout << "5) View Sales Bonus" << endl << endl;
    cout << setw(32) << setfill('+') << "" << setfill(' ') << endl;
}

void HandleSelection_SalesRep(string s) {
    system("cls");
    string userInput = "";
    if (s == "1") {
        SalesRep::PrintSalesRepList();
        enterPause();
    } else if (s == "2") {
        cout << "Enter a sales rep's name: ";
        cin.ignore();
        getline(cin, userInput);
        system("cls");
        SalesRep::PrintSingleSalesRep(userInput);
        cout << endl << endl << endl << endl;
        Sale::PrintSalesBySalesRep(userInput);
        enterPause(false);
    } else if (s == "3") {
        string nName;
        string nAddress;
        string nPhone;
        string nEmail;

        cout << "Enter new sales rep's name: ";
        cin.ignore();
        getline(cin, nName);
        cout << "Enter new sales rep's address: ";
        getline(cin, nAddress);
        cout << "Enter new sales rep's phone number: ";
        getline(cin, nPhone);
        cout << "Enter new sales rep's email: ";
        getline(cin, nEmail);

        SalesRep sr = SalesRep();
        if (sr.QuickAdd(nName, nAddress, nPhone, nEmail, 0)) {
            cout << endl << nName << " has been added as a sales rep." << endl;
            SalesRep::LoadSalesReps();
        } else {
            cout << endl << "Error adding " << nName << " as a sales rep." << endl;
        }
        enterPause(false);
    } else if (s == "4") {
        string uName;
        string uAddress;
        string uPhone;
        string uEmail;

        cout << "Enter a sales rep's name to update: ";
        cin.ignore();
        getline(cin, userInput);
        SalesRep sr = SalesRep::LoadSingleSalesRep(userInput);

        cout << "Enter sales rep's new name: ";
        getline(cin, uName);
        cout << "Enter sales rep's new address: ";
        getline(cin, uAddress);
        cout << "Enter sales rep's new phone number: ";
        getline(cin, uPhone);
        cout << "Enter sales rep's new email: ";
        getline(cin, uEmail);

        cout << endl << endl << "Old Name: " << sr.GetName() << " | New Name: " << uName << endl;
        cout << "Old Address: " << sr.GetAddress() << " | New Name: " << uAddress << endl;
        cout << "Old Phone Number: " << sr.GetPhoneNumber() << " | New Name: " << uPhone << endl;
        cout << "Old Email: " << sr.GetEmail() << " | New Name: " << uEmail << endl;

        sr.SetName(uName);
        sr.SetAddress(uAddress);
        sr.SetPhoneNumber(uPhone);
        sr.SetEmail(uEmail);
        sr.SaveSalesRepUpdates();
        SalesRep::LoadSalesReps();
        enterPause(false);

    } else if (s == "5") {
        cout << "Enter a sales rep's name to view bonus: ";
        cin.ignore();
        getline(cin, userInput);

        SalesRep sr = SalesRep::LoadSingleSalesRep(userInput);
        double totalSalesValue = Sale::GetAnnualSalesByRep(userInput, 2023);
        double bonus = sr.CalculateBonus(totalSalesValue);

        cout << userInput << " had a total of $" << totalSalesValue << " in sales in 2023." << endl;
        cout << "Bonus is 15% of total sales." << endl << endl;

        cout << "Bonus is $" << fixed << setprecision(2) << bonus << endl;
        enterPause(false);
    }
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
            Client::LoadClients();
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

        cout << endl << endl << "Old Name: " << c.GetName() << " | New Name: " << uName << endl;
        cout << "Old Address: " << c.GetAddress() << " | New Name: " << uAddress << endl;
        cout << "Old Phone Number: " << c.GetPhoneNumber() << " | New Name: " << uNumber << endl;
        cout << "Old Email: " << c.GetEmail() << " | New Name: " << uEmail << endl;

        c.SetName(uName);
        c.SetAddress(uAddress);
        c.SetPhoneNumber(uNumber);
        c.SetEmail(uEmail);
        c.SaveClientUpdates();
        Client::LoadClients();
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
    while (ApplicationRunning) {
        string userInput = "";
        if (s == "0") {
            ApplicationRunning = false;
        } else if (s == "1") {
            PrintMenu_Client();
            while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {
                cout << "Please select an option: ";
                cin >> userInput;
            }
            if (userInput == "0") { break; }
            HandleSelection_Client(userInput);
        } else if (s == "2") {
            PrintMenu_SalesRep();
            while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" && userInput != "5") {
                cout << "Please select an option: ";
                cin >> userInput;
            }
            if (userInput == "0") { break; }
            HandleSelection_SalesRep(userInput);
        } else if (s == "3") {
            PrintMenu_Products();
            while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" && userInput != "5") {
                cout << "Please select an option: ";
                cin >> userInput;
            }
            if (userInput == "0") { break; }
            HandleSelection_Products(userInput);
        } else if (s == "4") {
            PrintMenu_Sales();
            while (userInput != "0" && userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {
                cout << "Please select an option: ";
                cin >> userInput;
            }
            if (userInput == "0") { break; }
            HandleSelection_Sales(userInput);
        }
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