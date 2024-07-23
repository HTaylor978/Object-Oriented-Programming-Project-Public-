// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Tau class header file

#ifndef TAU_H
#define TAU_H

#include<iostream>
#include<memory>
#include<vector>
#include"particle.h"

enum class decay_type
{
  None,
  leptonic,
  hadronic
};

class tau: public particle
{
private:
	decay_type type;
  std::vector<std::shared_ptr<particle>> decay_products; 
public:
	// Constructors
	tau() // Default
	: particle{}, type(decay_type::None), decay_products(std::vector<std::shared_ptr<particle>> (1, nullptr)) {}
	tau(bool is_anti, double energy, decay_type t); // Parameterized
  tau(const tau&); // Copy
	tau(tau&&); // Move
  // Destructor
  ~tau() {}
	// Setters
	void set_decay_type(decay_type); // Affects decay products
	// Getters
	decay_type get_decay_type() const {return type;}
	std::vector<std::shared_ptr<particle>> get_decay_products() const {return decay_products;}
  // Operators
  tau & operator=(const tau&); // Copy
	tau & operator=(tau&&); // Move
	// Print data
	void print_data();
};

#endif