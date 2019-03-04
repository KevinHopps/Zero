// zero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdexcept>
#include "../zero.h"

int main(int argc, char** argv)
{
	int result = 0;

	try
	{
		Args args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(argv[i]);

		zero(args);
	}
	catch (const std::exception& exc)
	{
		std::cerr << "exception: " << exc.what() << std::endl;
		result = 1;
	}
	catch (...)
	{
		std::cerr << "exception" << std::endl;
		result = 2;
	}

	return result;
}
