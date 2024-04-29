#include <iostream>
#include "Polinom.h"
#include <string>
int main() {
	Polinom p1;
	size_t command = 0;
	std::cout << "1.Add monon" << std::endl << "2.Add polinom" << std::endl << "3.Print polinom" << std::endl << "4.Multiply" << std::endl << "5.Derivative monoms by variable (x, y, z)" << std::endl << "6.Integrate monoms by variable (x, y, z)" << std::endl<<"7.Calculating value of the polinom in the point"<<std::endl<<"8.Cancel"<<std::endl;
	while (command != 8) {
		std::string polinom;
		std::cout << "Enter the command: ";
		std::cin >> command;
		std::cout << std::endl;
		_flushall();
		if (command == 1) {
			std::cout << "Enter monom (6x^4y^2z^10): ";
			std::cin >> polinom;
			if (polinom[0] == '-') {
				p1.add_monom(polinom, 0);
			}
			p1.add_monom(polinom, 1);
		}
		if (command == 2) {
			command = 0;
			std::cout << "Enter polinom (10x^2y^3z^4+20x^3y^4z^5): ";
			std::cin >> polinom;
			p1.add_polinom(polinom);
		}
		if (command == 3) {
			std::cout << p1.to_str() << std::endl;;
		}
		if (command == 4) {
			char tmp;
			std::cout << "Do you want to multiply polinom by the coefficient or by the monom <C/M>: ";
			std::cin >> tmp;
			std::cout<<std::endl;
			if (tmp == 'C') {
				double cf;
				std::cout << "Enter the coefficient: ";
				std::cin >> cf;
				p1.mult_monom(cf);
			}
			if (tmp == 'M') {
				std::string tmp;
				std::cout << "Enter the monom: ";
				std::cin >> tmp;
				p1.add_monom(tmp, 2);
			}
		}
		if (command == 5) {
			char variable;
			std::cout << "Enter the variable: ";
			std::cin >> variable;
			std::cout << std::endl<<"Result = " + p1.derivative(variable).to_str() << std::endl;
		}
		if (command == 6) {
			char variable;
			std::cout << "Enter the variable: ";
			std::cin >> variable;
			std::cout << std::endl << "Result = " + p1.integrate(variable).to_str() << std::endl;
		}
		if (command == 7) {
			std::string coeffs;
			std::string x, y, z;
			size_t fl = 0;
			size_t i = 0;
			std::cout << "Enter the coefficients (x,y,z): ";
			std::cin >> coeffs;
			std::cout << std::endl;
			while (i < coeffs.length() - 1) {
				if (coeffs[i] == ',') {
					i++;
					fl++;
				}
				else {
					if (fl == 0)x.push_back(coeffs[i]);
					if (fl == 1)y.push_back(coeffs[i]);
					else z.push_back(coeffs[i]);
					i++;
				}
			}
			std::cout << "Result = "<< p1.calculation_in_the_point(stod(x), stod(y), stod(z))<<std::endl;
		}

	}
	return 0;
}