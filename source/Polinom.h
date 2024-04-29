#pragma once
#include <iostream>
#include "Monom.h"
#include "List.h"
class Polinom: public List<Monom> {
public:
	size_t nonDisplayedZeros = 1;
public:
	Polinom();
	Polinom(Polinom& other);
	
	void add_monom(Monom mn);
	void add_monom(std::string monom, short flag);
	void add_polinom(std::string pmn);
	void subtract_monom(Monom mn);
	void mult_monom(double coef);
	void mult_monom(Monom mn);

	double calculation_in_the_point(int x, int y, int z);
	Polinom derivative(char variable);
	Polinom integrate(char variable);
	Polinom add_polinom(Polinom& other);

	Polinom& operator=(Polinom& other);

	std::string to_str();
	~Polinom() {};
};