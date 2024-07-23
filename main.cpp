// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Main

#include<ctime>
#include<iostream>
#include<vector>
#include"detector.h"
#include"sub_detector.h"
#include"tracker.h"
#include"calorimeter.h"
#include"muon_chamber.h"
#include"particle.h"
#include"calorimeter_particle.h"
#include"electron.h"
#include"muon.h"
#include"tau.h"
#include"neutrino.h"
#include"photon.h"
#include"proton.h"
#include"neutron.h"
#include"event.h"

// Compile line
// g++ -std=gnu++17 -g bool_detector.cpp calorimeter_particle.cpp calorimeter.cpp detector.cpp electron.cpp event.cpp main.cpp muon_chamber.cpp muon.cpp neutrino.cpp neutron.cpp particle.cpp photon.cpp proton.cpp sub_detector.cpp tau.cpp tracker.cpp -o project.exe

int main()
{ 
  // Seed random number gen
  std::srand(std::time(nullptr));
  
  // Instantiate detector with one of each sub detector
  std::vector<sub_detector_type> sub_detectors;
  sub_detectors.push_back(sub_detector_type::tracker);
  sub_detectors.push_back(sub_detector_type::calorimeter);
  sub_detectors.push_back(sub_detector_type::muon_chamber);
	detector lhc_detector(sub_detectors);

  // Instantiate events
  // Event 1 (2 photons, 125 GeV total)
  std::vector<particle_type> event_1_particles;
  double event_1_energy = 125; // GeV
  event_1_particles.push_back(particle_type::photon);
  event_1_particles.push_back(particle_type::photon);
  event event1(event_1_energy, event_1_particles);

  // Event 2 (1 neutron, 1 photon, 1 proton, 1500 GeV)
  std::vector<particle_type> event_2_particles;
  double event_2_energy = 1500; // GeV
  event_2_particles.push_back(particle_type::neutron);
  event_2_particles.push_back(particle_type::photon);
  event_2_particles.push_back(particle_type::proton);
  event event2(1500, event_2_particles);

  // Event 3 (1 tau [hadronic], 1 anti-tau [leptonic], 1500 GeV)
  std::vector<particle_type> event_3_particles;
  double event_3_energy = 1500; // GeV
  event_3_particles.push_back(particle_type::hadronic_tau);
  event_3_particles.push_back(particle_type::leptonic_antitau);
  event event3(event_3_energy, event_3_particles);

  // Event 4 (1 proton, 1 neutrino, 1 anti-neutrino, 1500 GeV [electron neutrinos])
  std::vector<particle_type> event_4_particles;
  double event_4_energy = 1500; // GeV
  event_4_particles.push_back(particle_type::proton);
  event_4_particles.push_back(particle_type::electron_neutrino);
  event_4_particles.push_back(particle_type::electron_antineutrino);
  event event4(event_4_energy, event_4_particles);

  // Event 5 (1 proton, 1 electron, 1 muon, 1000 GeV)
  std::vector<particle_type> event_5_particles;
  double event_5_energy = 1000; // GeV
  event_5_particles.push_back(particle_type::proton);
  event_5_particles.push_back(particle_type::electron);
  event_5_particles.push_back(particle_type::muon);
  event event5(event_5_energy, event_5_particles);

  // Add all events to a vector
  std::vector<event> events{event1, event2, event3, event4, event5};

  // Run each event into the detector
  for(auto it{events.begin()}; it != events.end(); it++)
    lhc_detector.use_detector(*it);

  // Print data about all events
  lhc_detector.print_total_data();
  return 0;
}