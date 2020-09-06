#pragma once
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>

#include "olcPixelGameEngine.h"

class GameBoy;

class Debugger : public olc::PixelGameEngine
{
public:
	Debugger() { sAppName = "Hadron GameBoy Debugger"; }

	inline void connect_device(GameBoy* instance) { gb = instance; };
	GameBoy *gb = nullptr;

	std::map<uint16_t, std::string> map_asm;

	std::string hex(uint32_t, uint8_t);

	void draw_ram(int, int, uint16_t, int, int);
	void draw_cpu(int, int);
	void draw_code(int, int, int);

	bool OnUserCreate();
	bool OnUserUpdate(float);
};

