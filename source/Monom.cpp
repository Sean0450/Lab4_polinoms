#include <iostream>
#include "Monom.h"
Monom::Monom() {
	this->degX = 0;
	this->degY = 0;
	this->degZ = 0;
	this->cf = 0;
}
Monom::Monom(double coeff, size_t X, size_t Y, size_t Z) {
	this->cf = coeff;
	this->degX = X;
	this->degY = Y;
	this->degZ = Z;

}
bool
Monom::Equals(const Monom& other){
	return cf == other.cf;
}
bool
Monom::operator==(const Monom& other) {
	return degX == other.degX && degY == other.degY && degZ == other.degZ;
}
bool
Monom::operator<(const Monom& other) {
	if (degX < other.degX) {
		return true;
	}
	if (degX < other.degX && degY < other.degY) {
		return true;
	}
	if (degX < other.degX && degY < other.degY && degZ < other.degZ) {
		return true;
	}
	return false;
}
bool
Monom::operator>(const Monom& other) {
	if (degX > other.degX) {
		return true;
	}
	if (degX > other.degX && degY > other.degY) {
		return true;
	}
	if (degX > other.degX && degY > other.degY && degZ > other.degZ) {
		return true;
	}
	return false;
}