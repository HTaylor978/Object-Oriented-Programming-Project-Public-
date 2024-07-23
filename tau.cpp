// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Tau member function implementation file
  
#include<iostream>
#include<memory>
#include<vector>
#include"tau.h"
#include"electron.h"
#include"neutrino.h"
#include"proton.h"

// Parameterized constructor
tau::tau(bool is_anti, double energy, decay_type t)
: particle{is_anti, energy}
{
  set_decay_type(t);
}

// Deep copy constructor
tau::tau(const tau& input)
: particle{input}, type(input.get_decay_type()), decay_products(input.get_decay_products()) {}

// Move constructor
tau::tau(tau&& input)
: particle(std::move(input)), type(input.get_decay_type())
{
  // Move decay products
  decay_products = std::move(input.decay_products);

  // Reset original values
  type = decay_type::None;
}

// Decay type setter (sets decay products too)
void tau::set_decay_type(decay_type input)
{ 
  bool is_anti = (charge == -1) ? false : true;
  if(input == decay_type::leptonic)
  {
    type = input;
    // Tau decays to Electron, Electron Anti-Neutrino, Tau Neutrino
    // Charges flipped for Anti-Tau

    // Generate random energies for decay products
    std::vector<double> energies = generate_energies(true_energy, 3);

    // Create decay products and assign random energies
    decay_products.push_back(std::make_shared<electron>(is_anti, energies[0]));
    decay_products.push_back(std::make_shared<neutrino>(flavour::electron, !is_anti, energies[1])); 
    decay_products.push_back(std::make_shared<neutrino>(flavour::tau, is_anti, energies[2])); 
  }
  else if(input == decay_type::hadronic)
  {
    type = input;
    // Tau decays to Tau Anti-Neutrino, Hadronic particles
    // Charges flipped for Anti-Tau
    
    // Generate random energies for calorimeter energies and decay products
    std::vector<double> energies = generate_energies(true_energy, 2);

    // Push tau neutrino into decay products vector
    decay_products.push_back(std::make_shared<neutrino>(flavour::tau, is_anti, energies[0]));

    // Push back dummy proton for a calorimeter energy vector
    decay_products.push_back(std::make_shared<proton>(is_anti, energies[1]));
  }
  else
  {
    type = decay_type::None;
    decay_products = std::vector<std::shared_ptr<particle>> (1, nullptr);
    std::cout<<"Decay Type of particle: "<<particle_id<<" set to 'None' and Decay Products set to '0'"<<std::endl;
  }
}

// Deep copy assignment operator
tau & tau::operator=(const tau& input)
{
  if(&input != this)
  {
    particle::operator=(input);
    type = input.get_decay_type();
    decay_products = input.get_decay_products(); 
  }
  return *this;
}

// Move assignment operator
tau & tau::operator=(tau&& input)
{
  if(&input != this)
  {
    particle::operator=(std::move(input));
    std::swap(type, input.type);
    std::swap(decay_products, input.decay_products);
  }
  return *this;
}

// Print data
void tau::print_data()
{
  if(charge == 1) std::cout<<"Anti-";
	std::cout<<"Tau"<<std::endl;
	particle::print_particle_data();
  std::cout<<"Decay Type: ";
  if(type == decay_type::leptonic)
    std::cout<<"Leptonic";
  else if(type == decay_type::hadronic)
    std::cout<<"Hadronic";
  std::cout<<std::endl;
  std::cout<<"----- Decay Products -----"<<std::endl;
}