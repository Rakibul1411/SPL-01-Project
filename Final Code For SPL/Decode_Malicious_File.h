#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void decodeMaliciousFile(const char* filePath)
{

    ifstream inputFile(filePath, ios::binary);


    if (!inputFile.is_open())
    {
        cout << "Failed to open file!" << endl;
        return;
    }

    vector<char> fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    inputFile.close();

    for (char& byte : fileData)
    {
        byte = byte >> 1;
    }


    ofstream outputFile(filePath, ios::binary);

    outputFile.write(fileData.data(), fileData.size());

    outputFile.close();

    cout << "File Decoding Complete." << endl;
}



























