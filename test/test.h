#pragma once

#include <iostream>

void test(bool condition)
{
	std::cout << (condition ? "OK." : "Fail!") << "\n";
}
