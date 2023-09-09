/*
 * Simple MD5 implementation in C++
 * 
 * md5.cpp
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "functions.h"
#include <cmath>

// Auxiliary functions definitions (that each take as input three
// 32-bit words and produce as output one 32-bit word):
#define roundF(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define roundG(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define roundH(x, y, z) ((x) ^ (y) ^ (z))
#define roundI(x, y, z) ((y) ^ ((x) | (~z)))

// LeftRotate function definition:
#define leftRotate(x, n) (((x) << (n)) | ((x) >> (32-(n))))

using namespace std;

int main() {
    int n;
    string message;
    string bits_message;

    unsigned k[64];

    // "s" specifies the per-round shift amounts:
    unsigned s[64] = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
            5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    // Use binary integer part of the sines of integers (Radians) as constants:
    for (int i = 0; i < 64; i++)
    {
        k[i] = floor(pow(2, 32) * abs(sin(i + 1))); // floor function is opposite of ceil function
    }

    // Initialize variables:
    unsigned h0 = 0x67452301; //A
    unsigned h1 = 0xefcdab89; //B
    unsigned h2 = 0x98badcfe; //C
    unsigned h3 = 0x10325476; //D

    // Get the message:
    cout<<"MD5 Algorithm" << endl << endl;
    cout << "Enter a message: ";
    getline(cin, message);  //getline is a standard library function that is used to read a line of text from an input stream

    // String conversion to binary:
    bits_message = stringToBinary(message);

    // Pre-processing: adding a single 1 bit & padding with zeros
    bits_message = appendTo512Bits(bits_message);

    // Process the message in successive 512-bit chunks:
    n = (int)bits_message.length() / 32;

    for (int i = 0; i <= (n / 16) - 1; i++) {

        // Little endian:
        string m[16];
        for (int j = 0; j < 16; j++) {
            m[j] = littleEndian32Bits(bits_message.substr(j * 32, 32));
        }

        // Initialize hash value for this chunk:
        unsigned a = h0;
        unsigned b = h1;
        unsigned c = h2;
        unsigned d = h3;

        unsigned f = 0;
        int g = 0;

        // Main loop:
        for (int i = 0; i < 64; i++) {
            if (i >= 0 && i < 16) {
                f = roundF(b, c, d);
                g = i;
            } else if (i >= 16 && i < 32) {
                f = roundG(b, c, d);
                g = (5 * i + 1) % 16;
            } else if (i >= 32 && i < 48) {
                f = roundH(b, c, d);
                g = (3 * i + 5) % 16;
            } else if (i >= 48 && i < 64) {
                f = roundI(b, c, d);
                g = (7 * i) % 16;
            }

            f = f + a + k[i] + binaryStringToDecimal(m[g]);
            a = d;
            d = c;
            c = b;
            b = b + leftRotate(f, s[i]);
        }

        // Add this chunk's hash to result so far:
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
    }

    // Output (in little-endian):
    string hArray[4] = {
            littleEndian32Bits(numberToBinary(h0, 32)),
            littleEndian32Bits(numberToBinary(h1, 32)),
            littleEndian32Bits(numberToBinary(h2, 32)),
            littleEndian32Bits(numberToBinary(h3, 32))
    };

    // Binary to hex:
    cout << "The MD5 digest for your message is: ";

    for (int h = 0; h < 4; h++) {
        string bin(hArray[h]);
        int result = 0;

        for (size_t count = 0; count < bin.length(); ++count) {
            result *= 2;
            result += bin[count] == '1' ? 1 : 0;
        }

        cout << hex << setw(8) << setfill('0') << result;
    }

    cout << endl << endl;

    return 0;
}