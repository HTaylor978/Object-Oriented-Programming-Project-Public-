// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Photon class header file

#ifndef PHOTON_H
#define PHOTON_H

#include<iostream>
#include<vector>
#include"calorimeter_particle.h"

class photon: public calorimeter_particle
{
public:
	// Constructors
	photon() // Default
	: calorimeter_particle{} {}
	photon(double energy); // Parameterized
	photon(const photon& input) // Copy
	: calorimeter_particle{input} {}
	photon(photon&& input) // Move
	: calorimeter_particle{std::move(input)} {}
	// Destructor
	~photon() {}
	// Print data
	void print_data();
};

#endif