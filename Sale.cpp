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
    Date = "UNKNOWN";
    ClientName = "UNKNOWN";
    SalesRepName = "UNKNOWN";
    ProductName = "UNKNOWN";
    ProductQty = 0;
    SubTotal = 0.00;
}

// [TBomer] Getters and Setters
void Sale::SetSaleID(int id) {
    SaleID = id;
}

void Sale::SetDate(string d) {
    Date = d;
}

void Sale::SetClientName(string cN) {
    ClientName = cN;
}

void Sale::SetSalesRepName(string srN) {
    SalesRepName = srN;
}

void Sale::SetProductName(string pN) {
    ProductName = pN;
}

void Sale::SetProductQty(int q) {
    ProductQty = q;
}

void Sale::SetSubTotal(double sT) {
    SubTotal = sT;
}

int Sale::GetSaleID() {
    return SaleID;
}

string Sale::GetDate() {
    return Date;
}

string Sale::GetClientName() {
    return ClientName;
}

string Sale::GetSalesRepName() {
    return SalesRepName;
}

string Sale::GetProductName() {
    return ProductName;
}

int Sale::GetProductQty() {
    return ProductQty;
}

double Sale::GetSubTotal() {
    return SubTotal;
}

void Sale::SetDBString(string dbStr) {
    dbString = dbStr;
}

string Sale::GetDBString() {
    return dbString;
}

void Sale::GenerateSaleID() {
    srand((unsigned)time(NULL));
    SaleID = 10000000 + (rand() % 10000001);
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
            try {
                if (!Global::IsStringNumber(curr)) {
                    throw std::invalid_argument("Unsupported controller type.");
                }
                c.SetSaleID(stoi(curr));
            } catch (invalid_argument e) {
                cout << "Warning: Invalid argument passed to stoi in Sale::BuildFromString(). Argument Passed: " << curr << endl;
            }
        } else if (linePosition == 2) {
            c.SetDate(curr);
        } else if (linePosition == 3) {
            c.SetClientName(curr);
        } else if (linePosition == 4) {
            c.SetSalesRepName(curr);
        } else if (linePosition == 5) {
            c.SetProductName(curr);
        } else if (linePosition == 6) {
            try {
                if (!Global::IsStringNumber(curr)) {
                    throw std::invalid_argument("Unsupported controller type.");
                }
                curr.erase(remove_if(curr.begin(), curr.end(), ::isspace), curr.end());
                c.SetProductQty(stoi(curr));
            } catch (invalid_argument e) {
                cout << "Warning: Invalid argument passed to stoi in Sale::BuildFromString(). Argument Passed: " << curr << endl;
            }
        }
        linePosition++;
    }
    try {
        if (!Global::IsStringNumber(Line)) {
            throw std::invalid_argument("Unsupported controller type.");
        }
        c.SetSubTotal(stod(Line));
    }
    catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stod in Client::BuildFromString(). Argument Passed: " << Line << endl;
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
        

        if (SaleID != NULL) {
            if (!Date.empty()) {
                if (!ClientName.empty()) {
                    if (!SalesRepName.empty()) {
                        if (!ProductName.empty()) {
                            if (ProductQty != NULL) {
                                if (SubTotal != NULL) {
                                    _SaleDB << SaleID << "\t" << Date << "\t" << ClientName << "\t" << SalesRepName << "\t" << ProductName << "\t" << ProductQty << "\t" << SubTotal << "\n";
                                } else {
                                    cout << "Error adding Sale: Sub Total is NULL." << endl;
                                }
                            } else {
                                cout << "Error adding Sale: Product quantity is NULL." << endl;
                            }
                        } else {
                            cout << "Error adding Sale: Product name is empty.." << endl;
                        }
                    } else {
                        cout << "Error adding Sale: Sales Rep name is empty.." << endl;
                    }
                } else {
                    cout << "Error adding Sale: Client name is empty." << endl;
                }
            } else {
                cout << "Error adding Sale: Date is empty." << endl;
            }
        } else {
            cout << "Error adding Sale: Sale ID is NULL." << endl;
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
            if (c.SaleID == SaleID) {
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
void Sale::PrintSingleSale(int SaleID) {
    cout << "===== Arbor Eight | Sale: " << SaleID << " =====" << endl << endl;
    cout << left << setw(15) << "Sale ID";
    cout << left << setw(21) << "Date of Sale";
    cout << left << setw(21) << "Client";
    cout << left << setw(21) << "Sales Rep";
    cout << left << setw(21) << "Product";
    cout << left << setw(12) << "Quantity";
    cout << left << setw(9) << "Sub Total" << endl;
    cout << setw(140) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].SaleID == SaleID) {
            cout << left << setw(12) << Sale::Sales[i].SaleID;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].Date;
            cout << " | ";
            cout << right << setw(18) << Sale::Sales[i].ClientName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].SalesRepName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].ProductName;
            cout << " | ";
            cout << left << setw(9) << Sale::Sales[i].ProductQty;
            cout << " | ";
            string t = to_string(Sale::Sales[i].SubTotal);
            t = "$" + t;
            t.erase(t.find_last_not_of('0') + 1, string::npos);
            cout << left << setw(6) << t;
        }
    }
}

// [TBomer] Loads a single Sale from the DB and returns a new Sale object.
Sale Sale::LoadSingleSale(int SaleID) {
    Sale c = Sale();
    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].SaleID == SaleID) {
            c.SetSaleID(Sale::Sales[i].SaleID);
            c.SetDate(Sale::Sales[i].Date);
            c.SetClientName(Sale::Sales[i].ClientName);
            c.SetSalesRepName(Sale::Sales[i].SalesRepName);
            c.SetProductName(Sale::Sales[i].ProductName);
            c.SetProductQty(Sale::Sales[i].ProductQty);
            c.SetSubTotal(Sale::Sales[i].SubTotal);
        }
    }
    return c;
}

// [TBomer] Prints a formatted Sale list.
void Sale::PrintSaleList() {
    cout << "===== Arbor Eight, Sales List =====" << endl << endl;
    cout << left << setw(15) << "Sale ID";
    cout << left << setw(21) << "Date of Sale";
    cout << left << setw(21) << "Client";
    cout << left << setw(21) << "Sales Rep";
    cout << left << setw(21) << "Product";
    cout << left << setw(12) << "Quantity";
    cout << left << setw(9) << "Sub Total" << endl;
    cout << setw(140) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        cout << left << setw(12) << Sale::Sales[i].SaleID;
        cout << " | ";
        cout << left << setw(18) << Sale::Sales[i].Date;
        cout << " | ";
        cout << right << setw(18) << Sale::Sales[i].ClientName;
        cout << " | ";
        cout << left << setw(18) << Sale::Sales[i].SalesRepName;
        cout << " | ";
        cout << left << setw(18) << Sale::Sales[i].ProductName;
        cout << " | ";
        cout << left << setw(9) << Sale::Sales[i].ProductQty;
        cout << " | ";
        string t = to_string(Sale::Sales[i].SubTotal);
        t = "$" + t;
        t.erase(t.find_last_not_of('0') + 1, string::npos);
        cout << left << setw(6) << t;

        if (i != Sale::Sales.size() - 1) {
            cout << endl;
        }
    }
}



double Sale::GetAnnualSales(int y) {
    double AnnualSales = 0.00;
    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {

        int saleYear = stoi(Sale::Sales[i].Date.substr(0, 8));
        
        if (saleYear == y) {
            AnnualSales += Sale::Sales[i].SubTotal;
        }
    }
    return AnnualSales;
}

void Sale::PrintSalesByProduct(string p) {
    cout << "===== Arbor Eight, Sales List =====" << endl << endl;
    cout << left << setw(15) << "Sale ID";
    cout << left << setw(21) << "Date of Sale";
    cout << left << setw(21) << "Client";
    cout << left << setw(21) << "Sales Rep";
    cout << left << setw(21) << "Product";
    cout << left << setw(12) << "Quantity";
    cout << left << setw(9) << "Sub Total" << endl;
    cout << setw(140) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].ProductName == p) {
            cout << left << setw(12) << Sale::Sales[i].SaleID;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].Date;
            cout << " | ";
            cout << right << setw(18) << Sale::Sales[i].ClientName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].SalesRepName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].ProductName;
            cout << " | ";
            cout << left << setw(9) << Sale::Sales[i].ProductQty;
            cout << " | ";
            string t = to_string(Sale::Sales[i].SubTotal);
            t = "$" + t;
            t.erase(t.find_last_not_of('0') + 1, string::npos);
            cout << left << setw(6) << t;
            if (i != Sale::Sales.size() - 1) {
                cout << endl;
            }
        }
    }
}

void Sale::PrintSalesByCustomer(string c) {
    cout << "===== Arbor Eight, Sales List =====" << endl << endl;
    cout << left << setw(15) << "Sale ID";
    cout << left << setw(21) << "Date of Sale";
    cout << left << setw(21) << "Client";
    cout << left << setw(21) << "Sales Rep";
    cout << left << setw(21) << "Product";
    cout << left << setw(12) << "Quantity";
    cout << left << setw(9) << "Sub Total" << endl;
    cout << setw(140) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].ClientName == p) {
            cout << left << setw(12) << Sale::Sales[i].SaleID;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].Date;
            cout << " | ";
            cout << right << setw(18) << Sale::Sales[i].ClientName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].SalesRepName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].ProductName;
            cout << " | ";
            cout << left << setw(9) << Sale::Sales[i].ProductQty;
            cout << " | ";
            string t = to_string(Sale::Sales[i].SubTotal);
            t = "$" + t;
            t.erase(t.find_last_not_of('0') + 1, string::npos);
            cout << left << setw(6) << t;
            if (i != Sale::Sales.size() - 1) {
                cout << endl;
            }
        }
    }
}

void Sale::PrintSalesBySalesRep(string sR) {
    cout << "===== Arbor Eight, Sales List =====" << endl << endl;
    cout << left << setw(15) << "Sale ID";
    cout << left << setw(21) << "Date of Sale";
    cout << left << setw(21) << "Client";
    cout << left << setw(21) << "Sales Rep";
    cout << left << setw(21) << "Product";
    cout << left << setw(12) << "Quantity";
    cout << left << setw(9) << "Sub Total" << endl;
    cout << setw(140) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Sale::Sales.size(); i++) {
        if (Sale::Sales[i].SalesRepName == p) {
            cout << left << setw(12) << Sale::Sales[i].SaleID;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].Date;
            cout << " | ";
            cout << right << setw(18) << Sale::Sales[i].ClientName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].SalesRepName;
            cout << " | ";
            cout << left << setw(18) << Sale::Sales[i].ProductName;
            cout << " | ";
            cout << left << setw(9) << Sale::Sales[i].ProductQty;
            cout << " | ";
            string t = to_string(Sale::Sales[i].SubTotal);
            t = "$" + t;
            t.erase(t.find_last_not_of('0') + 1, string::npos);
            cout << left << setw(6) << t;
            if (i != Sale::Sales.size() - 1) {
                cout << endl;
            }
        }
    }
}