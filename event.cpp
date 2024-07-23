// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Event class member function implementation

#include<iostream>
#include<memory>
#include<vector>
#include"event.h"
#include"electron.h"
#include"muon.h"
#include"tau.h"
#include"neutrino.h"
#include"proton.h"
#include"neutron.h"
#include"photon.h"

// Parameterized constructor 
event::event(double energy, std::vector<particle_type> event_particles)
: total_energy(energy), input_particle_types(event_particles)
{
  // Assign all values to the particle map, where each index of the map will be
  // a particle type, and it will take an energy as an input, as to allow random
  // energies to be assigned using lambda functions
  particle_map[particle_type::electron] = [](double input) {return std::make_shared<electron>(false, input);};
  particle_map[particle_type::antielectron] = [](double input) {return std::make_shared<electron>(true, input);};
  particle_map[particle_type::electron_neutrino] = [](double input) {return std::make_shared<neutrino>(flavour::electron, false, input);};
  particle_map[particle_type::electron_antineutrino] = [](double input) {return std::make_shared<neutrino>(flavour::electron, true, input);};
  particle_map[particle_type::muon] = [](double input) {return std::make_shared<muon>(false, input);};
  particle_map[particle_type::antimuon] = [](double input) {return std::make_shared<muon>(true, input);};
  particle_map[particle_type::muon_neutrino] = [](double input) {return std::make_shared<neutrino>(flavour::muon, false, input);};
  particle_map[particle_type::muon_antineutrino] = [](double input) {return std::make_shared<neutrino>(flavour::muon, true, input);};
  particle_map[particle_type::leptonic_tau] = [](double input) {return std::make_shared<tau>(false, input, decay_type::leptonic);};
  particle_map[particle_type::hadronic_tau] = [](double input) {return std::make_shared<tau>(false, input, decay_type::hadronic);};
  particle_map[particle_type::leptonic_antitau] = [](double input) {return std::make_shared<tau>(true, input, decay_type::leptonic);};
  particle_map[particle_type::hadronic_antitau] = [](double input) {return std::make_shared<tau>(true, input, decay_type::hadronic);};
  particle_map[particle_type::tau_neutrino] = [](double input) {return std::make_shared<neutrino>(flavour::tau, false, input);};
  particle_map[particle_type::tau_antineutrino] = [](double input) {return std::make_shared<neutrino>(flavour::tau, true, input);};
  particle_map[particle_type::proton] = [](double input) {return std::make_shared<proton>(false, input);};
  particle_map[particle_type::antiproton] = [](double input) {return std::make_shared<proton>(true, input);};
  particle_map[particle_type::neutron] = [](double input) {return std::make_shared<neutron>(input);};
  particle_map[particle_type::photon] = [](double input) {return std::make_shared<photon>(input);};

  // Use random numbers to generate the particles energies
  int n = event_particles.size();
  std::vector<double> initial_energies = generate_energies(total_energy, n);
  for(int i{}; i < n; i++)
  {
    auto it = particle_map.find(event_particles[i]);
    if (it != particle_map.end())
      particles.push_back(it->second(initial_energies[i]));
  }
}

// Move constructor
event::event(event&& input)
: total_energy(input.get_total_energy()), input_particle_types(input.get_input_particle_types()),
particles(input.get_particles())
{
  // Reset original values
  total_energy = 0;
  input_particle_types = std::vector<particle_type>{particle_type::None};
  particles = std::vector<std::shared_ptr<particle>>{nullptr};
}

// Deep copy assignment operator
event & event::operator=(const event& input)
{
  if(&input != this)
  {
    total_energy = input.get_total_energy();
    input_particle_types = input.get_input_particle_types();
    particles = input.get_particles();
  }
  return *this;
}

// Move assignment operator
event & event::operator=(event&& input)
{
  if(&input != this)
  {
    std::swap(total_energy, input.total_energy);
    std::swap(input_particle_types, input.input_particle_types);
    std::swap(particles, input.particles);
  }
  return *this;
}