// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Electron class member function implementation

#include<iostream>
#include"electron.h"

// Parameterized constructor
electron::electron(bool is_anti, double energy)
: calorimeter_particle{is_anti, energy}
{
	set_calorimeter_energies("EM", energy);
}

// Print data
void electron::print_data()
{	
	if(charge == 1) std::cout<<"Anti-";
	std::cout<<"Electron"<<std::endl;
	calorimeter_particle::print_calorimeter_particle_data();
}