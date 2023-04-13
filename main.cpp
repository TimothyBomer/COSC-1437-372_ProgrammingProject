/*  -----------------------------------------------------------------
    Class:
        Name:           Main
        Definition:     main.cpp
        Header:         N/A

    Description:    Acts as the launcher and QA tester.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
------------------------------------------------------------------- */


#include <iostream>
#include <string>
#include <fstream>


#include "Client.h"

using namespace std;


int main(int argc, char** argv) {
    Global::SetCurrentDirectory(argv);


    Client::InitializeDatabase();

    /*Client c1 = Client();
    c1.SetName("Felix Crystal");
    c1.SetAddress("1234 MyStreet Dr, Test City, TX, 12345");
    c1.SetSalesToDate(81);
    c1.AddClient();*/


    /*Client::LoadClients();
    Client c = Client::LoadSingleClient("Felix Crystal");
    cout << c.GetAddress();

    c.SetSalesToDate(82);
    c.SaveClientUpdates();*/


    cout << endl << endl; // Adding some buffer to end out program output.
}