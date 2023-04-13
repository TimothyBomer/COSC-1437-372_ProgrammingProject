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
#include "Sale.h"

// [TBomer] Initialize static properties
const string Sale::SALES_FILE = "Sales.db";
string Sale::SALES_DATABASE_PATH = "";
bool Sale::isDBInitialized = false;
vector<Sale> Sale::Sales;


// [TBomer] Default constructor
Sale::Sale() {
    Name = "UNKNOWN";
    Address = "UNKNOWN";
    SalesToDate = 0;
}

// [TBomer] Getters and Setters
void Sale::SetName(string n) {
    Name = n;
}

void Sale::SetAddress(string a) {
    Address = a;
}

void Sale::SetSalesToDate(int s) {
    SalesToDate = s;
}

string Sale::GetName() {
    return Name;
}

string Sale::GetAddress() {
    return Address;
}

int Sale::GetSalesToDate() {
    return SalesToDate;
}

void Sale::SetDBString(string dbStr) {
    dbString = dbStr;
}

string Sale::GetDBString() {
    return dbString;
}


// [TBomer] Build Sale object from tab-delimited string.
Sale Sale::BuildFromString(string Line) {
    const string delimeter = "\t";
    size_t pos = 0;
    string curr;
    int linePosition = 1;

    Sale c = Sale();
    while ((pos = Line.find(delimeter)) != string::npos) {
        curr = Line.substr(0, pos);
        Line.erase(0, pos + delimeter.length());
        if (linePosition == 1) {
            c.SetName(curr);
        }
        else if (linePosition == 2) {
            c.SetAddress(curr);
        }
        linePosition++;
    }
    try {
        if (!Global::IsStringNumber(Line)) {
            throw std::invalid_argument("Unsupported controller type.");
        }
        c.SetSalesToDate(stoi(Line));
    }
    catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stoi in Sale::BuildFromString(). Argument Passed: " << Line << endl;
    }
    return c;
}

// [TBomer] Creates a new Sale.
void Sale::AddSale() {
    ofstream _SaleDB(Sale::SALES_DATABASE_PATH, ios::app);
    if (!_SaleDB) {
        cout << "Unable to open Sale database.";
    }
    else {
        if (!Name.empty()) {
            if (!Address.empty()) {
                if (SalesToDate != NULL) {
                    _SaleDB << Name << "\t" << Address << "\t" << SalesToDate << "\n";
                }
                else {
                    cout << "Error adding Sale: Sales to Date is NULL." << endl;
                }
            }
            else {
                cout << "Error adding Sale: Address is empty." << endl;
            }
        }
        else {
            cout << "Error adding Sale: Name is empty." << endl;
        }

        _SaleDB.close();
    }
}

// [TBomer] Update DB to use most recent Sale data.
//              removes old entry and creates a new one.
void Sale::SaveSaleUpdates() {
    bool SaleFound = false;
    ifstream _SaleDB(Sale::SALES_DATABASE_PATH, ios::app);
    string line;
    if (_SaleDB.is_open()) {
        while (getline(_SaleDB, line)) {
            Sale c = Sale::BuildFromString(line);
            if (c.Name == Name) {
                SaleFound = true;
                break;
            }
        }
        _SaleDB.close();
        Global::EraseLineFromFile(Sale::SALES_DATABASE_PATH, line);
        AddSale();
    }
    else {
        cout << "Unable to open Sale database.";
    }
}

// [TBomer] Initializes the Sale DB for usage.
//              Creates the database and directory if needed.
void Sale::InitializeDatabase() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string SaleDatabase = dbTemp.append("\\").append(SALES_FILE);
    Sale::SALES_DATABASE_PATH = SaleDatabase;

    if (!Global::file_exists(SaleDatabase)) {
        wstring stemp = wstring(DatabaseDirectory.begin(), DatabaseDirectory.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectory(sw, NULL);
        ofstream _SaleDBCreate(SaleDatabase);
        _SaleDBCreate.close();
    }

    Sale::isDBInitialized = true;
}

// [TBomer] Populates the Sales array from DB.
void Sale::LoadSales() {
    ifstream _SaleDB(Sale::SALES_DATABASE_PATH);
    string line;
    if (_SaleDB.is_open()) {
        while (getline(_SaleDB, line)) {
            Sale c = Sale::BuildFromString(line);
            Sale::Sales.push_back(c);
        }
        _SaleDB.close();
    }
    else {
        cout << "Unable to open Sale database.";
    }
}

// [TBomer] Prints the output for a single Sale
void Sale::PrintSingleSale(string pName) {
    cout << "===== Arbor Eight | Customer: " << pName << " =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].Name == pName) {
            cout << left << setw(18) << Sale::Sales[i].Name;
            cout << " | ";
            cout << right << setw(13) << Sale::Sales[i].SalesToDate;
            cout << " | ";
            cout << left << setw(35) << Sale::Sales[i].Address;
        }
    }
}

// [TBomer] Loads a single Sale from the DB and returns a new Sale object.
Sale Sale::LoadSingleSale(string pName) {
    Sale c = Sale();
    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].Name == pName) {
            c.SetName(Sale::Sales[i].Name);
            c.SetAddress(Sale::Sales[i].Address);
            c.SetSalesToDate(Sale::Sales[i].SalesToDate);
        }
    }
    return c;
}

// [TBomer] Prints a formatted Sale list.
void Sale::PrintSaleList() {
    cout << "===== Arbor Eight, Sales List =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');

    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        cout << left << setw(18) << Sale::Sales[i].Name;
        cout << " | ";
        cout << right << setw(13) << Sale::Sales[i].SalesToDate;
        cout << " | ";
        cout << left << setw(35) << Sale::Sales[i].Address;

        if (i != Sale::Sales.size() - 1) {
            cout << endl;
        }
    }
}