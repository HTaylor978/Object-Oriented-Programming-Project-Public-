// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Tracker class header file

#ifndef TRACKER_H
#define TRACKER_H

#include<iostream>
#include"bool_detector.h"
#include"particle.h"

class tracker: public bool_detector
{
public:
	// Constructors
	tracker() // Deafult
	: bool_detector{3} {} // Tracker has 3 detection layers
	tracker(const tracker& input) // Copy
	: bool_detector{input} {}
	tracker(tracker&& input) // Move
	: bool_detector(std::move(input)) {}
	// Destructor
	~tracker() {}
  // Use sub detector
  void use_sub_detector(std::shared_ptr<particle>);
	// Print data
	void print_data();
};

#endif