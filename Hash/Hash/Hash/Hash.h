#pragma once
#include <fstream>
#include <math.h>

#ifdef HASH_EXPORTS
#define HASH_API _declspec(dllexport)
#else
#define HASH_API _declspec(dllimport)
#endif

unsigned long long HASH_API Hash(std::string filepath);
