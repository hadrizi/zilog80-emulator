#pragma once
#define _CARTRIDGE_SIZE 0x200000

#include "core.h"

struct Cartridge
{
	Cartridge(const char*);
	~Cartridge();

	H_BYTE m_memory[_CARTRIDGE_SIZE];
};

