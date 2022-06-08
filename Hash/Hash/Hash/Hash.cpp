#include "Hash.h"

unsigned long long Hash(std::string filepath)
{
	unsigned long long FNV_offset_basis = 14695981039346656037;
	unsigned long long FNV_prime = 1099511628211;
	unsigned long long hash = FNV_offset_basis;
	char* byte = new char[16384];
	std::fstream file(filepath.c_str(), std::ios::in | std::ios::binary);
	const auto begin = file.tellg();
	file.seekg(0, std::ios::end);
	const auto end = file.tellg();
	int filesize = (end - begin);
	file.clear();
	file.seekg(0);
	while (filesize > 0)
	{
		file.read(byte, std::min(16384, filesize));
		int operations = std::min(16384, filesize);
		filesize -= 16384;
		for (int i = 0; i < operations; i++)
		{
			hash = (hash ^ byte[i]) * FNV_prime;
		}
	}
	return hash;
}

