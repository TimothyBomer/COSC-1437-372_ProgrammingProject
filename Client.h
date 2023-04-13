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
        Client();
        void SetName(string n);
        void SetAddress(string a);
        void SetSalesToDate(int s);
        
        static void InitializeDatabase();
        static void LoadClients();
        static void PrintClientList();
        static void PrintSingleClient(string pName);
        static Client BuildFromString(string s);

        // [TBomer] Constants. This holds the location of the Clients.db file
        static const string CLIENT_FILE;

        static vector<Client> clients;

    private:
        string Name;
        string Address;
        int SalesToDate;
        static bool isDBInitialized;


};