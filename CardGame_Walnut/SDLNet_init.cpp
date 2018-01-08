#include "SDLNet_init.hpp"
#include <iostream>

bool SDLNet::Init() {
	if (SDLNet_Init() < 0) {
		std::cout << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void SDLNet::Quit() {
	SDLNet_Quit();
}