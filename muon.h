// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Muon class header file

#ifndef MUON_H
#define MUON_H

#include<iostream>
#include<vector>
#include"particle.h"

class muon: public particle
{
private:
	std::vector<int> has_interacted; // [0] is inner muon chamber, [1] is outer muon chamber
public:
	// Constructors
	muon() // Default
	: particle{}, has_interacted(std::vector<int> (2,0)) {}
	muon(bool is_anti, double energy) // Parameterized
  : particle{is_anti, energy}, has_interacted(std::vector<int> (2,0)) {}
  muon(const muon&); // Copy
	muon(muon&&); // Move
	// Destructor
	~muon() {}
	// Setters
	void set_inner_layer_interaction(const bool input) {has_interacted[0] = input;}
  void set_outer_layer_interaction(const bool input) {has_interacted[1] = input;}
	// Getters
	std::vector<int> get_has_interacted() const {return has_interacted;}
	double get_tracker_interaction() const {return has_interacted[0];}
  double get_muon_chamber_interaction() const {return has_interacted[1];}
  // Operators
  muon & operator=(const muon&); // Copy
	muon & operator=(muon&&); // Move
	// Print data
	void print_data();
};

#endif