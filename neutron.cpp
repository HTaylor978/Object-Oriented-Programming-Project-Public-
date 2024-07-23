// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Neutron class member function implementation

#include<iostream>
#include"neutron.h"

// Parameterized constructor
neutron::neutron(double energy)
: calorimeter_particle{energy}
{
	set_calorimeter_energies("BOTH", energy);
}

// Print data
void neutron::print_data()
{
	std::cout<<"Neutron"<<std::endl;
	calorimeter_particle::print_calorimeter_particle_data();
}