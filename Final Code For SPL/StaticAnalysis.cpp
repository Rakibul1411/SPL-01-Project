#include<iostream>
#include<fstream>
#include<cstdio>
#include<cerrno>
#include <filesystem>
#include<string>
#include<dirent.h>
#include"Main_File.h"

using namespace std;

int main() {
    cout << "\nWelcome to 'Static Analysis of Malware'\n";

    while (true)
    {
        cout << "\nDo you want to test a File or a Folder for Malware Detection?" << endl;
        cout << "If so then select an option:\n";
        cout << "  1. A File\n";
        cout << "  2. A Folder\n";
        cout << "  3. Exit\n";

        int userSelection;
        cin >> userSelection;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (userSelection == 1)
        {
            cout << "Enter the File Path: ";
            string fileLocation;
            getline(cin, fileLocation);
            check(fileLocation);
        }

        else if (userSelection == 2)
        {
            cout << "Enter the Folder Path: ";
            string directoryPath;
            getline(cin, directoryPath);

            DIR* directory;
            struct dirent* dirEntry;

            if ((directory = opendir(directoryPath.c_str())) != nullptr)
            {
                while ((dirEntry = readdir(directory)) != nullptr)
                {
                    string entryName = dirEntry->d_name;

                    if (entryName != "." && entryName != "..")
                    {
                        filesystem::path directories(directoryPath);
                        filesystem::path fileName(entryName);
                        filesystem::path fullPath = directories / fileName;

                        cout << "File Path: " << fullPath << endl;
                        cout << "\nTesting ---------------------" << endl;
                        check(fullPath);
                    }
                }

                closedir(directory);
            }

            else
            {
                cout << "Failed to open the Directory." << endl;
                return 1;
            }
        }

        else if (userSelection == 3)
        {
            // Exit the program
            return 0;
        }

        else
        {
            cout << "Invalid option. Please select a valid option." << endl;
        }

    }

}
