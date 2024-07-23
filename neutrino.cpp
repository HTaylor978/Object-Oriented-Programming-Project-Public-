// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Neutrino member function implementation file

#include<iostream>
#include"neutrino.h"

// Default constructor
neutrino::neutrino(flavour f)
: particle{}, anti(false), has_interacted(false)
{
  set_flavour(f);
}

// Parameterized constructor
neutrino::neutrino(flavour f, bool is_anti, double energy)
: particle{energy}, anti(is_anti), has_interacted(false)
{
  set_flavour(f);
}

// Deep copy constructor
neutrino::neutrino(const neutrino& input)
: particle{input}, flav(input.get_flavour()), anti(input.get_anti()),
has_interacted(input.get_has_interacted()) {}

// Move constructor
neutrino::neutrino(neutrino&& input)
: particle(std::move(input)), flav(input.get_flavour()), anti(input.get_anti()),
has_interacted(input.get_has_interacted())
{
  // Reset original values
  flav = flavour::None;
  anti = false;
  has_interacted = false;
}

// Flavour setter
void neutrino::set_flavour(const flavour input)
{
  if(input == flavour::electron || input == flavour::muon || input == flavour::tau)
    flav = input;
  else
  {
    flav = flavour::None;
    std::cout<<"Flavour of particle: "<<particle_id<<" set to 'None'"<<std::endl;
  }
}

// Deep copy assignment operator
neutrino & neutrino::operator=(const neutrino& input)
{
  if(&input != this)
  {
    particle::operator=(input);
    flav = input.get_flavour();
    anti = input.get_anti();
    has_interacted = input.get_has_interacted();  
  }
  return *this;
}

// Move assignment operator
neutrino & neutrino::operator=(neutrino&& input)
{
  if(&input != this)
  {
    particle::operator=(std::move(input));
    std::swap(flav, input.flav);
    std::swap(anti, input.anti);
    std::swap(has_interacted, input.has_interacted);
  }
  return *this;
}

// Print data
void neutrino::print_data()
{
  switch(flav)
  {
    case flavour::electron:
      std::cout<<"Electron ";
      break;
    case flavour::muon:
      std::cout<<"Muon ";
      break;
    case flavour::tau:
      std::cout<<"Tau ";
      break;
  }
  if(anti) std::cout<<"Anti-";
	std::cout<<"Neutrino"<<std::endl;
	particle::print_particle_data();
  std::cout<<"Has Interacted: ";
  if(has_interacted == true) std::cout<<"True";
  else std::cout<<"False";
  std::cout<<std::endl;
}