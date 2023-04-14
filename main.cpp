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
#include "SalesRep.h"
#include "Product.h"
#include "Sale.h"
#include "Test.h"

using namespace std;

void PrintMainMenu() {
    cout << "===== Arbor Eight | Main Menu =====" << endl << endl;
    cout << "1) Manage Clients" << endl;
    cout << "2) Manage Sales Representatives" << endl;
    cout << "3) Manage Products" << endl;
    cout << "4) Manage Sales" << endl;





    
    //cout << left << setw(21) << "Name";
}

int main(int argc, char** argv) {
    Global::SetCurrentDirectory(argv);

    /*
        [TBomer]
            Test::PopulateDatabases() can be used to populate test data into the DBs.
            If the DB files exist, nothing will happen. If they do not exist,
            they will be created and popualted with data.

            You can disable individual databases by setting the property BEFORE
            the PopulateDatabases call. They are all enabled by default.

            Disable Client DB Population:       Test::populateClients = false;
            Disable Product DB Population:      Test::populateProducts = false;
            Disable Sales Rep DB Population:    Test::populateSalesReps = false;
            Disable Sales DB Population:        Test::populateSales = false;

    */

    PrintMainMenu();

    


    // Adding extra padding at bottom
    cout << endl << endl << endl << endl << endl << endl;
}