#pragma once

#include <iostream>

inline void test(bool condition)
{
	std::cout << (condition ? "OK." : "Fail!") << "\n";
}
