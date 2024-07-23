// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Bool detector (abstract) class header file

#ifndef BOOL_DETECTOR_H
#define BOOL_DETECTOR_H

#include<iostream>
#include<memory>
#include<vector>
#include"sub_detector.h"
#include"particle.h"

class bool_detector: public sub_detector
{
protected:
  std::vector<int> detection_layers;
public:
	// Constructors
  bool_detector() {} // Default
	bool_detector(int n) // Parameterized
	: sub_detector{}, detection_layers(std::vector<int> (n, 0)) {}
	bool_detector(const bool_detector& input) // Copy
	: sub_detector{input}, detection_layers(input.get_detection_layers()) {}
	bool_detector(bool_detector&&); // Move
	// Destructor
	~bool_detector() {}
  // Setters
  void set_detection_layers();
	// Getters
	std::vector<int> get_detection_layers() const {return detection_layers;}
	// Operators
	bool_detector & operator=(const bool_detector&); // Copy
	bool_detector & operator=(bool_detector&&); // Move
  // Use detector
  void use_sub_detector(std::shared_ptr<particle>) {}
	// Print data
	virtual void print_data() = 0;
};

#endif