// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Calorimeter class member function implementation

#include<cstdlib>
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include"calorimeter.h"
#include"calorimeter_particle.h"
#include"particle.h"
#include"tau.h"

// Move constructor
calorimeter::calorimeter(calorimeter&& input)
: sub_detector(std::move(input)), deposited_energies(input.get_deposited_energies()),
deposited_in_em(input.get_deposited_in_em()), deposited_in_had(input.get_deposited_in_had()) 
{
  // Reset original values
  deposited_energies = std::vector<double>{0};
  deposited_in_em = std::vector<int>{0};
  deposited_in_had = std::vector<int>{0};
}

// Deep copy assignment operator
calorimeter & calorimeter::operator=(const calorimeter& input)
{
  if(&input != this)
  {
    sub_detector::operator=(input);
    deposited_energies = input.get_deposited_energies();
    deposited_in_em = input.get_deposited_in_em();
    deposited_in_had = input.get_deposited_in_had();
  }
  return *this;
}

// Move assignment operator
calorimeter & calorimeter::operator=(calorimeter&& input)
{
  if(&input != this)
  {
    sub_detector::operator=(std::move(input));
    std::swap(deposited_energies, input.deposited_energies);
    std::swap(deposited_in_em, input.deposited_in_em);
    std::swap(deposited_in_had, input.deposited_in_had);
  }
  return *this;
}

// Use sub detector
void calorimeter::use_sub_detector(std::shared_ptr<particle> input)
{ 
  // Set calorimeter energies to zero
  deposited_energies = {0, 0, 0, 0};

  auto em_ptr = dynamic_cast<calorimeter_particle*>(input.get());
  if(em_ptr)
  {
    double total_energy = input->get_true_energy();
    std::vector<double> true_energies = em_ptr->get_calorimeter_energies();

    // Create random efficiencies for the each layer of the calorimeter
    // and apply the efficiency to the energy deposited in each layer
    for(int i{}; i < true_energies.size(); i++)
    {
      double rand_eff = static_cast<double>(std::rand()) / RAND_MAX;
      deposited_energies[i] = true_energies[i] * rand_eff;
    }
    // Add particle ID and energy detected
    particles_interacted.push_back(input->get_particle_id());
    total_detected_energy.push_back(deposited_energies[0] + deposited_energies[1] +
    deposited_energies[2] + deposited_energies[3]);

    // Add to histories of EM and HAD deposits (used for particle prediction)
    if(deposited_energies[0] + deposited_energies[1] > 0 && deposited_energies[2] + deposited_energies[3] == 0)
    {
      deposited_in_em.push_back(1);
      deposited_in_had.push_back(0);
    } 
    else if(deposited_energies[0] + deposited_energies[1] == 0 && deposited_energies[2] + deposited_energies[3] > 0)
    {
      deposited_in_em.push_back(0);
      deposited_in_had.push_back(1);
    }
    else
    {
      deposited_in_em.push_back(1);
      deposited_in_had.push_back(1);      
    }
  }
  else
  {
    total_detected_energy.push_back(0);
    deposited_in_em.push_back(0);
    deposited_in_had.push_back(0);
  }
}

// Print data
void calorimeter::print_data()
{
  std::cout<<"  Energy Deposited in the Calorimeter: ["<<deposited_energies[0]<<", "<<deposited_energies[1]
  <<", "<<deposited_energies[2]<<", "<<deposited_energies[3]<<"] GeV"<<std::endl;
}