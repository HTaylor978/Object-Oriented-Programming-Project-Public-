// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Tracker class member function implementation

#include<iostream>
#include<memory>
#include<vector>
#include"tracker.h"
#include"bool_detector.h"
#include"particle.h"
#include"tau.h"

// Use sub detector
void tracker::use_sub_detector(std::shared_ptr<particle> input)
{ 
  detection_layers = {0, 0, 0};

  // Trackers only interact with charged particles
  if(input->get_charge() != 0)
  { 
    set_detection_layers();

    // Check at least 2 are true
    if(detection_layers[0] + detection_layers[1] + detection_layers[2] >= 2)
      sub_detector::use_sub_detector(input);
    else
      total_detected_energy.push_back(0);
  }
  else
    total_detected_energy.push_back(0);
}

// Print data
void tracker::print_data()
{
  std::cout<<"  Particle Detected by Tracker: ";
  if(detection_layers[0] + detection_layers[1] + detection_layers[2] >= 2)
    std::cout<<"True";
  else std::cout<<"False";
  std::cout<<std::endl;
}