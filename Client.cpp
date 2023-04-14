/*  -----------------------------------------------------------------
    Class:
        Name:           Client
        Definition:     Client.cpp
        Header:         Client.h

    Description:    Client class to handle all client related requests.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
        TBomer          04/12/2023      Completed client class.
------------------------------------------------------------------- */
#include "Client.h"

// [TBomer] Initialize static properties
const string Client::CLIENT_FILE = "Clients.db";
string Client::CLIENT_DATABASE_PATH = "";
bool Client::isDBInitialized = false;
vector<Client> Client::clients;


// [TBomer] Default constructor
Client::Client() {
    Name = "UNKNOWN";
    Address = "UNKNOWN";
    SalesToDate = 0;
}

// [TBomer] Getters and Setters
void Client::SetName(string n) {
    Name = n;
}

void Client::SetAddress(string a) {
    Address = a;
}

void Client::SetSalesToDate(int s) {
    SalesToDate = s;
}

void Client::SetPhoneNumber(string pNum) {
    PhoneNumber = pNum;
}

void Client::SetEmail(string e) {
    Email = e;
}

string Client::GetName() {
    return Name;
}

string Client::GetAddress() {
    return Address;
}

int Client::GetSalesToDate() {
    return SalesToDate;
}

string Client::GetPhoneNumber() {
    return PhoneNumber;
}

string Client::GetEmail() {
    return Email;
}

void Client::SetDBString(string dbStr) {
    dbString = dbStr;
}

string Client::GetDBString() {
    return dbString;
}


// [TBomer] Build client object from tab-delimited string.
Client Client::BuildFromString(string Line) {
    const string delimeter = "\t";
    size_t pos = 0;
    string curr;
    int linePosition = 1;

    Client c = Client();
    while ((pos = Line.find(delimeter)) != string::npos) {
        curr = Line.substr(0, pos);
        Line.erase(0, pos + delimeter.length());
        if (linePosition == 1) {
            c.SetName(curr);
        } else if (linePosition == 2) {
            c.SetAddress(curr);
        } else if (linePosition == 3) {
            c.SetPhoneNumber(curr);
        } else if (linePosition == 4) {
            c.SetEmail(curr);
        }
        linePosition++;
    }
    try {
        if (!Global::IsStringNumber(Line)) {
            throw std::invalid_argument("Unsupported controller type.");
        }
        c.SetSalesToDate(stoi(Line));
    } catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stoi in Client::BuildFromString(). Argument Passed: " << Line << endl;
    }
    return c;
}

// [TBomer] Creates a new client.
bool Client::AddClient() {
    bool rVal = false;
    ofstream _clientDB(Client::CLIENT_DATABASE_PATH, ios::app);
    if (!_clientDB) {
        cout << "Unable to open client database.";
    } else {
        if (!Name.empty()) {
            if (!Address.empty()) {
                if (!PhoneNumber.empty()) {
                    if (!Email.empty()) {
                        if (SalesToDate != NULL || SalesToDate == 0) {
                            _clientDB << Name << "\t" << Address << "\t" << PhoneNumber << "\t" << Email << "\t" << SalesToDate << "\n";
                            rVal = true;
                        } else {
                            cout << "Error adding client: Sales to Date is NULL." << endl;
                        }
                    } else {
                        cout << "Error adding client: Email address is empty." << endl;
                    }
                } else {
                    cout << "Error adding client: Phone number is empty." << endl;
                }
            } else {
                cout << "Error adding client: Address is empty." << endl;
            }
        } else {
            cout << "Error adding client: Name is empty." << endl;
        }
        _clientDB.close();
    }
    return rVal;
}

bool Client::QuickAdd(string n, string a, int s, string pN, string e) {
    Client c = Client();
    c.SetName(n);
    c.SetAddress(a);
    c.SetSalesToDate(s);
    c.SetPhoneNumber(pN);
    c.SetEmail(e);
    return c.AddClient();
}

// [TBomer] Update DB to use most recent client data.
//              removes old entry and creates a new one.
void Client::SaveClientUpdates() {
    bool ClientFound = false;
    ifstream _clientDB(Client::CLIENT_DATABASE_PATH, ios::app);
    string line;
    if (_clientDB.is_open()) {
        while (getline(_clientDB, line)) {
            Client c = Client::BuildFromString(line);
            if (c.Name == Name) {
                ClientFound = true;
                break;
            }
        }
        _clientDB.close();
        Global::EraseLineFromFile(Client::CLIENT_DATABASE_PATH, line);
        AddClient();
    }
    else {
        cout << "Unable to open client database.";
    } 
}

// [TBomer] Initializes the client DB for usage.
//              Creates the database and directory if needed.
void Client::InitializeDatabase() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ClientDatabase = dbTemp.append("\\").append(CLIENT_FILE);
    Client::CLIENT_DATABASE_PATH = ClientDatabase;

    if (!Global::file_exists(ClientDatabase)) {
        wstring stemp = wstring(DatabaseDirectory.begin(), DatabaseDirectory.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectory(sw, NULL);
        ofstream _clientDBCreate(ClientDatabase);
        _clientDBCreate.close();
    }

    Client::isDBInitialized = true;
}

// [TBomer] Populates the clients array from DB.
void Client::LoadClients() {
    ifstream _clientDB(Client::CLIENT_DATABASE_PATH);
    string line;
    if (_clientDB.is_open()) {
        while (getline(_clientDB, line)) {
            Client c = Client::BuildFromString(line);
            Client::clients.push_back(c);
        }
        _clientDB.close();
    }
    else {
        cout << "Unable to open client database.";
    }
}

// [TBomer] Prints the output for a single client
void Client::PrintSingleClient(string pName) {
    cout << "===== Arbor Eight | Customer: " << pName << " =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(16) << "Phone Number";
    cout << left << setw(35) << "Email";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(132) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Client::clients.size(); i++) {
        if (Client::clients[i].Name == pName) {
            cout << left << setw(18) << Client::clients[i].Name;
            cout << " | ";
            cout << right << setw(13) << Client::clients[i].SalesToDate;
            cout << " | ";
            cout << left << setw(13) << Client::clients[i].PhoneNumber;
            cout << " | ";
            cout << left << setw(32) << Client::clients[i].Email;
            cout << " | ";
            cout << left << setw(35) << Client::clients[i].Address;
        }
    }
}

// [TBomer] Loads a single client from the DB and returns a new Client object.
Client Client::LoadSingleClient(string pName) {
    Client c = Client();
    for (unsigned int i = 0; i < Client::clients.size(); i++) {
        if (Client::clients[i].Name == pName) {            
            c.SetName(Client::clients[i].Name);
            c.SetAddress(Client::clients[i].Address);
            c.SetPhoneNumber(Client::clients[i].PhoneNumber);
            c.SetEmail(Client::clients[i].Email);
            c.SetSalesToDate(Client::clients[i].SalesToDate);
        }
    }
    return c;
}

// [TBomer] Prints a formatted client list.
void Client::PrintClientList() {
    cout << "===== Arbor Eight, Client List =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');

    cout << endl;

    for (unsigned int i = 0; i < Client::clients.size(); i++) {
        cout << left << setw(18) << Client::clients[i].Name;
        cout << " | ";
        cout << right << setw(13) << Client::clients[i].SalesToDate;
        cout << " | ";
        cout << left << setw(35) << Client::clients[i].Address;

        if (i != Client::clients.size() - 1) {
            cout << endl;
        }
    }
}