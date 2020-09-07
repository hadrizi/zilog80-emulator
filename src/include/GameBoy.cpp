#include "GameBoy.h"

GameBoy::GameBoy()
{
	cpu.connect_device(this);
	cpu.reset();

	cartrdige_loader.connect_device(this);
	screen.connect_device(this);
	debugger.connect_device(this);

	screen.flush();

	for (auto& i : m_memory) i = 0x00;
}

GameBoy::~GameBoy()
{

}

void GameBoy::write(H_WORD addr, H_BYTE data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		m_memory[addr] = data;
}

H_BYTE GameBoy::read(H_WORD addr)
{	
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return m_memory[addr];

	return 0x00;
}

H_BYTE* GameBoy::read_ptr(H_WORD addr)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return &m_memory[addr];

	return nullptr;
}