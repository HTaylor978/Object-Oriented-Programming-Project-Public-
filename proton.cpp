// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Proton class member function implementation

#include<iostream>
#include"proton.h"

// Parameterized constructor
proton::proton(bool is_anti, double energy)
: calorimeter_particle{is_anti, energy}
{ 
  // Invert charge as a proton has a negative anti-particle
	set_calorimeter_energies("BOTH", energy);
  charge *= -1;
}

// Print data
void proton::print_data()
{
	if(charge == -1) std::cout<<"Anti-";
	std::cout<<"Proton"<<std::endl;
	calorimeter_particle::print_calorimeter_particle_data();
}