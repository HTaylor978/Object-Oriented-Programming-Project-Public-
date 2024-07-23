// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Calorimeter class header file

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include<iostream>
#include"sub_detector.h"
#include"particle.h"

class calorimeter: public sub_detector
{
private:
	std::vector<double> deposited_energies; // [EM_1, EM_2, HAD_1, HAD_2] GeV
	std::vector<int> deposited_in_em; // History of energy deposits in EM calorimeter
	std::vector<int> deposited_in_had; // History of energy deposits in HAD calorimeter
public:
	// Constructors
	calorimeter() // Deafult
	: sub_detector{}, deposited_energies(std::vector<double> (4,0)) {}
	calorimeter(const calorimeter& input) // Copy
  : sub_detector{input}, deposited_energies(input.get_deposited_energies()),
	deposited_in_em(input.get_deposited_in_em()), deposited_in_had(input.get_deposited_in_had()) {}
	calorimeter(calorimeter&&); // Move
	// Destructor
	~calorimeter() {}
	// Getters
	std::vector<double> get_deposited_energies() const {return deposited_energies;}
	std::vector<int> get_deposited_in_em() const {return deposited_in_em;}
	std::vector<int> get_deposited_in_had() const {return deposited_in_had;}
	// Operators
	calorimeter & operator=(const calorimeter&); // Copy
	calorimeter & operator=(calorimeter&&); // Move
  // Use sub detector
  void use_sub_detector(std::shared_ptr<particle>);
	// Print data
	void print_data();
};

#endif