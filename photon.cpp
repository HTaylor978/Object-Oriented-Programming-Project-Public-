// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Photon class member function implementation

#include<iostream>
#include"photon.h"

// Parameterized constructor
photon::photon(double energy)
: calorimeter_particle{energy}
{
	set_calorimeter_energies("EM", energy);
}

// Print data
void photon::print_data()
{
	std::cout<<"Photon"<<std::endl;
	calorimeter_particle::print_calorimeter_particle_data();
}