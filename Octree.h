#pragma once
#include <vector>
#include<bitset>
#include <cstdint> // For uint32_t, uint64_t]
#include "Morton.h"
#include <unordered_map>

class Octree
{
	uint64_t code;
	std::bitset<8> octet;

	double x, y, z;
	double dx, dy, dz;
	void intialize_coordinates() {
		Morton::decodeMortonCode(code, x, y, z, dx, dy, dz);
	}

	void add_child(int i)			{		octet.set(i);				}
	void remove_child(int ii)		{		octet.reset(ii);			}
	bool checkOctet(int i)			{		return octet.test(i);		}

	uint64_t get_child_code(int i)	{		return (code << 3) | i ;	}
	uint64_t get_parent_code()		{		return code >> 3;			}
};


//uint32_t children;

//uint32_t get_child_count() {
//	children & (0x00000008);
//}

//uint32_t get_child(int i) { // 1-8
//	return (children >> (3 * i)) & 0x00000008;
//}

//uint32_t add_child(int i) {
//	octet.set(i);
//	children += (++i << get_child_count());
//	children++;
//}

//bool remove_child(int ii) {
//	auto length = get_child_count();
//	auto temp = children;
//	if (!octet.test(ii))
//		return false;
//	octet.reset(ii);
//	children--;
//	for (size_t i = 0; i < length*3; i+=3){
//		temp >>= 3;
//		if ((temp & 0x00000008) == ii)
//		{
//			temp >>= 3; i += 3;
//			// Shift left part down and combine with the right part
//			children = (temp << i) | (children & ((1 << i) - 1));
//			return true;
//		}
//	}
//	return false;
//}


