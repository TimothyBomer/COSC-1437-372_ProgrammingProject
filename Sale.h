/*  -----------------------------------------------------------------
    Class:
        Name:           Sale
        Definition:     Sale.cpp
        Header:         Sale.h

    Description:    Sale class to handle all sales related requests.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
------------------------------------------------------------------- */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include <windows.h>
#include "Global.h";
using namespace std;

/*
    Possible data properties:
        Client name
        Sale date
        product name
        product count
        subtotal
*/

#pragma once
class Sale {
public:
    // [TBomer] Constants. This holds the location of the Sales.db file
    static const string SALES_FILE;
    static string SALES_DATABASE_PATH;

    // [TBomer] Constructors
    Sale();

    // Getters and Setters
    void SetName(string n);
    void SetAddress(string a);
    void SetSalesToDate(int s);
    string GetName();
    string GetAddress();
    int GetSalesToDate();

    // [TBomer] Mutators
    void AddSale();
    void SaveSaleUpdates();

    // [TBomer] Static Functions
    static void InitializeDatabase();
    static void LoadSales();
    static void PrintSaleList();
    static void PrintSingleSale(string pName);
    static Sale LoadSingleSale(string pName);
    static Sale BuildFromString(string s);

    static vector<Sale> Sales; // [TBomer] This holds the list of Sales. Populated by the LoadSales() function call.

private:
    string Name;
    string Address;
    int SalesToDate;
    static bool isDBInitialized;

    // [TBomer] When loading a Sale by name, the dbString property holds the content of the database line for the Sale.
    //              This is used for updating the Sale information.
    string dbString;
    void SetDBString(string s);
    string GetDBString();

};