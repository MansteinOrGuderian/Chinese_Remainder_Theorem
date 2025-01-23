#include "Header.h"

int main() {
	Chinese_Remainder_Theorem_Info();
	std::vector<long long int> vector_of_remainders, vector_of_modulos;
	std::cout << "Enter amount of equations: ";
	int amount_of_equations(0);
	std::cin >> amount_of_equations;
	std::cout << "Enter remainders:\n";
	for (int i = 0; i < amount_of_equations; i++) {
		long long int remainder(0);
		std::cin >> remainder;
		vector_of_remainders.push_back(remainder);
	}
	std::cout << "Enter modulos:\n";
	for (int i = 0; i < amount_of_equations; i++) {
		long long int modulo(0);
		std::cin >> modulo;
		vector_of_modulos.push_back(modulo);
	}
	std::cout << "System to solve:\n";
	for (int i = 0; i < vector_of_remainders.size(); i++)
		std::cout << "x = " << vector_of_remainders[i] << " mod " << vector_of_modulos[i] << '\n';
	std::cout << "x = " << Chinese_Remainder_Theorem(vector_of_remainders, vector_of_modulos);
}