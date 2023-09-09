
#include "functions.h"
#include <bitset>
#include <iostream>
#include "math.h"

using namespace std;

string stringToBinary(string msg)
{
    string binary;

    for (size_t i = 0; i < msg.size(); ++i) {
        binary += bitset<8>(msg.c_str()[i]).to_string();
    }

    return binary;
}

string appendTo512Bits(string msg)
{
    string result = msg;
    int string_size = (int)msg.length();

    // Pre-processing: adding a single 1 bit
    result += '1';

    int fullSize;

    // "0" bits are appended, so that the length in bits of the padded message
    // becomes congruent to 448, modulo 512
    if ((string_size % 512) < 448) {
        fullSize = 512 * (string_size / 512) + 448 - string_size - 1;
    }
    else {
        fullSize = 512 * (string_size / 512) + 511 - string_size + 448;
    }

    // Pre-processing: padding with zeros to 448 bits, modulo 512
    for (int i = 0; i < fullSize; i++) {
        result += '0';
    }

    // Pre-processing: append length to 64 bits
    string string_size_binary = numberToBinary(string_size, -1);

    string result_lenght;

    for (int i = 0; i < (64 - string_size_binary.size()); i++) {
        result_lenght += '0';
    }

    result_lenght += string_size_binary;
    result_lenght = littleEndian64Bits(result_lenght);

    return result + result_lenght;
}


string numberToBinary(unsigned number, int size){
    string binary;
    while (number != 0) {
        binary = (number % 2 == 0 ? "0" : "1") + binary;
        number /= 2;
    }

    //can't understand
    if (size > -1) {
        if (size > binary.length()) {
            string temp;
            for (int i = (int)binary.length(); i < size; i++) {
                temp += '0';
            }
            binary = temp + binary;
        }
    }

    return binary;
}

//string reverse(string to_reverse){
//    string result;
//    for (int i = (int)to_reverse.length() - 1; i >= 0; i--)
//        result += to_reverse[i];
//    return result;
//}

string littleEndian32Bits(string str)
{
    string b1, b2, b3, b4;

    for (int i=0; i<32; i++) {
        if ((i >= 0) & (i < 8))
            b1 += str[i];
        if ((i >= 8) & (i < 16))
            b2 += str[i];
        if ((i >= 16) & (i < 24))
            b3 += str[i];
        if ((i >= 24) & (i < 32))
            b4 += str[i];
    }

    return b4 + b3 + b2 + b1;
}

string littleEndian64Bits(string str)
{
    string b1, b2, b3, b4, b5, b6, b7, b8;

    for (int i = 0; i < 64; i++) {
        if ((i >= 0) & (i < 8))
            b1 += str[i];
        if ((i >= 8) & (i < 16))
            b2 += str[i];
        if ((i >= 16) & (i < 24))
            b3 += str[i];
        if ((i >= 24) & (i < 32))
            b4 += str[i];
        if ((i >= 32) & (i < 40))
            b5 += str[i];
        if ((i >= 40) & (i < 48))
            b6 += str[i];
        if ((i >= 48) & (i < 56))
            b7 += str[i];
        if ((i >= 56) & (i < 64))
            b8 += str[i];
    }

    return b8 + b7 + b6 + b5 + b4 + b3 + b2 + b1;
}

unsigned binaryStringToDecimal(string a)
{
    unsigned num = 0;
    bool neg = false;

    if (a.at(0) == '1') {
        neg = true;
        for (int x = (int)a.length() - 1; x >= 0; x--) {
            if (a.at(x) == '1')
                a.at(x) = '0';
            else
                a.at(x) = '1';
        }

        a.at(a.length() - 1) += 1;
        for (int x = (int)a.length() - 1; x >= 0; x--) {
            if (a.at(x) == '2') {
                if (x-1 >= 0) {
                    if (a.at(x - 1) == '1')
                        a.at(x - 1) = '2';
                    if (a.at(x - 1) == '0')
                        a.at(x - 1) = '1';
                    a.at(x) = '0';
                }
            } else if (a.at(x) == '3') {
                if (x - 1 >= 0)
                    a.at(x-1) += '2';
                a.at(x) = '1';
            }
        }

        if (a.at(0) == '2')
            a.at(0) = '0';
        else if (a.at(0) == '3')
            a.at(0) = '1';
    }

    for (int x = (int)a.length() - 1; x >= 0; x--) {
        if (a.at(x) == '1')
            num += pow(2.0, a.length() - x - 1);
    }

    if (neg)
        num = num *- 1;

    return num;
}
