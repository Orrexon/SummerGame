// SummerGamev2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Core core;
	if (!core.initialize())
	{
		std::cout << "there is something wrong" << std::endl;
	}
	core.run();
	return 0;
}

