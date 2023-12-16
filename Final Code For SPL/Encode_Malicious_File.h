#include<iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void encodeMaliciousFile(const char* filePath)
{
    ifstream file(filePath, ios::binary);

    if (!file.is_open())
    {
        cout << "Failed to Open File!" << endl;
        return;
    }


    vector<char> fileData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();


    for (char& byte : fileData)
    {
        byte = byte << 1;
    }

    ofstream outFile(filePath, ios::binary);


    outFile.write(fileData.data(), fileData.size());

    outFile.close();

    cout << "File Encoding Complete." << endl;
}




























/*#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void decodeFile(const char* filePath) {
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    char ch;
    while (file.read(&ch, sizeof(ch))) {
        ch = ch << 1; // Perform left shift by one bit

        // Move the file pointer back by one byte to overwrite the original byte
        file.seekp(-sizeof(ch), std::ios::cur);
        file.write(&ch, sizeof(ch));
        file.seekg(0, std::ios::cur); // Move the file pointer back to the next byte
    }

    file.close();
    std::cout << "file Decoding complete." << std::endl;
}*/
