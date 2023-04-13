/*  -----------------------------------------------------------------
    Class:
        Name:           SalesPrep
        Definition:     SalesRep.cpp
        Header:         SalesRep.h

    Description:    Sales Rep class to handle all sales rep related requests.
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

#pragma once
class SalesRep {
    public:
        // [TBomer] Constants. This holds the location of the SalesReps.db file
        static const string SALESREP_FILE;
        static string SALESREP_DATABASE_PATH;

        // [TBomer] Constructors
        SalesRep();

        // Getters and Setters
        void SetName(string n);
        void SetAddress(string a);
        void SetSalesToDate(int s);
        string GetName();
        string GetAddress();
        int GetSalesToDate();

        // [TBomer] Mutators
        void AddSalesRep();
        void SaveSalesRepUpdates();

        // [TBomer] Static Functions
        static void InitializeDatabase();
        static void LoadSalesReps();
        static void PrintSalesRepList();
        static void PrintSingleSalesRep(string pName);
        static SalesRep LoadSingleSalesRep(string pName);
        static SalesRep BuildFromString(string s);

        static vector<SalesRep> salesReps; // [TBomer] This holds the list of sales reps. Populated by the LoadSalesRep() function call.

    private:
        string Name;
        string Address;
        int SalesToDate;
        static bool isDBInitialized;

        // [TBomer] When loading a sales rep by name, the dbString property holds the content of the database line for the sales rep.
        //              This is used for updating the sales rep information.
        string dbString;
        void SetDBString(string s);
        string GetDBString();

};