#include "Screen.h"
#include "GameBoy.h"

Screen::Screen()
	: m_screenData{ blackPixel }, m_window(nullptr), m_screen(nullptr)
{
	for (int x = 0; x < _SCREEN_W; ++x)
		for (int y = 0; y < _SCREEN_H; ++y)
			m_screenData[x + y * _SCREEN_W] = blackPixel;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	m_window = SDL_CreateWindow
	(
		"Hadron Game Boy emulator", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_SCREEN_EMU_W, _SCREEN_EMU_H,
		SDL_WINDOW_SHOWN
	);

	m_screen = SDL_GetWindowSurface(m_window);

	SDL_FillRect(m_screen, NULL, SDL_MapRGB
	(
		m_screen->format,
		whitePixel.r,
		whitePixel.g,
		whitePixel.b
	));

	SDL_UpdateWindowSurface(m_window);
}

Screen::~Screen()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Screen::write(H_WORD addr, H_BYTE data)
{
	gb->write(addr, data);
}
H_BYTE  Screen::read(H_WORD addr)
{
	return gb->read(addr);
}
H_BYTE* Screen::read_ptr(H_WORD addr)
{
	return gb->read_ptr(addr);
}

void Screen::set_pixel(int x, int y, ScreenData sd)
{
	m_screenData[x + y * _SCREEN_W] = sd;

	int _x = x * _SCREEN_M;
	int _y = y * _SCREEN_M;

	for (int x_offset = 0; x_offset < _SCREEN_M; ++x_offset)
	{
		for (int y_offset = 0; y_offset < _SCREEN_M; ++y_offset)
		{
			Uint8* p = (Uint8*)m_screen->pixels + (_y + y_offset) * m_screen->pitch + (_x + x_offset) * 4;
			*(Uint32*)p = SDL_MapRGB
			(
				m_screen->format, 
				m_screenData[x + y * _SCREEN_W].r, 
				m_screenData[x + y * _SCREEN_W].g, 
				m_screenData[x + y * _SCREEN_W].b
			);
		}
	}
}
