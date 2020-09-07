#define OLC_PGE_APPLICATION
#include "include/GameBoy.h"

#include <iostream>

int main(int argc, char** argv)
{
	GameBoy* gb = new GameBoy();

	//Cartridge c("C:\\personal\\8bitgames\\GB\\Tetris.gb");
	//gb->cartrdige_loader.load_cartridge(c);

	std::cout << (1u << 9) << std::endl;
	gb->debugger.Construct(680, 480, 2, 2);
	gb->debugger.Start();

	std::cin.get();
	return 0;
}