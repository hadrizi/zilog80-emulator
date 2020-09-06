#include "CartridgeLoader.h"
#include "GameBoy.h"

void CartridgeLoader::load_cartridge(Cartridge& cartrdige)
{
	for (int i = 0; i < _CARTRIDGE_SIZE; i++)
	{
		write(i + 0x100, cartrdige.m_memory[i]);
	}
}

void CartridgeLoader::write(H_WORD addr, H_BYTE data)
{
	gb->write(addr, data);
}
H_BYTE  CartridgeLoader::read(H_WORD addr)
{
	return gb->read(addr);
}
H_BYTE* CartridgeLoader::read_ptr(H_WORD addr)
{
	return gb->read_ptr(addr);
}