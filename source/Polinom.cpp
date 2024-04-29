#include <iostream>
#include "Polinom.h"
#include <string>
Polinom::Polinom() :List<Monom>::List() {
	Monom mn;
	mn.cf = 1;
	mn.degX = mn.degY = 0;
	mn.degZ = -1;
	head->value = mn;
}

Polinom::Polinom(Polinom& other) {
	Monom mn(1, 0, 0, -1);
	head->value = mn;
	zero();
	for (size_t j = 0; j < other.size; j++) {
		insert_last(other.get_current());
		next();
	}
}
void
Polinom::add_monom(std::string str, short flag) {
	size_t i = 0;
	while (i < str.length()) {
		std::string coeff;
		for (; isdigit(str[i]) || str[i] == ' ' || str[i] == '-' || str[i] == ','; i++) {
			if (str[i] == ' ') { continue; }
			coeff.push_back(str[i]);
		}
		std::string degX, degY, degZ;
		if (str[i] == 'x') {
			i += 2;
			while (isdigit(str[i]))
			{
				degX.push_back(str[i]);
				i++;
			}
		}
		if (str[i] == 'y')
		{
			i += 2;
			while (isdigit(str[i]))
			{
				degY.push_back(str[i]);
				i++;
			}
		}
		if (str[i] == 'z')
		{
			i += 2;
			while (isdigit(str[i]))
			{
				degZ.push_back(str[i]);
				i++;
			}
		}
		double _coef = 1;
		size_t _degX = 0, _degY = 0, _degZ = 0;
		if (!coeff.empty()) {
			_coef = stod(coeff);
			if (flag == 0) {
				_coef = -_coef;
			}
		}
		if (!degX.empty()) {
			_degX = stoi(degX);
		}
		if (!degY.empty()) {
			_degY = stoi(degY);
		}
		if (!degZ.empty()) {
			_degZ = stoi(degZ);
		}
		if (flag == 0) {
			subtract_monom(Monom(_coef, _degX, _degY, _degZ));
		}
		if (flag == 1) {
			add_monom(Monom(_coef, _degX, _degY, _degZ));
		}
		if (flag == 2) {
			mult_monom(Monom(_coef, _degX, _degY, _degZ));
		}
	}
}
void
Polinom::add_polinom(std::string pmn) {
	size_t i = 0;
	std::string mn;
	while (i < pmn.length() - 1) {
		mn = "";
		if (pmn[i] == '+') {
			i++;
			while (true) {
				if (pmn[i] == '+' || pmn[i] == ' ' || pmn[i] == '-') {
					break;
				}
				mn.push_back(pmn[i]);
				i++;
				if (i == pmn.length()) {
					i--;
					break;
				}
			}
			add_monom(mn, 1);
		}
		else if (pmn[i] == '-') {
			i++;
			while (true) {
				if (pmn[i] == '+' || pmn[i] == ' ' || pmn[i] == '-') {
					break;
				}
				mn.push_back(pmn[i]);
				i++;
				if (i == pmn.length()) {
					i--;
					break;
				}
			}
			add_monom(mn, 0);
		}
		else {
			while (pmn[i] != '+') {
				if (pmn[i] == '-') {
					break;
				}
				mn.push_back(pmn[i]);
				i++;
			}
			add_monom(mn, 1);
		}
	}
}
void
Polinom::add_monom(Monom m) {
	zero();
	while (m < current->value) {
		next();
	}
	if (current->value == m) {
		current->value.cf += m.cf;
		if (current->value.cf == 0) {
			delete_current();
		}
	}
	else {
		insert_current(m);
	}
}
void
Polinom::subtract_monom(Monom mn) {
	zero();
	bool flag = false;
	for (size_t j = 0; j < size; j++) {
		if (current->value == mn) {
			current->value.cf -= mn.cf;
			flag = true;
			if (current->value.cf == 0) {
				delete_current();
				return;
			}
			else { return; }
		}
		next();
	}
	if (flag == false) {
		insert_last(mn);
	}
}
Polinom
Polinom::derivative(char variable) {
	zero();
	Polinom result;
	for (size_t j = 0; j < size; j++) {
		Monom tmp = get_current();
		if (variable == 'x') {
			tmp.cf *= tmp.degX;
			tmp.degX --;
		}
		if (variable == 'y') {
			tmp.cf *= tmp.degY;
			tmp.degY --;
		}
		if (variable == 'z') {
			tmp.cf *= tmp.degZ;
			tmp.degZ --;
		}
		result.add_monom(tmp);
		next();
	}
	return result;
}
Polinom
Polinom::integrate(char variable) {
	Polinom result;
	zero();
	for (size_t j = 0; j < size; j++) {
		Monom tmp = get_current();
		if (variable == 'x') {
			tmp.cf /= tmp.degX;
			tmp.degX++;
		}
		if (variable == 'y') {
			tmp.cf /= tmp.degY;
			tmp.degY++;
		}
		if (variable == 'z') {
			tmp.cf /= tmp.degZ;
			tmp.degZ++;
		}
		result.add_monom(tmp);
	}
	return result;
}
void
Polinom::mult_monom(Monom mn) {
	zero();
	for (size_t j = 0; j < size; j++) {
		Monom result = get_current();
		result.cf *= mn.cf;
		result.degX += mn.degX;
		result.degY += mn.degY;
		result.degZ += mn.degZ;
		current->value = result;
		next();
	}
}
void
Polinom::mult_monom(double coef) {
	zero();
	for (size_t j = 0; j < size; j++) {
		Monom result = get_current();
		result.cf *= coef;
		current->value = result;
		next();
	}
}
double
Polinom::calculation_in_the_point(int x, int y, int z) {
	zero();
	size_t answer = 0;
	for (size_t j = 0; j < size; j++) {
		answer += current->value.cf * pow(x, current->value.degX) * pow(y, current->value.degY) * pow(z, current->value.degZ);
		next();
	}
	return answer;

}
std::string
Polinom::to_str() {
	std::string res;
	size_t j = 0;
	zero();
	for (j; j < size; j++) {
		Monom mn = get_current();
		std::string coeff = std::to_string(mn.cf);
		for (int i = 0; i < nonDisplayedZeros; i++) {
			coeff.pop_back();
			res += " " + coeff;
			if (mn.degX != 0) {
				res += "x^" + std::to_string(mn.degX);
			}
			if (mn.degY != 0) {
				res += "y^" + std::to_string(mn.degY);
			}
			if (mn.degZ != 0) {
				res += "z^" + std::to_string(mn.degZ);
			}
			res += " ";
			if (current->next != nullptr && size > 1) {
				res += "+";
			}
		}
		next();
	}
	return res;
}
Polinom
Polinom::add_polinom(Polinom& other) {
	Polinom res(other);
	zero();
	for (size_t j = 0; j < size; j++) {
		res.add_monom(get_current());
		next();
	}
	return res;
}
Polinom&
Polinom::operator=(Polinom& other) {
	while (head != tail) {
		Node<Monom>* tmp = head;
		head = head->next;
		delete tmp;
	}
	head = new Node<Monom>();
	head->next = head;
	tail = current = previous = head;
	size = 0;
	other.zero();
	for (size_t j = 0; j < other.size; j++) {
		add_monom(other.get_current());
		other.next();
	}

	return *this;
}