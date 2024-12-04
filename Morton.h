#pragma once
#include <iostream>
#include <cstdint> // For uint32_t, uint64_t]
#include<bitset>
#include<string>
#include <bit>
template <int n>
void print_bits(std::string s, std::bitset<n> b) {
    std::cout << s <<" -> " << b << std::endl;
}

template <int n>
void print3(std::bitset<n> b) {
    
    for (size_t i = 0; i < n; i++){
        std::cout << b[n - i - 1];
        if ((n-i-1) % 3 == 0)
            std::cout << " ";
    }
}

template <int n>
void print4(std::bitset<n> b) {

    for (size_t i = 0; i < n; i++) {
        std::cout << b[n - i - 1];
        if ((n - i - 1) % 4 == 0)
            std::cout << " ";
    }
}


class Morton
{
public:
    static double bit[33];
    // Helper function to interleave bits of a 32-bit integer
    static void intitialize() {
        bit[0] = 0.5;
        for (size_t i = 1; i < 32; i++)
            bit[i] = bit[i - 1] / 2;
    }
    // Helper function to interleave bits of a 32-bit integer
    static double convert_to_coordinate(uint32_t num, int n) {
        if (num < 2 || n == 1) return num & 1;  int i = n / 2;
        return 
            convert_to_coordinate(num & ((1 << i) - 1), i) + bit[n-i] * 
            convert_to_coordinate(num >> i, n-i);
    }


    // Helper function to interleave bits of a 32-bit integer
    static uint32_t convert_to_code(double x) {
        uint32_t sum = 0;
        double temp = x, xnew = x;
        
        for (size_t i = 0; xnew > 0 && i<32; i++){
            temp = xnew - bit[i];
            if (temp >= 0) {
                xnew = temp;
                sum += 1 << i;
            }
        }
        return sum;
    }

#define _LSB_(x) (x & 1)
    // Helper function to interleave bits of a 32-bit integer
    static double convert_to_coordinate(uint32_t x, double& resolution) {
        if (bit[0] != 0.5)
            intitialize();

        double sum = 0;
        size_t i = 0;
        for (i = 0; x != 0; i++, x >>= 1)
            if (_LSB_(x) == 1)
                sum += bit[i];

        if (i > 0) resolution = bit[i - 1];
        else resolution = 1;
        return sum;
    }

    // Helper function to interleave bits of a 32-bit integer
    static double convert_to_coordinate(uint32_t x) {
        if (bit[0] != 0.5)
            intitialize();

        double sum = 0;
        for (size_t i = 0; x != 0; i++, x >>= 1)
            if (_LSB_(x) == 1)
                sum += bit[i];

        return sum;
    }


        // Helper function to interleave bits of a 32-bit integer
    static uint32_t interleaveBits(uint32_t xx) {

            uint32_t x = xx;
            x = x             & 0x0000ffff; 
            x = (x | x << 16) & 0xff0000ff; 
            x = (x | x << 8)  & 0x0f00f00f; 
            x = (x | x << 4)  & 0xc30c30c3; 
            x = (x | x << 2)  & 0x49249249; 

            return x;
    }

    // Helper function to deinterleave bits
    static uint32_t deinterleaveBits(uint64_t code) {
        uint64_t x = code;

        x = x               & 0x9249249249249249; 
        x = (x | (x >> 2))  & 0x30c30c30c30c30c3; 
        x = (x | (x >> 4))  & 0xf00f00f00f00f00f; 
        x = (x | (x >> 8))  & 0x00ff0000ff0000ff; 
        x = (x | (x >> 16)) & 0xffff00000000ffff; 
        x = (x | (x >> 32)) & 0x00000000ffffffff; 

        return x;
    }


    // Function to decode a Morton code into (x, y, z) coordinates



    static void decodeMortonCode(uint64_t mortonCode, uint32_t& x, uint32_t& y, uint32_t& z) {
        x = deinterleaveBits(mortonCode >> 2); // Extract x bits
        y = deinterleaveBits(mortonCode >> 1); // Extract y bits
        z = deinterleaveBits(mortonCode);      // Extract z bits
    }

    static void decodeMortonCode(uint64_t mortonCode, double& x, double& y, double& z) {
        uint32_t xx ,yy,zz;      
        decodeMortonCode(mortonCode, xx, yy, zz);// Extract bits
        x = convert_to_coordinate(xx);
        y = convert_to_coordinate(yy);
        z = convert_to_coordinate(zz);
    }

    static void decodeMortonCode(uint64_t mortonCode,
        double& x, double& y, double& z,
        double& dx, double& dy, double& dz) {
        uint32_t xx, yy, zz;
        decodeMortonCode(mortonCode, xx, yy, zz);// Extract bits
        x = convert_to_coordinate(xx, dx);
        y = convert_to_coordinate(yy, dy);
        z = convert_to_coordinate(zz, dz);
    }

    // Function to compute the Morton code for 3D coordinates
    static uint64_t computeMortonCode(uint32_t x, uint32_t y, uint32_t z) {
        uint64_t mortonX = interleaveBits(x);
        uint64_t mortonY = interleaveBits(y);
        uint64_t mortonZ = interleaveBits(z);
        return (mortonX << 2) | (mortonY << 1) | mortonZ; // Combine interleaved bits
    }

    static int example() {
        uint32_t x = 0b1011;  // Example x-coordinate
        uint32_t y = 0b1101;  // Example y-coordinate
        uint32_t z = 0b0011;  // Example z-coordinate

        uint64_t mortonCode = computeMortonCode(x, y, z);

        std::cout << "Morton code for " << std::endl;
        std::cout << "x = "; print4(std::bitset<8>(x)); std::cout << " " << std::endl;
        std::cout << "y = "; print4(std::bitset<8>(y)); std::cout << " " << std::endl;
        std::cout << "z = "; print4(std::bitset<8>(z)); std::cout << " " << std::endl;
        std::cout << "------------------------" << std::endl;
        print3(std::bitset<16>(mortonCode));
        std::cout << "\n-------------------------\n\n\n";

        decodeMortonCode(mortonCode, x, y, z);
        std::cout << "DeMorton code for " << std::endl;
        std::cout << "x = "; print4(std::bitset<8>(x)); std::cout << " " << std::endl;
        std::cout << "y = "; print4(std::bitset<8>(y)); std::cout << " " << std::endl;
        std::cout << "z = "; print4(std::bitset<8>(z)); std::cout << " " << std::endl;
        std::cout << "------------------------" << std::endl;

        print3(std::bitset<16>(mortonCode));

        double resolution = 0;
        std::cout << std::endl << "------------------------" << std::endl;
        for (size_t i = 0; i < 10; i++)
        {
            auto xx = convert_to_coordinate(i, resolution);
            x = convert_to_code(xx);
            std::cout << "x code = " << i << " , ";
            std::cout << "x convert_to_coordinate = " << xx << " , ";
            std::cout << "x resolution = " << resolution << " , ";
            std::cout << "x convert_to_code = " << x << std::endl;
        }
        std::cout << "\n-------------------------\n";
        return 0;
    }

    static void masks1() {
        print_bits("00", std::bitset<32>(0x0000ffff));
        print_bits("16", std::bitset<32>(0xff0000ff));
        print_bits("08", std::bitset<32>(0x0f00f00f));
        print_bits("04", std::bitset<32>(0xc30c30c3));
        print_bits("02", std::bitset<32>(0x49249249));
        std::cout << "\n--------1-----------------\n\n\n";
    }
    static void masks2() {
        print_bits("00", std::bitset<64>(0x9249249249249249));
        print_bits("02", std::bitset<64>(0x30c30c30c30c30c3));
        print_bits("04", std::bitset<64>(0xf00f00f00f00f00f));
        print_bits("08", std::bitset<64>(0x00ff0000ff0000ff));
        print_bits("16", std::bitset<64>(0xffff00000000ffff));
        print_bits("32", std::bitset<64>(0x00000000ffffffff));
        std::cout << "\n--------1-----------------\n\n\n";
    }

};

