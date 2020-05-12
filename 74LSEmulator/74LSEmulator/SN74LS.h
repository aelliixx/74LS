/*
	License GNU AGPLv3
	~~~~~~~~~~~~~~~

	Copyright 2020 Donatas Mockus
*/

#pragma once
#include <cstdint>
#include <bitset>

namespace Alx
{
	uint8_t mask(uint8_t a, uint8_t mask)
	{
		return a & mask;
	}
	uint8_t flipBits(uint8_t a, int bitCount)
	{
		a = Alx::mask(a, 0b11111111 >> (8 - bitCount));
		uint8_t t = ((a << bitCount) + a) >> 1;
		a = Alx::mask(t, 0b11111111 >> (8 - bitCount));
		return a;
	}
}

// Quad dual input gates
class gate
{
protected:
	uint8_t A;
	uint8_t B;
public:
	uint8_t Y = 0b0;
	gate() : A(0b0), B(0b0) {}
	~gate() {}

	void getPins()
	{
		std::cout << std::bitset<4>(static_cast<uint16_t>(Y)) << std::endl;
	}
};

class SN74LS00 : public gate
{
public:
	SN74LS00() { this->A = 0b0, this->B = 0b0; }
	SN74LS00(uint8_t A, uint8_t B) { this->A = A, this->B = B; }
	SN74LS00 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->Y = ~(this->A & this->B);
		return *this;
	}
	SN74LS00 tick()
	{
		this->Y = ~(this->A & this->B);
		return *this;
	}
};

class SN74LS02 : public gate
{
public:
	SN74LS02() { this->A = 0b0, this->B = 0b0; }
	SN74LS02(uint8_t A, uint8_t B) { this->A = A, this->B = B; }
	SN74LS02 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->Y = ~(this->A | this->B);
		return *this;
	}
	SN74LS02 tick()
	{
		this->Y = ~(A | B);
		return *this;
	}
};

class SN74LS08 : public gate
{
public:
	SN74LS08() { this->A = 0b0, this->B = 0b0; }
	SN74LS08(uint8_t A, uint8_t B) { this->A = A, this->B = B; }
	SN74LS08 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->Y = this->A & this->B;
		return *this;
	}
	SN74LS08 tick()
	{
		this->Y = this->A & this->B;
		return *this;
	}
};

class SN74LS32 : public gate
{
public:
	SN74LS32() { this->A = 0b0, this->B = 0b0; }
	SN74LS32(uint8_t A, uint8_t B) { this->A = A, this->B = B; }
	SN74LS32 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->Y = this->A | this->B;
		return *this;
	}
	SN74LS32 tick()
	{
		this->Y = A | B;
		return *this;
	}
};

class SN74LS86 : public gate
{
public:
	SN74LS86() { this->A = 0b0, this->B = 0b0; }
	SN74LS86(uint8_t A, uint8_t B) { this->A = A, this->B = B; }
	SN74LS86 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->Y = this->A ^ this->B;
		return *this;
	}
	SN74LS86 tick()
	{
		this->Y = A ^ B;
		return *this;
	}
};

// Hex inverter
class SN74LS04
{
private:
	uint8_t A;
public:
	uint8_t Y = 0b0;
	SN74LS04() { this->A = 0b111111; }
	SN74LS04(uint8_t A) { this->A = A; }
	SN74LS04 tick(uint8_t A)
	{
		this->A = A;
		this->Y = ~this->A;
		return *this;
	}
	SN74LS04 tick()
	{
		this->Y = ~this->A;
		return *this;
	}
	void getPins()
	{
		std::cout << std::bitset<6>(static_cast<uint16_t>(Y)) << std::endl;
	}
};

// Hex buffer
class SN74LS07
{
private:
	uint8_t A;
public:
	uint8_t Y = 0b0;
	SN74LS07() { this->A = 0b111111; }
	SN74LS07(uint8_t A) { this->A = A; }
	SN74LS07 tick(uint8_t A)
	{
		this->A = A;
		this->Y = this->A;
		return *this;
	}
	SN74LS07 tick()
	{
		this->Y = this->A;
		return *this;
	}
	void getPins()
	{
		std::cout << std::bitset<6>(static_cast<uint16_t>(Y)) << std::endl;
	}
};

class SN74LS283
{
private:
	uint8_t A;
	uint8_t B;
	bool C0;
public:
	uint8_t Y;
	bool C4;
	SN74LS283() : A(0b0), B(0b0), C0(false), C4(false) {}
	SN74LS283(uint8_t A, uint8_t B, bool C0) : A(A), B(B), C0(C0), C4(false) {}
	SN74LS283(uint8_t A, uint8_t B) : A(A), B(B), C0(false), C4(false) {}
	~SN74LS283() {}

	void add(uint8_t A, uint8_t B, uint8_t C0/*uint8_t A1, uint8_t A2, uint8_t A3, uint8_t A4, uint8_t B1, uint8_t B2, uint8_t B3, uint8_t B4,*/)
	{
		/*uint8_t E = 0b00000, E1, E2, E3, E4, C;
		E1 = (~C0 ^ (~(~(A1 | B1)) & ~(A1 & B1)));
		E2 = (~((C0 & ~(A1 & B1)) | ~(A1 | B1)) ^ (~(~(A2 | B2)) & ~(A2 & B2)));
		E3 = (~((C0 & ~(A1 & B1) & ~(A2 & B2)) | (~(A2 & B2) & ~(A1 | B1)) | ~(A2 | B2)) ^ (~(~(A3 | B3)) & ~(A3 & B3)));
		E4 = (~((C0 & ~(A1 & B1) & ~(A2 & B2) & ~(A3 & B3)) | (~(A2 & B2) & ~(A3 & B3) & ~(A1 | B1)) | (~(A3 & B3) & ~(A2 | B2)) | ~(A3 | B3) ^ (~(~(A4 | B4)) & ~(A4 & B4))));
		this->C4 = (~((C0 & ~(A1 & B1) & ~(A2 & B2) & ~(A3 & B3) & ~(A4 & B4)) | (~(A2 & B2) & ~(A3 & B3) & ~(A4 & B4) & ~(A1 | B1)) | (~(A3 & B3) & ~(A4 & B4) & ~(A2 | B2)) | (~(A4 & B4) & ~(A3 | B3)) | ~(A4 | B4)));
		E = (E1 << 4) + (E2 << 3) + (E3 << 2) + E4 + (C4 << 5); this doesn't work but I'm leaving it in honour of the hours I spent writing it*/
		this->A = Alx::mask(A, 0b1111);
		this->B = Alx::mask(B, 0B1111);
		Y = this->A + this->B;
		C4 = Alx::mask(Y >> 4, 0b1);
	}
	SN74LS283 tick()
	{
		add(this->A, this->B, this->C0);
		return *this;
	}
	SN74LS283 tick(uint8_t A, uint8_t B, uint8_t C0)
	{
		this->A = A;
		this->B = B;
		this->C0 = C0;
		add(this->A, this->B, this->C0);
		return *this;
	}
	SN74LS283 tick(uint8_t A, uint8_t B)
	{
		this->A = A;
		this->B = B;
		this->C0 = 0b0;
		add(this->A, this->B, this->C0);
		return *this;
	}
	void getPins()
	{
		std::cout << std::bitset<4>(static_cast<uint16_t>(Y)) << " " << C4 << std::endl;
	}
};

class SN74LS139
{
private:
	uint8_t A = 0b0;
	uint8_t B = 0b0;
	bool Ea_ = false;
	bool Eb_ = false;
public:
	uint8_t Ya = 0b0;
	uint8_t Yb = 0b0;
	SN74LS139() : A(0b0), B(0b0), Ea_(false), Eb_(false) {}
	SN74LS139(uint8_t A, bool Ea_) : A(A), Ea_(Ea_), B(0b0), Eb_(false) {}
	SN74LS139(uint8_t A, bool Ea_, uint8_t B, bool Eb_) : A(A), Ea_(Ea_), B(B), Eb_(Eb_) {}

	void deMultiplex()
	{
		this->A = Alx::flipBits(this->A, 2);
		this->B = Alx::flipBits(this->B, 2);

		if (!Ea_)
			this->Ya = ~(0b1000 >> this->A);
		else
			this->Ya = 0b1111;
		if (!Eb_)
			this->Yb = ~(0b1000 >> this->B);
		else
			this->Yb = 0b1111;
	}
	SN74LS139 tick()
	{
		deMultiplex();
		return *this;
	}
	SN74LS139 tick(uint8_t A, bool Ea_)
	{
		this->A = A;
		this->Ea_ = Ea_;
		deMultiplex();
		return *this;
	}
	SN74LS139 tick(uint8_t A, bool Ea_, uint8_t B, bool Eb_)
	{
		this->A = A;
		this->Ea_ = Ea_;
		this->B = B;
		this->Eb_ = Eb_;
		deMultiplex();
		return *this;
	}
	void getPins()
	{
		std::cout << std::bitset<4>(static_cast<uint16_t>(Ya)) << " " << std::bitset<4>(static_cast<uint16_t>(Yb)) << std::endl;
	}
};