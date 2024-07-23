// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Calorimeter particle class header file
// For particles that deposit energy in calorimeter layers

#ifndef CALORIMETER_PARTICLES_H
#define CALORIMETER_PARTICLES_H

#include<iostream>
#include<vector>
#include"particle.h"

// Abstract base class for particles that deposit energy in the calorimeter
class calorimeter_particle: public particle
{
protected:
	std::vector<double> calorimeter_energies; // [EM_1, EM_2, HAD_1, HAD_2] GeV
public:
	// Constructors
	calorimeter_particle() // Default
	: particle{}, calorimeter_energies(std::vector<double> (4,0)) {}
	calorimeter_particle(bool is_anti, double energy); // Parameterized
	calorimeter_particle(double energy) // Parameterized for particles without anti-particles
	: particle{energy} {}
	calorimeter_particle(const calorimeter_particle&); // Copy
	calorimeter_particle(calorimeter_particle&&); // Move
	// Destructor
	~calorimeter_particle() {}
	// Setters
	void set_calorimeter_energies(const std::string, const double);
	// Getters
	std::vector<double> get_calorimeter_energies() const {return calorimeter_energies;}
	double get_em1() const {return calorimeter_energies[0];}
	double get_em2() const {return calorimeter_energies[1];}
	double get_had1() const {return calorimeter_energies[2];}
	double get_had2() const {return calorimeter_energies[3];}
	// Operators
  calorimeter_particle & operator=(calorimeter_particle&); // Copy
	calorimeter_particle & operator=(calorimeter_particle&&); // Move
	// Print data
	virtual void print_data() = 0;
	void print_calorimeter_particle_data();
};

std::vector<double> generate_energies(double, int);

#endif