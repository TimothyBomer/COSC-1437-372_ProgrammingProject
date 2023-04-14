/*  -----------------------------------------------------------------
    Class:
        Name:           Globals
        Definition:     Globals.cpp
        Header:         Globals.h

    Description:    Class to house global functions that can be
                        re-used anywhere.

    Author:         TBomer, JKantara, ALogan
    Date:           03/26/2023

    Revision History:
        Name:           Date:           Description:
        TBomer          03/26/2023      Initial creation.
        TBomer          04/12/2023      Added IsStringNumber()
                                        Added EraseLineFromFile()
        TBomer          04/13/2023      Allowed the usage of doubles
                                            in IsStringNumber()
------------------------------------------------------------------- */
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

#pragma once
class Global {
    public:
        // [TBomer] Used to set the current directory. Useful for locating Database files.
        static string CURRENT_DIR;
        static void SetCurrentDirectory(char** argv) {
            string directory = argv[0];
            directory.erase(directory.find_last_of('\\') + 1);
            unsigned int start_position_to_erase = directory.find("Debug");
            directory.erase(start_position_to_erase, 6);
            Global::CURRENT_DIR = directory.append("ProgrammingProject\\");
        }

        // [TBomer] Checks to see if a file exists.
        static inline bool file_exists(const string& name) {
            struct stat buffer;
            return (stat(name.c_str(), &buffer) == 0);
        }

        // [TBomer] Checks to see if a string can be cast to a number.
        //              useful for error handling.
        static bool IsStringNumber(const std::string& s) {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && (std::isdigit(*it) || *it == '.')) ++it;
            return !s.empty() && it == s.end();
        }

        // [TBomer] Deletes a specific line from a file.
        static void EraseLineFromFile(string path, string eraseLine) {
            string line;
            ifstream fin(path);
            ofstream temp("temp.txt");

            while (getline(fin, line)) {
                if (line != eraseLine) {
                    temp << line << endl;
                }   
            }

            temp.close();
            fin.close();

            const char* p = path.c_str();
            remove(p);
            rename("temp.txt", p);
        }

        static inline tm localtime_xp(time_t timer) {
            tm bt{};
            #if defined(__unix__)
                localtime_r(&timer, &bt);
            #elif defined(_MSC_VER)
                localtime_s(&bt, &timer);
            #else
                static mutex mtx;
                lock_guard<mutex> lock(mtx);
                bt = *localtime(&timer);
            #endif
            return bt;
        }

        // default = "YYYY-MM-DD HH:MM:SS"
        static inline string GetFormattedDate(const string& fmt = "%Y/%m/%d") {
            auto bt = localtime_xp(time(0));
            char buf[64];
            return { buf, strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
        }
        
};

