// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Proton class header file

#ifndef PROTON_H
#define PROTON_H

#include<iostream>
#include<vector>
#include"calorimeter_particle.h"

class proton: public calorimeter_particle
{
public:
	// Constructors
	proton() // Default
	: calorimeter_particle{} {}
	proton(bool is_anti, double energy); // Parameterized
	proton(const proton& input) // Copy
	: calorimeter_particle{input} {}
	proton(proton&& input) // Move
	: calorimeter_particle{std::move(input)} {}
	// Destructor
	~proton() {}
	// Print data
	void print_data();
};

#endif