/*  -----------------------------------------------------------------
    Class:
        Name:           Product
        Definition:     Product.cpp
        Header:         Product.h

    Description:    Product class to handle all product related requests.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
------------------------------------------------------------------- */
#include "Product.h"

// [TBomer] Initialize static properties
const string Product::PRODUCT_FILE = "Products.db";
string Product::PRODUCT_DATABASE_PATH = "";
bool Product::isDBInitialized = false;
vector<Product> Product::Products;


// [TBomer] Default constructor
Product::Product() {
    Name = "UNKNOWN";
    Description = "UNKNOWN";
    Price = 0.00;
    Stock = 0;
}

// [TBomer] Getters and Setters
void Product::SetName(string n) {
    Name = n;
}

void Product::SetDescription(string d) {
    Description = d;
}

void Product::SetPrice(double p) {
    Price = p;
}

void Product::SetStock(int s) {
    Stock = s;
}

string Product::GetName() {
    return Name;
}

string Product::GetDescription() {
    return Description;
}

int Product::GetStock() {
    return Stock;
}

double Product::GetPrice() {
    return Price;
}

void Product::SetDBString(string dbStr) {
    dbString = dbStr;
}

string Product::GetDBString() {
    return dbString;
}


// [TBomer] Build Product object from tab-delimited string.
Product Product::BuildFromString(string Line) {
    const string delimeter = "\t";
    size_t pos = 0;
    string curr;
    int linePosition = 1;

    Product c = Product();
    while ((pos = Line.find(delimeter)) != string::npos) {
        curr = Line.substr(0, pos);
        Line.erase(0, pos + delimeter.length());
        if (linePosition == 1) {
            c.SetName(curr);
        } else if (linePosition == 2) {
            c.SetDescription(curr);
        } else if (linePosition == 3) {
            try {
                if (!Global::IsStringNumber(curr)) {
                    throw std::invalid_argument("Unsupported controller type.");
                }
                c.SetPrice(stod(curr));
            } catch (invalid_argument e) {
                cout << "Warning: Invalid argument passed to stoi in Product::BuildFromString(). Argument Passed: " << curr << endl;
            }
        }
        linePosition++;
    }
    try {
        if (!Global::IsStringNumber(Line)) {
            throw std::invalid_argument("Unsupported controller type.");
        }
        c.SetStock(stoi(Line));
    } catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stoi in Product::BuildFromString(). Argument Passed: " << Line << endl;
    }
    return c;
}

// [TBomer] Creates a new Product.
void Product::AddProduct() {
    ofstream _ProductDB(Product::PRODUCT_DATABASE_PATH, ios::app);
    if (!_ProductDB) {
        cout << "Unable to open Product database.";
    }
    else {
        if (!Name.empty()) {
            if (!Description.empty()) {
                if (Price != NULL) {
                    if (Stock != NULL) {
                        _ProductDB << Name << "\t" << Description << "\t" << Price << "\t" << Stock << "\n";
                    } else {
                        cout << "Error adding Product: Stock is NULL." << endl;
                    }
                }
                else {
                    cout << "Error adding Product: Price is NULL." << endl;
                }
            }
            else {
                cout << "Error adding Product: Description is empty." << endl;
            }
        }
        else {
            cout << "Error adding Product: Name is empty." << endl;
        }

        _ProductDB.close();
    }
}

// [TBomer] Update DB to use most recent Product data.
//              removes old entry and creates a new one.
void Product::SaveProductUpdates() {
    bool ProductFound = false;
    ifstream _ProductDB(Product::PRODUCT_DATABASE_PATH, ios::app);
    string line;
    if (_ProductDB.is_open()) {
        while (getline(_ProductDB, line)) {
            Product c = Product::BuildFromString(line);
            if (c.Name == Name) {
                ProductFound = true;
                break;
            }
        }
        _ProductDB.close();
        Global::EraseLineFromFile(Product::PRODUCT_DATABASE_PATH, line);
        AddProduct();
    }
    else {
        cout << "Unable to open Product database.";
    }
}

// [TBomer] Initializes the Product DB for usage.
//              Creates the database and directory if needed.
void Product::InitializeDatabase() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ProductDatabase = dbTemp.append("\\").append(PRODUCT_FILE);
    Product::PRODUCT_DATABASE_PATH = ProductDatabase;

    if (!Global::file_exists(ProductDatabase)) {
        wstring stemp = wstring(DatabaseDirectory.begin(), DatabaseDirectory.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectory(sw, NULL);
        ofstream _ProductDBCreate(ProductDatabase);
        _ProductDBCreate.close();
    }

    Product::isDBInitialized = true;
}

// [TBomer] Populates the Products array from DB.
void Product::LoadProducts() {
    ifstream _ProductDB(Product::PRODUCT_DATABASE_PATH);
    string line;
    if (_ProductDB.is_open()) {
        while (getline(_ProductDB, line)) {
            Product c = Product::BuildFromString(line);
            Product::Products.push_back(c);
        }
        _ProductDB.close();
    }
    else {
        cout << "Unable to open Product database.";
    }
}

// [TBomer] Prints the output for a single Product
void Product::PrintSingleProduct(string pName) {
    cout << "===== Arbor Eight | Product: " << pName << " =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(28) << "Description";
    cout << left << setw(12) << "Price";
    cout << left << setw(12) << "Stock" << endl;
    cout << setw(68) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Product::Products.size(); i++) {
        if (Product::Products[i].Name == pName) {
            cout << left << setw(18) << Product::Products[i].Name;
            cout << " | ";
            cout << left << setw(25) << Product::Products[i].Description;
            cout << " | ";
            cout << left << setw(9) << Product::Products[i].Price;
            cout << " | ";
            cout << left << setw(9) << Product::Products[i].Stock;
        }
    }
}

// [TBomer] Loads a single Product from the DB and returns a new Product object.
Product Product::LoadSingleProduct(string pName) {
    Product c = Product();
    for (unsigned int i = 0; i < Product::Products.size(); i++) {
        if (Product::Products[i].Name == pName) {
            c.SetName(Product::Products[i].Name);
            c.SetDescription(Product::Products[i].Description);
            c.SetPrice(Product::Products[i].Price);
            c.SetStock(Product::Products[i].Stock);
        }
    }
    return c;
}

// [TBomer] Prints a formatted Product list.
void Product::PrintProductList() {
    cout << "===== Arbor Eight, Product List =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(28) << "Description";
    cout << left << setw(12) << "Price";
    cout << left << setw(12) << "Stock" << endl;
    cout << setw(68) << setfill('-') << "" << setfill(' ');

    cout << endl;

    for (unsigned int i = 0; i < Product::Products.size(); i++) {
        cout << left << setw(18) << Product::Products[i].Name;
        cout << " | ";
        cout << left << setw(25) << Product::Products[i].Description;
        cout << " | ";
        cout << left << setw(9) << Product::Products[i].Price;
        cout << " | ";
        cout << left << setw(9) << Product::Products[i].Stock;

        if (i != Product::Products.size() - 1) {
            cout << endl;
        }
    }
}