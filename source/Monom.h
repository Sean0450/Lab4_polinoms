#pragma once
#include <iostream>
class Monom {
public:
	double cf;
	size_t degX, degY, degZ;
public:
	Monom();
	Monom(double coeff, size_t degX, size_t degY, size_t degZ);
	~Monom() {};
	bool Equals(const Monom& other);
	bool operator==(const Monom& other);
	bool operator>(const Monom& other);
	bool operator<(const Monom& other);
};