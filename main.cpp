#define _CRT_SECURE_NO_WARNINGS

// C++ libraries code block
#include <fstream>
#include <iostream>
#include <cstring>
#include "MyDynamicArray.hpp"
#include "DynamicArray.hpp"

using namespace std;

const int MAX_CHARS_PER_LINE = 1000;
//const int MAX_TOKENS_PER_LINE = 50;
const char *const DELIMITER = "";
const char *const tab = "\t";

struct info {
    string sectionKeep = " ";
    int sectionCounter = 0;

}; // structure to store section title and the amount

struct sections {

    string termYear = " ";
    int numberSeen = 0;
    DynamicArray<string> seenSectionNumber;

};

int main() {

    /*
     * Variable Declaration START
     */

    //MyDynamicArray<string> firstRun;
    MyDynamicArray<info> finalRun;
    MyDynamicArray<sections> testings;

    double displayCounter = 0.0;
    int duplicateCounter = 0;
    int enterCounter = 0;
    int admitCounter = 0;

    char buf[MAX_CHARS_PER_LINE];
    char *token;


    ifstream dvcFile;

    /*
     * Variable Declaration END
     */

    dvcFile.open("dvc-schedule.txt");


    if (dvcFile.is_open()) {

        //Variables
        string line = " ";

        while (dvcFile.good()) {

            bool enterBool = true;

            displayCounter++;
            cout << (displayCounter / 76668) * 100 << "% \r"; // prints percentage.
            cout.flush();


            getline(dvcFile, line);
            strcpy(buf, line.c_str());

            if (buf[0] == 0) { continue; } // if


            const string term(token = strtok(buf, tab));
            const string section((token = strtok(nullptr, tab)));
            const string course((token = strtok(nullptr, tab)) ? token : "");
            const string instructor((token = strtok(nullptr, tab)) ? token : "");
            const string whenWhere((token = strtok(nullptr, tab)) ? token : "");


            if (course.find('-') == string::npos) { continue; }

            const string subjectCode(course.begin(), course.begin() + course.find('-')); // tracking this


            string key = " ";

            key += term;
            key += " ,";
            key += section;

            bool duplicate = false;

            /*
             * selfNote ->
             * enterCounter tracks the amount of term sections.
             * The first For-Loop goes through the amount of entered terms.
             */

            // checks if the object already has a term at 'i' equaling to the current term.
            // Performance -> it won't go through 70k to check for that term, only MAX 50

            for (int i = 0; i < enterCounter; ++i) {

                if (testings[i].termYear == term) { // if term exists then ->

                    for (int j = 0; j < testings[i].numberSeen; ++j) { // look through for matching section

                        if (testings[i].seenSectionNumber[j] == section) { // if found then count duplicate

                            duplicate = true; // later used to enter increase the counter & enter the term !Duplicate.
                            break;

                        }// if

                    }// for

                    if (!duplicate) // if no duplicate add section and add to counter & skip adding term again.
                    {
                        testings[i].numberSeen++;
                        testings[i].seenSectionNumber[testings[i].numberSeen] = section;
                        enterBool = false;

                    } // if

                } // if

            } // for

            if (duplicate) {

                duplicateCounter++; // this will increase the counter and skip adding that value.

            }// if
            else {

                bool tempCheck = false;

                if (enterBool) { // only runs if this term has no sections.

                    testings[enterCounter].termYear = term; // adding the new term

                    testings[enterCounter].numberSeen++; // adding 1 to "how many sections"

                    testings[enterCounter].seenSectionNumber[testings[enterCounter].numberSeen] = section; // adding the first section

                    enterCounter++; // counter for testings

                }
/*
                for (int j = 0; j < enterCounter ; ++j) {

                    cout << "Run #" << j << "\t" << enterCounter << "\t" << testings[j].termYear << "\t" << testings[j].numberSeen << "\r" << endl;

                }
*/
                //firstRun[enterCounter] = key; // this stores the term and section only to check for duplicates.


                for (int i = 0; i < admitCounter; ++i) {
                    if (finalRun[i].sectionKeep == subjectCode) // checks for an already existing subject
                    {
                        finalRun[i].sectionCounter++; // increment the amount of subjects.
                        tempCheck = true; // setting true skips the enxt if statement
                        break; // when found breaks out of the loop.

                    } // if
                }//for

                if (!tempCheck) {

                    finalRun[admitCounter].sectionKeep = subjectCode;

                    finalRun[admitCounter].sectionCounter = 1;

                    admitCounter++;

                }// if

            }// else

        }// while

    }// if ~ dvcFile.is_open()  ~

    else {

        cout << "\nError Opening file." << endl;

    }// else

    dvcFile.close(); // close file.

    for (int k = 0; k < admitCounter; ++k) {

        for (int i = 0; i < admitCounter; ++i) {

            if (finalRun[k].sectionKeep < finalRun[i].sectionKeep) {

                swap(finalRun[k], finalRun[i]);

            } // if
        }//for
    }//for


    cout << "\nNumber of Duplicates : " << duplicateCounter << endl;
    cout << "Term\tAmount\tSection\n";


    for (int j = 0; j < admitCounter; ++j) {
        if (finalRun[j].sectionKeep == "" || finalRun[j].sectionCounter == 0) { continue; } // if
        cout << "\t" << finalRun[j].sectionKeep << "\t" << finalRun[j].sectionCounter << "\t" << "Sections" << "\n";

    } // for

    cout << admitCounter << " <- admitcounter" << endl;


} // main
