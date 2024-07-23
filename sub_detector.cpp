// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Sub detector (abstract) class member function implementation

#include<cstdlib>
#include<iostream>
#include<memory>
#include<random>
#include<vector>
#include"sub_detector.h"
#include"particle.h"

// Move constructor
sub_detector::sub_detector(sub_detector&& input)
: total_detected_energy(input.get_total_detected_energy()), particles_interacted(input.get_particles_interacted())
{
  // Reset original values
  total_detected_energy = std::vector<double>{0};
  particles_interacted = std::vector<int>{0};
}

// Deep copy assignment operator
sub_detector & sub_detector::operator=(const sub_detector& input)
{
  if(&input != this)
  {
    total_detected_energy = input.get_total_detected_energy();
  }
  return *this;
}

// Move assignment operator
sub_detector & sub_detector::operator=(sub_detector&& input)
{
  if(&input != this)
  {
    std::swap(total_detected_energy, input.total_detected_energy);
    std::swap(particles_interacted, input.particles_interacted);
  }
  return *this;
}

// Use sub detector
void sub_detector::use_sub_detector(std::shared_ptr<particle> input)
{
  // Add ID detected particle
  particles_interacted.push_back(input->get_particle_id());
  // Add energy of detected particle (multiplied by some detector efficiency)
  double detected_energy = input->get_true_energy() * (static_cast<double>(std::rand()) / RAND_MAX);
  total_detected_energy.push_back(detected_energy);
}