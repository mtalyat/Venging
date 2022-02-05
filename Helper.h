#ifndef HELPER_H
#define HELPER_H

#include <fstream>
#include <iostream>
#include <bitset>
#include "Console.h"

#define vBYTE unsigned char
#define vBYTE_MAX 255

/// <summary>
/// Compacts the 4 bytes into one integer. The first argument represents the set of least significant bits.
/// </summary>
/// <param name="b0"></param>
/// <param name="b1"></param>
/// <param name="b2"></param>
/// <param name="b3"></param>
/// <returns></returns>
inline int compact(int b0, int b1, int b2, int b3)
{
	int output = 0;
	output |= b3;
	output <<= 8;
	output |= b2;
	output <<= 8;
	output |= b1;
	output <<= 8;
	output |= b0;
	return output;
}

/// <summary>
/// Extracts compacted data from an integer. The index is used to determine which "byte" to pick. 0 represents the least significant bits, and 3 represents the most significant.
/// </summary>
/// <param name="data"></param>
/// <param name="index"></param>
/// <returns></returns>
inline int extract(int data, int index)
{
	return (data >> (index * 8)) & 0b00000000000000000000000011111111;
}

/// <summary>
/// Gets the contents from the file in resources as a string.
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
inline std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

/// <summary>
/// Reads the given amount of numbers from the given file, and stores them in the given integer pointer array.
/// </summary>
/// <param name="filename"></param>
/// <param name="numbers"></param>
/// <param name="amount"></param>
inline void readNumbersFromFile(const char* filename, int* numbers, int amount)
{
	int i = 0;

	std::ifstream file(filename);
	if (!file.is_open())
	{
		Console::LogError("Could not open file.");
		return;
	}

	int current;
	while (i < amount && file >> current)
	{
		*numbers = current;

		numbers++;
		i++;
	}

	file.close();
}

#endif
