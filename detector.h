// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Detector class header file

#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<memory>
#include<vector>
#include"detector.h"
#include"sub_detector.h"
#include"particle.h"
#include"event.h"

enum class sub_detector_type
{
  tracker,
  calorimeter,
  muon_chamber
};


class detector
{
private:
  static int event_count;
  std::map<sub_detector_type, std::function<std::shared_ptr<sub_detector>()>> sub_detector_map;
  std::vector<std::shared_ptr<sub_detector>> sub_detectors;
public:
  // Constructors
  detector() {} // Default
  detector(std::vector<sub_detector_type>); // Parameterized
  detector(const detector& input) // Copy
  : sub_detectors(input.get_sub_detectors()) {}
  detector(detector&&); // Move
  // Destructor
  ~detector() {}
  // Getters
  std::vector<std::shared_ptr<sub_detector>> get_sub_detectors() const {return sub_detectors;}
  // Operators
  detector & operator=(const detector&); // Copy
  detector & operator=(detector&&); // Move
  // Use detector
  void use_detector(event);
  void predict_particles(event);
  void detected_by_sub_detectors(int, int, std::vector<int>, std::vector<std::vector<int>>&, double&); // used in prediction
  // Print data
  void print_detector_config(std::vector<sub_detector_type>); // Prints which sub detectors are in detector
  void print_detected_data(std::shared_ptr<particle>); // Prints the data found after detector has been used
  void print_event_data(double, double); // Prints invisible energy and energy efficiency
  void print_total_data(); // Prints all data for all events
  // Friend functions
};

#endif