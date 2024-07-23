// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Neutron class header file

#ifndef NEUTRON_H
#define NEUTRON_H

#include<iostream>
#include<vector>
#include"calorimeter_particle.h"

class neutron: public calorimeter_particle
{
public:
	// Constructors
	neutron() // Default
	: calorimeter_particle{} {}
	neutron(double energy); // Parameterized
	neutron(const neutron& input) // Copy
	: calorimeter_particle{input} {}
	neutron(neutron&& input) // Move
	: calorimeter_particle{std::move(input)} {}
	// Destructor
	~neutron() {}
	// Print data
	void print_data();
};

#endif