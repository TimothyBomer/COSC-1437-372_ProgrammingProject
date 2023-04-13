/*  -----------------------------------------------------------------
    Class:
        Name:           Globals
        Definition:     Globals.cpp
        Header:         Globals.h

    Description:    Class to house global functions.
    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
------------------------------------------------------------------- */
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#pragma once
class Global {
    public:
        static string CURRENT_DIR;

        static inline bool file_exists(const string& name) {
            struct stat buffer;
            return (stat(name.c_str(), &buffer) == 0);
        }

        static void SetCurrentDirectory(char** argv) {
            string directory = argv[0];
            directory.erase(directory.find_last_of('\\') + 1);

            unsigned int start_position_to_erase = directory.find("Debug");
            directory.erase(start_position_to_erase, 6);

            Global::CURRENT_DIR = directory.append("ProgrammingProject\\");
        }

        static bool IsStringNumber(const std::string& s) {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && std::isdigit(*it)) ++it;
            return !s.empty() && it == s.end();
        }
        
};

