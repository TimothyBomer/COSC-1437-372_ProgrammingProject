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
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include <windows.h>
#include "Global.h";
using namespace std;

#pragma once
class Product {
    public:
        // [TBomer] Constants. This holds the location of the Products.db file
        static const string PRODUCT_FILE;
        static string PRODUCT_DATABASE_PATH;

        // [TBomer] Constructors
        Product();

        // Getters and Setters
        void SetName(string n);
        void SetDescription(string d);
        void SetPrice(double p);
        void SetStock(int s);
        string GetName();
        string GetDescription();
        double GetPrice();
        int GetStock();

        // [TBomer] Mutators
        bool AddProduct();
        void SaveProductUpdates();

        // [TBomer] Static Functions
        static void InitializeDatabase();
        static void LoadProducts();
        static void PrintProductList();
        static void PrintSingleProduct(string pName);
        static Product LoadSingleProduct(string pName);
        static Product BuildFromString(string s);
        static bool QuickAdd(string n, string d, double p, int s);

        static vector<Product> Products; // [TBomer] This holds the list of Products. Populated by the LoadProducts() function call.

    private:
        string Name;
        string Description;
        double Price;
        int Stock;
        static bool isDBInitialized;

        // [TBomer] When loading a Product by name, the dbString property holds the content of the database line for the Product.
        //              This is used for updating the Product information.
        string dbString;
        void SetDBString(string s);
        string GetDBString();
};