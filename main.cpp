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

using namespace std;


int main(int argc, char** argv) {
    Global::SetCurrentDirectory(argv);
    cout << endl << endl; // Adding some buffer to end out program output.
}