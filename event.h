// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Event class header file

#ifndef EVENT_H
#define EVENT_H

#include<iostream>
#include<functional>
#include<map>
#include<memory>
#include<vector>
#include"particle.h"

// Enumerator class containing all possible particles
enum class particle_type
{
  electron,
  antielectron,
  electron_neutrino,
  electron_antineutrino,
  muon,
  antimuon,
  muon_neutrino,
  muon_antineutrino,
  leptonic_tau,
  hadronic_tau,
  leptonic_antitau,
  hadronic_antitau,
  tau_neutrino,
  tau_antineutrino,
  proton,
  antiproton,
  neutron,
  photon,
  None,
};

class event
{
private:
  std::map<particle_type, std::function<std::shared_ptr<particle>(double)>> particle_map;
  double total_energy;
  std::vector<particle_type> input_particle_types;
  std::vector<std::shared_ptr<particle>> particles;
public:
  // Constructors
  event() // Default
  : total_energy(0), particles(std::vector<std::shared_ptr<particle>>{nullptr}) {}
  event(double energy, std::vector<particle_type> event_particles); // Parameterized
  event(const event& input) // Copy
  : total_energy(input.get_total_energy()), input_particle_types(input.get_input_particle_types()),
  particles(input.get_particles()) {}
  event(event&&); // Move
  // Destructor
  ~event() {}
  // Getters
  double get_total_energy() const {return total_energy;}
  std::vector<particle_type> get_input_particle_types() const {return input_particle_types;}
  std::vector<std::shared_ptr<particle>> get_particles() const {return particles;}
  // Operators
  event & operator=(const event&); // Copy
  event & operator=(event&&); // Move
};

#endif