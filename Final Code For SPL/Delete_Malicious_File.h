#include<iostream>
#include <iostream>
#include <cstdio>
using namespace std;

void deleteMaliciousFile(const char* filePath)
{


    if (remove(filePath) != 0)
    {
        perror("Failed to delete the file");
    }

    else
    {
        cout << "File deleted successfully." << endl;
    }

    //return 0;
}

