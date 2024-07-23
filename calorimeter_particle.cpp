// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Calorimeter particles class member function implementation

#include<iostream>
#include<vector>
#include"particle.h"
#include"calorimeter_particle.h"

// Parameterized constructor
calorimeter_particle::calorimeter_particle(bool is_anti, double energy)
: particle{is_anti, energy} {}

// Deep copy constructor
calorimeter_particle::calorimeter_particle(const calorimeter_particle& input)
: particle{input}
{
	calorimeter_energies = input.get_calorimeter_energies();
}

// Move constcuctor
calorimeter_particle::calorimeter_particle(calorimeter_particle&& input)
:	particle(std::move(input)), calorimeter_energies(input.get_calorimeter_energies())
{
	// Reset values to 0
	calorimeter_energies = {0, 0, 0, 0};
}

// Calorimeter energies setter
void calorimeter_particle::set_calorimeter_energies(const std::string layers, const double total_energy)
{
	// Layers input variable determines where the energy can be deposited
	// Can either be "EM", "HAD" or "BOTH" (HAD is never used but implemented for completeness)
	std::vector<double> energies;
	if(layers == "EM")
	{
		// [EM_1, EM_2, 0, 0]
		energies = generate_energies(total_energy, 2);
		energies.push_back(0); energies.push_back(0);
	}
	else if(layers == "HAD")
	{
		// [0, 0, HAD_1, HAD_2]
		energies = generate_energies(total_energy, 2);
		energies.insert(energies.begin(), 0); energies.insert(energies.begin(), 0);
	}
	else if(layers == "BOTH")
	{
		// [EM_1, EM_2, HAD_1, HAD_2]
		energies = generate_energies(total_energy, 4);	
	}
	else 
	{
		energies = {0,0,0,0};
		std::cout<<"The Calorimeter Energies of Particle: "<<particle_id<<" Have Been Set to '0'"<<std::endl;
	}
	for(int i{}; i < energies.size(); i++)
		calorimeter_energies.push_back(energies[i]);
}

// Deep copy assignment operator
calorimeter_particle & calorimeter_particle::operator=(calorimeter_particle& input)
{
	if(&input != this)
	{	
		particle::operator=(input);
		calorimeter_energies = input.get_calorimeter_energies();
	}
	return *this;
}

// Move assignment operator
calorimeter_particle & calorimeter_particle::operator=(calorimeter_particle&& input)
{
	if(&input != this)
	{
		particle::operator=(std::move(input));
		std::swap(calorimeter_energies, input.calorimeter_energies);
	}
	return *this;
}

// Print data
void calorimeter_particle::print_calorimeter_particle_data()
{
	particle::print_particle_data();
	std::cout<<"Possible Energy Deposited in Calorimeter: ["<<calorimeter_energies[0]<<", "
	<<calorimeter_energies[1]<<", "<<calorimeter_energies[2]<<", "<<calorimeter_energies[3]<<"] GeV"<<std::endl;
}
