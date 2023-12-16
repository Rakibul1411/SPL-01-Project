cmake_minimum_required(VERSION 3.26)
project(Final_Code_For_SPL)

set(CMAKE_CXX_STANDARD 17)

add_executable(Final_Code_For_SPL StaticAnalysis.cpp
        Delete_Malicious_File.h
        Encode_Malicious_File.h
        Decode_Malicious_File.h
        MD5_Hashing_Algorithm.h
        Main_File.h
        PE_Header_Parsing.h
        Trie_DataStructure.h
)
