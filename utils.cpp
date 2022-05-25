

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
    bool debug = false;
    int getTime()
    {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t;
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }


    int getInt(const char* prompt)
    {
        char numLine;
        int record, state;

        if (prompt != nullptr)
        {

            cout << prompt;
        }

        cin >> record;
        cin.get(numLine);

        do
        {
            state = 0;
            if (cin.fail())
            {

                state++;

                cout << "Bad integer value, ";
                cout << "try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> record;
                cin.get(numLine);
            }
        } while (state > 0);

        do
        {
            state = 0;

            if (numLine != '\n')
            {

                state++;
                cout << "Enter only an integer, ";
                cout << "try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> record;
                cin.get(numLine);

            }
        } while (state > 0);
        return record;
    }
   
    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
    {

        int state;
        int record;
     
        if (prompt != nullptr)
        {
            
            cout << prompt;
        }
        do
        {

            state = 0;
            record = getInt();
            
            if ((record > max || record < min) && (errorMessage != nullptr))
            {

                cout << errorMessage;
                if (showRangeAtError == true)
                {
               
                    cout << "[";
                    cout << min;
                    cout << " <= value <= ";
                    cout << max;
                    cout << "]: ";
                }
                state++;

            }
        } while (state != 0);
        return record;
    }

    char* getcstr(const char* prompt, std::istream& istr, char delimiter)
    {

        char firstString[9999];
        char* secondString;

        if (prompt != nullptr)
        {

            cout << prompt;
        }

        istr.getline(firstString, 9999, delimiter);
        secondString = new char[strlen(firstString) + 1];
        strcpy(secondString, firstString);

        return secondString;
    }
}