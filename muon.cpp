// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Muon member function implementation file

#include<iostream>
#include"muon.h"

// Deep copy constructor
muon::muon(const muon& input)
: particle{input}
{
  has_interacted = input.get_has_interacted();
}

// Move constructor
muon::muon(muon&& input)
: particle(std::move(input)), has_interacted(input.get_has_interacted())
{
  // Reset original values
  has_interacted = std::vector<int>{0};
}

// Deep copy assignment operator
muon & muon::operator=(const muon& input)
{
  if(&input != this)
  {
    particle::operator=(input);
    has_interacted = input.get_has_interacted();
  }
  return *this;
}

// Move assignment operator
muon & muon::operator=(muon&& input)
{
  if(&input != this)
  {
		particle::operator=(std::move(input));
    std::swap(has_interacted, input.has_interacted);    
  }
  return *this;
}

// Print data
void muon::print_data()
{
  if(charge == 1) std::cout<<"Anti-";
	std::cout<<"Muon"<<std::endl;
	particle::print_particle_data();
  std::cout<<"Interacted with Inner Layer of Muon Chamber: ";
  if(has_interacted[0] == true) std::cout<<"True";
  else std::cout<<"False";
  std::cout<<std::endl<<"Interacted with Outer Layer of Muon Chamber: ";
  if(has_interacted[1] == true) std::cout<<"True";
  else std::cout<<"False";
  std::cout<<std::endl;
}