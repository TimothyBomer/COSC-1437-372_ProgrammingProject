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
#include "SalesRep.h"


// [TBomer] Initialize static properties
const string SalesRep::SALESREP_FILE = "SalesReps.db";
string SalesRep::SALESREP_DATABASE_PATH = "";
bool SalesRep::isDBInitialized = false;
vector<SalesRep> SalesRep::salesReps;


// [TBomer] Default constructor
SalesRep::SalesRep() {
    Name = "UNKNOWN";
    Address = "UNKNOWN";
    SalesToDate = 0;
}

// [TBomer] Getters and Setters
void SalesRep::SetName(string n) {
    Name = n;
}

void SalesRep::SetAddress(string a) {
    Address = a;
}

void SalesRep::SetSalesToDate(int s) {
    SalesToDate = s;
}

string SalesRep::GetName() {
    return Name;
}

string SalesRep::GetAddress() {
    return Address;
}

int SalesRep::GetSalesToDate() {
    return SalesToDate;
}

void SalesRep::SetDBString(string dbStr) {
    dbString = dbStr;
}

string SalesRep::GetDBString() {
    return dbString;
}


// [TBomer] Build client object from tab-delimited string.
SalesRep SalesRep::BuildFromString(string Line) {
    const string delimeter = "\t";
    size_t pos = 0;
    string curr;
    int linePosition = 1;

    SalesRep sr = SalesRep();
    while ((pos = Line.find(delimeter)) != string::npos) {
        curr = Line.substr(0, pos);
        Line.erase(0, pos + delimeter.length());
        if (linePosition == 1) {
            sr.SetName(curr);
        }
        else if (linePosition == 2) {
            sr.SetAddress(curr);
        }
        linePosition++;
    }
    try {
        if (!Global::IsStringNumber(Line)) {
            throw std::invalid_argument("Unsupported controller type.");
        }
        sr.SetSalesToDate(stoi(Line));
    }
    catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stoi in SalesRep::BuildFromString(). Argument Passed: " << Line << endl;
    }
    return sr;
}

// [TBomer] Creates a new sales rep.
void SalesRep::AddSalesRep() {
    ofstream _salesRepDB(SalesRep::SALESREP_DATABASE_PATH, ios::app);
    if (!_salesRepDB) {
        cout << "Unable to open sales rep database.";
    }
    else {
        if (!Name.empty()) {
            if (!Address.empty()) {
                if (SalesToDate != NULL) {
                    _salesRepDB << Name << "\t" << Address << "\t" << SalesToDate << "\n";
                }
                else {
                    cout << "Error adding sales rep: Sales to Date is NULL." << endl;
                }
            }
            else {
                cout << "Error adding sales rep: Address is empty." << endl;
            }
        }
        else {
            cout << "Error adding sales rep: Name is empty." << endl;
        }

        _salesRepDB.close();
    }
}

// [TBomer] Update DB to use most recent sales rep data.
//              removes old entry and creates a new one.
void SalesRep::SaveSalesRepUpdates() {
    bool repFound = false;
    ifstream _salesRepDB(SalesRep::SALESREP_DATABASE_PATH, ios::app);
    string line;
    if (_salesRepDB.is_open()) {
        while (getline(_salesRepDB, line)) {
            SalesRep sr = SalesRep::BuildFromString(line);
            if (sr.Name == Name) {
                repFound = true;
                break;
            }
        }
        _salesRepDB.close();
        Global::EraseLineFromFile(SalesRep::SALESREP_DATABASE_PATH, line);
        AddSalesRep();
    }
    else {
        cout << "Unable to open sales rep database.";
    }
}

// [TBomer] Initializes the sales rep DB for usage.
//              Creates the sales rep and directory if needed.
void SalesRep::InitializeDatabase() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string SalesRepDatabase = dbTemp.append("\\").append(SALESREP_FILE);
    SalesRep::SALESREP_DATABASE_PATH = SalesRepDatabase;

    if (!Global::file_exists(SalesRepDatabase)) {
        wstring stemp = wstring(DatabaseDirectory.begin(), DatabaseDirectory.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectory(sw, NULL);
        ofstream _salesRepDBCreate(SalesRepDatabase);
        _salesRepDBCreate.close();
    }

    SalesRep::isDBInitialized = true;
}

// [TBomer] Populates the sales rep array from DB.
void SalesRep::LoadSalesReps() {
    ifstream _salesRepDB(SalesRep::SALESREP_DATABASE_PATH);
    string line;
    if (_salesRepDB.is_open()) {
        while (getline(_salesRepDB, line)) {
            SalesRep sr = SalesRep::BuildFromString(line);
            SalesRep::salesReps.push_back(sr);
        }
        _salesRepDB.close();
    }
    else {
        cout << "Unable to open sales rep database.";
    }
}

// [TBomer] Prints the output for a single sales rep
void SalesRep::PrintSingleSalesRep(string pName) {
    cout << "===== Arbor Eight | Sales Rep: " << pName << " =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < SalesRep::salesReps.size(); i++) {
        if (SalesRep::salesReps[i].Name == pName) {
            cout << left << setw(18) << SalesRep::salesReps[i].Name;
            cout << " | ";
            cout << right << setw(13) << SalesRep::salesReps[i].SalesToDate;
            cout << " | ";
            cout << left << setw(35) << SalesRep::salesReps[i].Address;
        }
    }
}

// [TBomer] Loads a single sales rep from the DB and returns a new SalesRep object.
SalesRep SalesRep::LoadSingleSalesRep(string pName) {
    SalesRep c = SalesRep();
    for (unsigned int i = 0; i < SalesRep::salesReps.size(); i++) {
        if (SalesRep::salesReps[i].Name == pName) {
            c.SetName(SalesRep::salesReps[i].Name);
            c.SetAddress(SalesRep::salesReps[i].Address);
            c.SetSalesToDate(SalesRep::salesReps[i].SalesToDate);
        }
    }
    return c;
}

// [TBomer] Prints a formatted sales rep list.
void SalesRep::PrintSalesRepList() {
    cout << "===== Arbor Eight, Sales Reps List =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');

    cout << endl;

    for (unsigned int i = 0; i < SalesRep::salesReps.size(); i++) {
        cout << left << setw(18) << SalesRep::salesReps[i].Name;
        cout << " | ";
        cout << right << setw(13) << SalesRep::salesReps[i].SalesToDate;
        cout << " | ";
        cout << left << setw(35) << SalesRep::salesReps[i].Address;

        if (i != SalesRep::salesReps.size() - 1) {
            cout << endl;
        }
    }
}