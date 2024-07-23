// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Tracker class member function implementation

#include<iostream>
#include<memory>
#include<typeinfo>
#include<vector>
#include"muon_chamber.h"
#include"bool_detector.h"
#include"particle.h"
#include"muon.h"

// Use sub detector
void muon_chamber::use_sub_detector(std::shared_ptr<particle> input)
{ 
  detection_layers = {0, 0};
  // Muon chambers only interact with muons
  auto muon_ptr = dynamic_cast<muon*>(input.get());
  if(muon_ptr)
  { 
    set_detection_layers();
    
    // Set input muon data members
    muon_ptr->set_inner_layer_interaction(detection_layers[0]);
    muon_ptr->set_outer_layer_interaction(detection_layers[1]);

    // Check at least 2 are true
    if(detection_layers[0] + detection_layers[1] >= 1)
      sub_detector::use_sub_detector(input);
    else
      total_detected_energy.push_back(0);
  }
  else
    total_detected_energy.push_back(0);
}

// Print data
void muon_chamber::print_data()
{
  std::cout<<"  Particle Detected by Muon Chamber: ";
  if(detection_layers[0] + detection_layers[1] >= 1)
    std::cout<<"True";
  else std::cout<<"False";
  std::cout<<std::endl;
}