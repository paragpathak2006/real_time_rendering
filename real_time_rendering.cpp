// real_time_rendering.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Morton.h"
#include <cmath>
#include <bitset>
int main()
{
    Morton::intitialize();
    auto x = std::bitset<32>("00000000000000000000000000000101");
    auto y = std::bitset<32>("00000000000000000000000000000011");
    auto z = std::bitset<32>("00000000000000000000000000000111");
    float t = 0.8;

    auto xx = x.to_ulong();
    auto yy = y.to_ulong();
    auto zz = z.to_ulong();

//    std::cout << xx << std::endl;
//    std::cout << yy << std::endl;
//    std::cout << zz << std::endl;
//    std::cout << std::bitset<64>(Morton::computeMortonCode(xx, yy, zz)) << std::endl;
//    std::cout << "Hello World!\n";
     Morton::example();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
