#pragma once
#include <iostream>
#include <vector>

long long int Finding_inverse_by_modulo(long long int number_to_inverse, long long int modulo_number) {
	if (number_to_inverse == 0 || modulo_number == 0)// gcd(0, 0) = 0, gcd (0, n) = n, gcd (n, 0) = n
		return 0; // In this cases inverse don't exist
	if (number_to_inverse > modulo_number)
		number_to_inverse = number_to_inverse % modulo_number;
	long long int r_i_minus_one = number_to_inverse, r_i = modulo_number, q(0), r_i_plus_one(1);
	std::vector<long long int> r_i_minus_one_vector, r_i_vector, q_vector, minus_q_vector, r_i_plus_one_vector;
	while (r_i_plus_one != 0) { // common Euclidean Algorithm
		q = r_i_minus_one / r_i;
		r_i_plus_one = r_i_minus_one % r_i;
		q_vector.push_back(q), minus_q_vector.push_back(-q), r_i_plus_one_vector.push_back(r_i_plus_one);
		r_i_minus_one_vector.push_back(r_i_minus_one), r_i_vector.push_back(r_i);
		r_i_minus_one = r_i;
		r_i = r_i_plus_one;
	}
	/*for (long long int i = 0; i < q_vector.size(); i++)
		std::cout << r_i_minus_one_vector[i] << " = " << r_i_vector[i] << " * " << q_vector[i] << " + " << r_i_plus_one_vector[i] << '\n';*/
	if (r_i_vector.back() != 1) { // gcd(a, b) != 1, a^{-1} don't exist
		//std::cout << "Doesn't exict a^{-1} mod b\n" << number_to_inverse << "^{-1} mod " << modulo_number << '\n';
		return 0; // error code
	}
	else {
		//std::cout << "Exict a^{-1} mod b\n" << number_to_inverse << "^{-1} mod " << modulo_number << '\n';
		minus_q_vector.erase(minus_q_vector.begin()); // first element in vector always 0, so we delete it
		long long int temp_i_minus_one = 0, temp_i = 1, temp_i_plus_one;
		std::vector<long long int> temp_vector;
		temp_vector.push_back(0), temp_vector.push_back(1);
		for (long long int i = 0; i < minus_q_vector.size(); i++) {
			temp_i_plus_one = minus_q_vector[i] * temp_i + temp_i_minus_one;
			temp_i_minus_one = temp_i;
			temp_i = temp_i_plus_one;
			temp_vector.push_back(temp_i_plus_one);
		}
		/*for (long long int i = 0; i < minus_q_vector.size(); i++) {
			if (i == 0)
				std::cout << " |  |";
			std::cout << minus_q_vector[i] << ((i != minus_q_vector.size() - 1) ? '|' : '\n');
		}
		for (long long int i = 0; i < temp_vector.size(); i++)
			std::cout << temp_vector[i] << ((i != temp_vector.size() - 1) ? '|' : '\n');*/
		return temp_vector[(temp_vector.size() - 2)]; // need penultimate element, because last element is modulo
	}
}

void Chinese_Remainder_Theorem_Info() {
	std::cout << "----- Chinese Remainder Theorem -----\n";
	std::cout << "Given following system of equations:\n";
	std::cout << "x = r_1 mod m_1\n	...	\nx = r_i mod m_i\n	...	\nx = r_n mod m_n\n";
	std::cout << "Finding x using formula:\n";
	std::cout << "x = (r_1 * M_1 * N_1 + ... + r_i * M_i * N_i + ... + r_n * M_n * N_n) mod M,\nWhere:\n";
	std::cout << "M = m_1 * ... * m_i * ... * m_n,\nM_i = M / m_i,\nN_i = M_i^{-1} mod m_i\n";
	std::cout << "ATTENTION!\nBe careful, that /forall i, j = /overline{1, n}, i != j, should fulfilled gcd(m_i, m_j) = 1 - pairwise coprime numbers.\n";
	std::cout << "In this code it doesn't check.\nUnhandled exceptions:\n1) If one of m_i = 0 - will be error (program will crash).\n";
	std::cout << "2) If one of gcd(m_i, m_j) != 1, you will get x = 0 - wrong code answer because x doesn't exist.\n";
}

long long int Chinese_Remainder_Theorem(std::vector<long long int>& vector_of_remainders, std::vector<long long int>& vector_of_modulos) {
	long long int production_of_modulos = 1;
	for (auto modulo : vector_of_modulos)
		production_of_modulos *= modulo;
	std::vector<long long int> vector_of_M, vector_of_N;
	for (auto modulo : vector_of_modulos) {
		long long int M_i = production_of_modulos / modulo;
		vector_of_M.push_back(M_i);
	}
	for (int i = 0; i < vector_of_modulos.size(); i++) {
		long long int N_i = Finding_inverse_by_modulo(vector_of_M[i], vector_of_modulos[i]);
		vector_of_N.push_back(N_i);
	}
	long long int x = 0;
	std::cout << "x = (";
	for (int i = 0; i < vector_of_modulos.size(); i++) {
		x += (vector_of_remainders[i] * vector_of_M[i] * vector_of_N[i]);
		x %= production_of_modulos;
		std::cout << vector_of_remainders[i] << '*' << vector_of_M[i] << '*' << vector_of_N[i] << ((i != vector_of_modulos.size() - 1) ? " + " : ") mod ");
	}
	std::cout << production_of_modulos << '\n';
	return ((x < 0) ? (x + production_of_modulos) : (x % production_of_modulos));
}