#define _CRT_SECURE_NO_WARNINGS

#include "Cartridge.h"

#include <algorithm>
#include <iostream>
#include <fstream>

Cartridge::Cartridge(const char* filename)
	: m_memory{ 0 }
{
	//m_memory = new H_BYTE[_CARTRIDGE_SIZE];
	for (int i = 0; i < _CARTRIDGE_SIZE; ++i)
		m_memory[i] = 0;

	std::cout << "Loading: " << filename << std::endl;

	FILE* pFile = nullptr;
	pFile = fopen(filename, "rb");
	if (pFile == nullptr)
	{
		std::cerr << "ROM file failure" << std::endl;
		exit(1);
	}

	fseek(pFile, 0, SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	printf("Game size: %d\n", (int)lSize);

	size_t result = fread(m_memory, 1, lSize, pFile);
	if (result != lSize)
	{
		std::cerr << "ROM read failure" << std::endl;
		exit(1);
	}

	if (lSize > _CARTRIDGE_SIZE)
		std::cerr << "Error: ROM too big for memory" << std::endl;

	fclose(pFile);
}

Cartridge::~Cartridge()
{
	delete[] m_memory;
}