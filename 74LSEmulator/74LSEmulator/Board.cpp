#include <iostream>
#include <bitset>
#include <cstdint>
#include "SN74LS.h"

int main()
{
	//SN74LS32 IC1(0b10, 0b11);
	//IC1.tick();
	//IC1.getPins();

	//SN74LS86 IC2(0b011, 0b110);
	//IC2.tick();
	//IC2.getPins();

	//SN74LS08 IC3(0b0101, 0b0011);
	//IC3.tick();
	//IC3.getPins();

	//SN74LS04 IC4(0b000111);
	//IC4.tick();
	//IC4.getPins();

	//SN74LS283 IC5;
	//IC5.tick();
	//std::cout << IC5.C4;

	SN74LS139 ic1(0b00, false, 0b11, false);
	ic1.tick();
	ic1.getPins();



	std::cin.get();
	return 0;
}