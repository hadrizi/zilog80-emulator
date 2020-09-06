#pragma once
#include <array>

#include "core.h"
#include "Screen.h"
#include "CPUZ80.h"
#include "CartridgeLoader.h"
#include "Screen.h"
#include "Debugger.h"

class GameBoy
{
public:
	GameBoy();
	~GameBoy();

public:// Hardware
	CPUZ80 cpu;                       // Custom 8-bit Sharp LR35902. Simplified Z80.
    CartridgeLoader cartrdige_loader; // Cartridge loader. One cartrdige at a time
    Screen screen;                    // 160x144 monochromic screen
    Debugger debugger;                // Just simple debugger

	/* 
		Memory Map
        Interrupt Enable Register
        --------------------------- FFFF
        Internal RAM
        --------------------------- FF80
        Empty but unusable for I/O
        --------------------------- FF4C
        I/O ports
        --------------------------- FF00
        Empty but unusable for I/O
        --------------------------- FEA0
        Sprite Attrib Memory (OAM)
        --------------------------- FE00
        Echo of 8kB Internal RAM
        --------------------------- E000
        8kB Internal RAM
        --------------------------- C000
        8kB switchable RAM bank
        --------------------------- A000
        8kB Video RAM
        --------------------------- 8000 --
        16kB switchable ROM bank           |
        --------------------------- 4000   |= 32kB Cartrigbe
        16kB ROM bank #0                   |     
        --------------------------- 0000 --

        TOTAL 64kB of memory
	*/
	std::array<H_BYTE, 64 * 1024> m_memory;

public:
    void  write(H_WORD, H_BYTE);
    H_BYTE  read(H_WORD);
    H_BYTE* read_ptr(H_WORD);
};

