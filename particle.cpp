// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Particle (abstract) member function implementation file

#include<algorithm>
#include<iostream>
#include<random>
#include<vector>
#include"particle.h"

// Define and initialize the static data member
int particle::next_particle_id = 0;

// Parameterized constructor
particle::particle(bool is_anti, double energy)
: particle_id(next_particle_id++)
{
	if(is_anti) charge = 1;
	else charge = -1;;
	set_true_energy(energy);
}

// Parameterized constructor (for particles without antiparticles)
particle::particle(double energy)
: particle_id(next_particle_id++)
{
	charge = 0;
	set_true_energy(energy);
}

// Deep copy constructor
particle::particle(const particle& input)
: charge(input.charge), true_energy(input.true_energy), particle_id(next_particle_id++) {}

// Move constructor
particle::particle(particle&& input)
: particle_id(input.get_particle_id()), charge(input.get_charge()), true_energy(input.get_true_energy()) 
{
	// Reset original values
	particle_id = 0;
	charge = 0;
	true_energy = 0;
}

// True energy setter
void particle::set_true_energy(const double input)
{
	if(validate_true_energy(input)) true_energy = input;
	else
	{
		true_energy = 0;
		std::cout<<"True energy of particle: "<<particle_id<<" set to '0'"<<std::endl;
	}
}

// True energy validation
bool particle::validate_true_energy(double input)
{
	if(input >= 0)
		return true;
	return false;
}

// Deep copy assignment operator
particle & particle::operator=(const particle& input)
{
	if(&input != this)
	{	
		// Increment ID
		particle_id = next_particle_id++;

		charge = input.get_charge();
		true_energy = input.get_true_energy();
	}
	return *this;
}

// Move assignment operator
particle & particle::operator=(particle&& input)
{
	if(&input != this)
	{
		std::swap(particle_id, input.particle_id);
		std::swap(charge, input.charge);
		std::swap(true_energy, input.true_energy);
	}
	return *this;
}

// Print data
void particle::print_particle_data()
{
	std::cout.precision(3);
	std::cout<<"ID: "<<particle_id<<", ";
  std::cout<<"Charge: "<<charge<<", ";
  std::cout<<"True Energy: "<<true_energy<<" GeV, "<<std::endl;
}

// Random energy generator
std::vector<double> generate_energies(double energy, int num)
{
	std::vector<double> output (num, 0);
	double sum{};
	for(int i{}; i < num; i++)
	{
		double rand_num = static_cast<double>(std::rand());
		output[i] = rand_num;
		sum += output[i];
	}

	// Normalize the numbers to ensure their sum equals 1
	for (int i = 0; i < num; i++)
	{	
		output[i] /= sum;
		output[i] *= energy;
	}
	return output;
}