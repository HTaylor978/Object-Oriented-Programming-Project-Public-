// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Muon Chamber class header file

#ifndef MUON_CHAMBER_H
#define MUON_CHAMBER_H

#include<iostream>
#include"bool_detector.h"
#include"particle.h"

class muon_chamber: public bool_detector
{
public:
	// Constructors
	muon_chamber() // Deafult
	: bool_detector{2} {} // Muon chamber has 2 detection layers
	muon_chamber(const muon_chamber& input) // Copy
	: bool_detector{input} {}
	muon_chamber(muon_chamber&& input) // Move
	: bool_detector(std::move(input)) {}
	// Destructor
	~muon_chamber() {}
  // Use sub detector
  void use_sub_detector(std::shared_ptr<particle>);
	// Print data
	void print_data();
};

#endif