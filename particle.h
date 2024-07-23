// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Particle (abstract) class header file

#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<vector>

class particle
{
protected:
	static int next_particle_id; // Will be incremented each time a class is instantiated
	int particle_id; // Keeps track of which particle is in the simulation
	int charge; // e
	double true_energy; // GeV
public:
	// Constructors
	particle() // Default
	: particle_id(-1), charge(0), true_energy(0) {}
	particle(bool is_anti, double energy); // Parameterized
	particle(double energy); // Parameterized for particles without anti-particles
	particle(const particle&); // Copy
	particle(particle&&); // Move
	// Destructor
	~particle() {}
	//Setters
	void set_true_energy(const double);
	// Getters
	int get_particle_id() const {return particle_id;}
  int get_charge() const {return charge;}
	double get_true_energy() const {return true_energy;}
	// Validation
	bool validate_true_energy(double);
	// Operators
	particle & operator=(const particle&); // Copy
	particle & operator=(particle&&); // Move
	// Printing function
  virtual void print_data() = 0;
	void print_particle_data();
};

std::vector<double> generate_energies(double, int);

#endif