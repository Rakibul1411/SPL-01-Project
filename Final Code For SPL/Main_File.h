#include<iostream>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <vector>
#include"Delete_Malicious_File.h"
#include "MD5_Hashing_Algorithm.h"
#include"Trie_DataStructure.h"
#include"PE_Header_Parsing.h"
#include"Encode_Malicious_File.h"
#include"Decode_Malicious_File.h"
typedef unsigned long DWORD;
using namespace std;


int check(string s)
{
    char keys[10000][35];

    int track;
    int count = 0;
    struct TrieNode *root = getNode();
    //int i;
    const char* fileName = s.c_str();

    ifstream file(s, ios::binary);

    if(!file)
    {
        cerr << "Cannot open file: "<< s << endl;
        return -1;
    }

    if (file){

        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);


        string fileContent(fileSize, 0);
        file.read(&fileContent[0], fileSize);


        string md5 = MD5(fileContent);
        cout << "MD-5 Hash Value is: " << md5 << std::endl;
        const char *key=md5.c_str();



        FILE *fp = fopen("Predefined_Malicious_Hashset.txt", "r");
        if (fp == NULL)
        {
            printf("Error opening PreDefined Malicious Hashset File\n");
            return 1;
        }

        while (fscanf(fp, "%s", keys[count]) != EOF)
        {
            count++;
        }

        fclose(fp);


        struct TrieNode *root = getNode();
        loadHashes("Predefined_Malicious_Hashset.txt", root);


        //int i;
        for (int i = 0; i < count; i++)
        {
            insert(root, keys[i]);
        }


        if (search(root, key ))
        {
            cout << "This File is Detected as Malware by PreDefined Hash Value Matching..!!!" << endl<<endl;
            track=-1;
            file.close();
        }


        else
        {
            cout << "This File is not Detect as Malware by PreDefined Hash Value Matching. Lets recheck by Analysing of PE Header File." << endl<<endl;


            unsigned short  majorImageVersion;
            unsigned long  checksum;
            unsigned short dllCharacteristics;
            unsigned long initializedData;


            ifstream file(fileName,ios::binary);
            FILE *PpeFile;
            PpeFile = fopen(fileName, "rb");

            if (PpeFile == NULL)
            {
                printf("Can't open File.\n");
                return 1;
            }

            unsigned long signature=ParseDOSHeader(fileName, PpeFile);

            if(signature==0x5A4D)
            {
                ParseNTHeaders(fileName, PpeFile, &initializedData, &checksum, &dllCharacteristics, &majorImageVersion);

               /* cout<<"Basic Info"<<endl;
                cout<<"--------------"<<endl;
                cout<<"Initialized data:   "<<initializedData<<endl;
                printf("checksum:   0x%lX\n", checksum);
                printf("DLL characteristics:   0x%X\n", dllCharacteristics);
                printf("major image version:   0x%X\n", majorImageVersion);
                */


                int noOfSection=ParseSectionHeaders(fileName, file);

                fclose(PpeFile);

                stringstream ss;

                ss << hex << checksum;
                ss >> checksum;
                ss << hex << dllCharacteristics;
                ss >> dllCharacteristics;
                ss << hex << majorImageVersion;
                ss >> majorImageVersion;




                char sections[noOfSection][8];
                for(int i=0; i<noOfSection; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        sections[i][j] = SectionName[i][j];
                    }
                }

                //int i,j,k,l;

                int numNames = sizeof(sections) / sizeof(sections[0]);
                int numName = sizeof(known_section_names) / sizeof(known_section_names[0]);

                bool allPresent = true;

                for (int i = 0; i < numNames; ++i)
                {
                    bool found = false;
                    for (int j = 0; j < numName; ++j)
                    {
                        if (std::strcmp(sections[i], known_section_names[j]) == 0)
                        {
                            found = true;

                            break;
                        }
                    }

                    if (!found)
                    {
                        allPresent = false;

                        break;
                    }

                }


                if(initializedData==0)
                {
                    cout<<"THIS FILE IS 'MALWARE'!!"<<endl<<endl;
                    track=-1;

                }
                else if(!allPresent)
                {
                    cout<<"THIS FILE IS 'MALWARE'!!"<<endl<<endl;
                    track=-1;

                }

                else if((int)dllCharacteristics == 0 && (int)majorImageVersion == 0 && (int)checksum == 0)
                {
                    cout<<"THIS FILE IS 'MALWARE'"<<endl<<endl;
                    track=-1;

                }

                else
                {
                    cout<<"THIS FILE IS 'NOT MALWARE'"<<endl<<endl;
                    track=0;

                }
            }

            else
            {
                cout<<endl<<"it is not PE file"<<endl<<endl;
                return 0;

            }


        }

        file.close();


        if(track==-1)
        {

            cout<<"\nDo you want to Delete/Isolate the file or want to exit the program?"<<endl;
            cout<<"Select an option please-"<<endl;
            cout<<"  1.Delete"<<endl;
            cout<<"  2.Isolate"<<endl;
            cout<<"  3.Exit"<<endl;

            int i;
            cin>>i;
            const char* filePath=fileName;

            if(i==1)
            {

                deleteMaliciousFile(filePath);

            }


            else if(i==3)
            {
                return 0;
            }

            else if(i==2)
            {

                encodeMaliciousFile(filePath);

                int a;
                cout<<"Do you have (Decode) the file again?"<<endl<<"Press 1 to Decode the File"<<endl;
                cout<<"press 0 to exit"<<endl;
                cin>>a;

                if(a==1)
                {
                    decodeMaliciousFile(filePath);
                }

                if(a==0)
                {
                    return 0;
                }

            }

        }
    }


    else
    {
        cout << " Can't find the file " << endl;
    }











}
