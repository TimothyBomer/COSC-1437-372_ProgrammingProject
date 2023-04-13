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
        TBomer          04/12/2023      Added:
                                            * GetName()
                                            * GetAddress()
                                            * GetSalesToDate()
                                            * AddClient()
                                            * SaveClientUpdates()
                                            * PrintSingleClient()
                                            * LoadSingleClient()
                                            * SetDBString()
                                            * GetDBString()
                                            * dbString private property
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
class Client {
    public:
        // [TBomer] Constants. This holds the location of the Clients.db file
        static const string CLIENT_FILE;
        static string CLIENT_DATABASE_PATH;

        // [TBomer] Constructors
        Client();

        // Getters and Setters
        void SetName(string n);
        void SetAddress(string a);
        void SetSalesToDate(int s);
        void SetPhoneNumber(string p);
        void SetEmail(string e);
        string GetName();
        string GetAddress();
        int GetSalesToDate();
        string GetPhoneNumber();
        string GetEmail();

        // [TBomer] Mutators
        void AddClient();
        void SaveClientUpdates();
        
        // [TBomer] Static Functions
        static void InitializeDatabase();
        static void LoadClients();
        static void PrintClientList();
        static void PrintSingleClient(string pName);
        static Client LoadSingleClient(string pName);
        static Client BuildFromString(string s);
        
        static vector<Client> clients; // [TBomer] This holds the list of clients. Populated by the LoadClients() function call.

    private:
        string Name;
        string Address;
        int SalesToDate;
        string PhoneNumber;
        string Email;
        static bool isDBInitialized;

        // [TBomer] When loading a client by name, the dbString property holds the content of the database line for the client.
        //              This is used for updating the client information.
        string dbString;
        void SetDBString(string s);
        string GetDBString();

};