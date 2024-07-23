// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Sub detector (abstract) class header file

#ifndef SUB_DETECTOR_H
#define SUB_DETECTOR_H

#include<iostream>
#include<memory>
#include<vector>
#include"particle.h"

class sub_detector
{
protected:
	std::vector<double> total_detected_energy;
  std::vector<int> particles_interacted;
public:
	// Constructors
	sub_detector() {} // Default
	sub_detector(const sub_detector& input) // Copy
	: total_detected_energy(input.get_total_detected_energy()),
	particles_interacted(input.get_particles_interacted()) {}
	sub_detector(sub_detector&&); // Move
	// Destructor
	~sub_detector() {}
	// Getters
	std::vector<double> get_total_detected_energy() const {return total_detected_energy;}
  std::vector<int> get_particles_interacted() const {return particles_interacted;}
	// Operators
	sub_detector & operator=(const sub_detector&); // Copy
	sub_detector & operator=(sub_detector&&); // Move
  // Use detector
  virtual void use_sub_detector(std::shared_ptr<particle>);
	// Print data
	virtual void print_data() = 0;
};

#endif