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
------------------------------------------------------------------- */
#include "Client.h"

const string Client::CLIENT_FILE = "Clients.db";
bool Client::isDBInitialized = false;
vector<Client> Client::clients;


// [TBomer] Default constructor
Client::Client() {
    Name = "UNKNOWN";
    Address = "UNKNOWN";
    SalesToDate = 0;
}

void Client::SetName(string n) {
    Name = n;
}

void Client::SetAddress(string a) {
    Address = a;
}

void Client::SetSalesToDate(int s) {
    SalesToDate = s;
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

void Client::SetDBString(string dbStr) {
    dbString = dbStr;
}

string Client::GetDBString() {
    return dbString;
}

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
        
    } catch (invalid_argument e) {
        cout << "Warning: Invalid argument passed to stoi in Client::BuildFromString(). Argument Passed: " << Line << endl;
    }
    

    return c;
}

void Client::AddClient() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ClientDatabase = dbTemp.append("\\").append(CLIENT_FILE);
    ofstream _clientDB(ClientDatabase, ios::app);

    if (!_clientDB) {
        cout << "Unable to open client database.";
    } else {
        if (!Name.empty()) {
            if (!Address.empty()) {
                if (SalesToDate != NULL) {
                    _clientDB << Name << "\t" << Address << "\t" << SalesToDate << "\n";
                } else {
                    cout << "Error adding client: Sales to Date is NULL." << endl;
                }
            } else {
                cout << "Error adding client: Address is empty." << endl;
            }
        } else {
            cout << "Error adding client: Name is empty." << endl;
        }
        
        _clientDB.close();
    }
}

void Client::SaveClientUpdates() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ClientDatabase = dbTemp.append("\\").append(CLIENT_FILE);

    bool ClientFound = false;

    ifstream _clientDB(ClientDatabase);
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
        Global::EraseLineFromFile(ClientDatabase, line);
        AddClient();
    }
    else {
        cout << "Unable to open client database.";
    } 
}





void Client::InitializeDatabase() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ClientDatabase = dbTemp.append("\\").append(CLIENT_FILE);

    if (!Global::file_exists(ClientDatabase)) {
        wstring stemp = wstring(DatabaseDirectory.begin(), DatabaseDirectory.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectory(sw, NULL);
        ofstream _clientDBCreate(ClientDatabase);
        _clientDBCreate.close();
    } 

    Client::isDBInitialized = true;
}


void Client::LoadClients() {
    string tempGlobal = Global::CURRENT_DIR;
    string DatabaseDirectory = tempGlobal.append("\Database");
    string dbTemp = DatabaseDirectory;
    string ClientDatabase = dbTemp.append("\\").append(CLIENT_FILE);

    ifstream _clientDB(ClientDatabase);
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

void Client::PrintSingleClient(string pName) {
    cout << "===== Arbor Eight | Customer: " << pName << " =====" << endl << endl;
    cout << left << setw(21) << "Name";
    cout << left << setw(16) << "Sales to Date";
    cout << left << setw(30) << "Address" << endl;
    cout << setw(64) << setfill('-') << "" << setfill(' ');
    cout << endl;

    for (unsigned int i = 0; i < Client::clients.size(); i++) {
        if (Client::clients[i].Name == pName) {
            cout << left << setw(18) << Client::clients[i].Name;
            cout << " | ";
            cout << right << setw(13) << Client::clients[i].SalesToDate;
            cout << " | ";
            cout << left << setw(35) << Client::clients[i].Address;
        }
    }
}

Client Client::LoadSingleClient(string pName) {
    Client c = Client();
    for (unsigned int i = 0; i < Client::clients.size(); i++) {
        if (Client::clients[i].Name == pName) {            
            c.SetName(Client::clients[i].Name);
            c.SetAddress(Client::clients[i].Address);
            c.SetSalesToDate(Client::clients[i].SalesToDate);
        }
    }
    return c;
}

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