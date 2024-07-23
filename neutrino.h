// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Neutrino class header file

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<iostream>
#include"particle.h"

enum class flavour
{
  None,
  electron,
  muon,
  tau
};

class neutrino: public particle
{
private:
  flavour flav;
  bool anti;
  bool has_interacted;
public:
	// Constructors
	neutrino(flavour f); // Default
	neutrino(flavour f, bool is_anti, double energy); // Parameterized
  neutrino(const neutrino&); // Copy
  neutrino(neutrino&&); // Move
	// Destructor
	~neutrino() {}
	// Setters
  void set_flavour(const flavour input);
  void set_anti(const bool input) {anti = input;}
  void set_has_interacted(const bool input) {has_interacted = input;}
	// Getters
  flavour get_flavour() const {return flav;}
  bool get_anti() const {return anti;}
	bool get_has_interacted() const {return has_interacted;}
  // Operators
  neutrino & operator=(const neutrino&); // Copy
  neutrino & operator=(neutrino&&); // Move
	// Print data
	void print_data();
};

#endif