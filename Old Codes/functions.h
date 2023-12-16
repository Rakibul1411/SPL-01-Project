/*
 * Simple MD5 implementation in C++
 *
 * functions.hpp
 */

#ifndef functions_h
#define functions_h

#include <cstdio>
#include <string>

using namespace std;

string stringToBinary(string);
string numberToBinary(unsigned, int);
unsigned binaryStringToDecimal(string);
string appendTo512Bits(string);
string reverse(string);
string littleEndian64Bits(string);
string littleEndian32Bits(string);

#endif