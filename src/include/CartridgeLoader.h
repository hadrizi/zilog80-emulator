#pragma once
#include "core.h"
#include "Cartridge.h"

class GameBoy;

class CartridgeLoader
{
public:
	inline void connect_device(GameBoy* instance) { gb = instance; };
	void load_cartridge(Cartridge&);
private:
	// GameBoy instance
	GameBoy* gb = nullptr;
	void    write(H_WORD, H_BYTE);
	H_BYTE  read(H_WORD);
	H_BYTE* read_ptr(H_WORD);
};

