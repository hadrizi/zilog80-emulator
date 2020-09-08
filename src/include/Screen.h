#pragma once
#define _SCREEN_W 160
#define _SCREEN_H 144
#define _SCREEN_M 5
#define _SCREEN_EMU_W _SCREEN_W * _SCREEN_M
#define _SCREEN_EMU_H _SCREEN_H * _SCREEN_M

#include "core.h"

#include <SDL.h>

#include <cstdlib>
#include <iostream>

class GameBoy;

struct ScreenData : public Color
{
	using Color::Color;
};

const ScreenData whitePixel     = ScreenData(0xE0, 0xF8, 0xD0);
const ScreenData lightGreyPixel = ScreenData(0xCC, 0xCC, 0xCC);
const ScreenData darkGreyPixel  = ScreenData(0x77, 0x77, 0x77);
const ScreenData blackPixel     = ScreenData(0x00, 0x00, 0x00);

class Screen
{
public:
	Screen();
	~Screen();

	inline void connect_device(GameBoy* instance) { gb = instance; };
	inline void flush() { SDL_UpdateWindowSurface(m_window); }

	void set_pixel(int, int, ScreenData);

private:
	ScreenData m_screenData[_SCREEN_W * _SCREEN_H];

	// SDL context
	SDL_Window* m_window;
	SDL_Surface* m_screen;
private:
public:
	// GameBoy instance
	GameBoy* gb = nullptr;
	void  write(H_WORD, H_BYTE);
	H_BYTE  read(H_WORD);
	H_BYTE* read_ptr(H_WORD);
};

