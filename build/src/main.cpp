#include <iostream>
#include "tbitfield.h"

int main() {
	TBitField test(1024);
	std::cout << test.GetBit(32);
}