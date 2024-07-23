// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Electron class header file

#ifndef ELECTRON_H
#define ELECTRON_H

#include<iostream>
#include<vector>
#include"calorimeter_particle.h"

class electron: public calorimeter_particle
{
public:
	// Constructors
	electron() // Default
	: calorimeter_particle{} {}
	electron(bool is_anti, double energy); // Parameterized
	electron(const electron& input) // Copy
	: calorimeter_particle{input} {}
	electron(electron&& input) // Move
	: calorimeter_particle{std::move(input)} {}
	// Destructor
	~electron() {}
	// Print data
	void print_data();
};

#endif