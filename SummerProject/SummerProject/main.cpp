//main.cpp
#include <iostream>
#include "SFML\Graphics.hpp"
#include "Core.h"

int main()
{
	Core core;
	if (!core.initialize())
	{
		std::cout << "there is something wrong" << std::endl;
	}
	core.run();
	
	return 0;
}