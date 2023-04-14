#include "Test.h"
#include "Global.h"
#include "Client.h"
#include "SalesRep.h"
#include "Product.h"
#include "Sale.h"

bool Test::populateClients = true;
bool Test::populateProducts = true;
bool Test::populateSales = true;
bool Test::populateSalesReps = true;

void Test::PopulateDatabases() {
    if (populateClients) {
        string tempGlobal = Global::CURRENT_DIR;
        string DatabaseDirectory = tempGlobal.append("\Database");
        string dbTemp = DatabaseDirectory;
        string Database = dbTemp.append("\\").append(Client::CLIENT_FILE);
        if (!Global::file_exists(Database)) {
            Client::InitializeDatabase();
            Client::QuickAdd("Ada Collier", "9714 State St., Dickson, TN 37055", 113, "1234567890", "acollier@arboreight.com");
            Client::QuickAdd("Katrina Thornton", "7532 Gregory Lane, Oshkosh, WI 54901", 158, "1234567890", "kthornton@arboreight.com");
            Client::QuickAdd("Robin Ferguson", "6 Wagon Rd., San Antonio, TX 78213", 13, "1234567890", "rferguson@arboreight.com");
            Client::QuickAdd("Ismael Morrison", "3 Dunbar St., Cocoa, FL 32927", 49, "1234567890", "imorrison@arboreight.com");
            Client::QuickAdd("Herman Gordon", "8 Lantern Drive, Omaha, NE 68107", 186, "1234567890", "hgordon@arboreight.com");
            Client::QuickAdd("Ollie Dean", "21 Carpenter Drive, Redford, MI 48239", 175, "1234567890", "hgordon@arboreight.com");
            Client::QuickAdd("Johnny Rios", "7713 Garden St., Hephzibah, GA 30815", 133, "1234567890", "jrios@arboreight.com");
            Client::QuickAdd("Jesse Howard", "406 Bellevue Road, Los Angeles, CA 90008", 132, "1234567890", "jhoward@arboreight.com");
            Client::QuickAdd("Rosemarie Hubbard", "8839 North Mammoth Ave., Fitchburg, MA 01420", 89, "1234567890", "rhubbard@arboreight.com");
            Client::QuickAdd("Marjorie Marsh", "534 Jefferson Road, Derry, NH 03038", 49, "1234567890", "mmarsh@arboreight.com");
        }
    }

    if (populateProducts) {
        string tempGlobal = Global::CURRENT_DIR;
        string DatabaseDirectory = tempGlobal.append("\Database");
        string dbTemp = DatabaseDirectory;
        string Database = dbTemp.append("\\").append(Product::PRODUCT_FILE);
        if (!Global::file_exists(Database)) {
            Product::InitializeDatabase();
            Product::QuickAdd("Hammer Set", "Comes with a hammer and nails.", 14.99, 38);
            Product::QuickAdd("Wrench Set", "16-Pack of wrenches.", 22.99, 41);
            Product::QuickAdd("Screwdriver Set", "24-Pack of screwdrivers.", 18.99, 66);
            Product::QuickAdd("Drill Package", "1 Drill and 10 drill bits.", 64.99, 24);
        }
    }

    if (populateSales) {
        string tempGlobal = Global::CURRENT_DIR;
        string DatabaseDirectory = tempGlobal.append("\Database");
        string dbTemp = DatabaseDirectory;
        string Database = dbTemp.append("\\").append(Sale::SALES_FILE);
        if (!Global::file_exists(Database)) {
            Sale::InitializeDatabase();

            Sale::QuickAdd("2023/04/13", "Ada Collier", "Carroll Gardner", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2022/04/13", "Katrina Thornton", "Frances Reid", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2023/04/13", "Robin Ferguson", "Bernadette Hill", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2021/04/13", "Ismael Morrison", "Bobbie Bryant", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2023/04/13", "Herman Gordon", "Elvira Sandoval", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2022/04/13", "Ollie Dean", "Otis Lowe", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2021/04/13", "Johnny Rios", "Faith Moss", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2023/04/13", "Jesse Howard", "Terry Barber", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2022/04/13", "Rosemarie Hubbard", "Rex Norris", "Hammer Set", 1, 14.99);
            Sale::QuickAdd("2022/04/13", "Marjorie Marsh", "Forrest Hammond", "Hammer Set", 1, 14.99);

        }
    }

    if (populateSalesReps) {
        string tempGlobal = Global::CURRENT_DIR;
        string DatabaseDirectory = tempGlobal.append("\Database");
        string dbTemp = DatabaseDirectory;
        string Database = dbTemp.append("\\").append(SalesRep::SALESREP_FILE);
        if (!Global::file_exists(Database)) {
            SalesRep::InitializeDatabase();
            SalesRep::QuickAdd("Self Service", "APPLICATION", "N/A", "support@arboreight.com", 0);
            SalesRep::QuickAdd("Carroll Gardner", "68 Rosewood St., Morristown, NJ 07960", "1234567890", "cgardner@arboreight.com", 100);
            SalesRep::QuickAdd("Frances Reid", "90 Hill Street, Somerset, NJ 08873", "1234567890", "freid@arboreight.com", 84);
            SalesRep::QuickAdd("Bernadette Hill", "672 North Bellevue St., Pleasanton, CA 94566", "1234567890", "bhill@arboreight.com", 171);
            SalesRep::QuickAdd("Bobbie Bryant", "39 Talbot Rd., Wyandotte, MI 48192", "1234567890", "bbryant@arboreight.com", 46);
            SalesRep::QuickAdd("Elvira Sandoval", "78 Illinois St., Louisville, KY 40207", "1234567890", "esandoval@arboreight.com", 3);
            SalesRep::QuickAdd("Otis Lowe", "91 Rockland St., Oak Park, MI 48237", "1234567890", "olowe@arboreight.com", 156);
            SalesRep::QuickAdd("Faith Moss", "8079 Indian Spring St., Waterbury, CT 06705", "1234567890", "fmoss@arboreight.com", 162);
            SalesRep::QuickAdd("Terry Barber", "9928 Carson Street, Thibodaux, LA 70301", "1234567890", "tbarber@arboreight.com", 180);
            SalesRep::QuickAdd("Rex Norris", "33 Greenrose Street, Beachwood, OH 44122", "1234567890", "rmorris@arboreight.com", 68);
            SalesRep::QuickAdd("Forrest Hammond", "87 Race Lane, El Paso, TX 79930", "1234567890", "fhammond@arboreight.com", 165);
        }
    }
}