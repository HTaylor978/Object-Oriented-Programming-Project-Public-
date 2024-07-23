// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Detector class member function implementation

#include<iostream>
#include<memory>
#include<vector>
#include"detector.h"
#include"sub_detector.h"
#include"tracker.h"
#include"calorimeter.h"
#include"muon_chamber.h"
#include"particle.h"
#include"tau.h"

// Define and initialize the static data member
int detector::event_count = 1;

// Parameterized constructor
detector::detector(std::vector<sub_detector_type> input)
{
  sub_detector_map[sub_detector_type::tracker] = []() {return std::make_shared<tracker>();};
  sub_detector_map[sub_detector_type::calorimeter] = []() {return std::make_shared<calorimeter>();};
  sub_detector_map[sub_detector_type::muon_chamber] = []() {return std::make_shared<muon_chamber>();};

  // Generate all the input sub detectors
  for(int i{}; i < input.size(); i++)
  {
    auto it = sub_detector_map.find(input[i]);
    if (it != sub_detector_map.end())
      sub_detectors.push_back(it->second());
  }
  print_detector_config(input);
}

// Move constructor
detector::detector(detector&& input)
: sub_detectors(input.get_sub_detectors())
{
  // Reset original values
  sub_detectors = std::vector<std::shared_ptr<sub_detector>>{nullptr};
}

// Deep copy assignment operator
detector & detector::operator=(const detector& input)
{
  if(&input != this)
  {
    sub_detectors = input.get_sub_detectors();
  }
  return *this;
}

// Move assignment operator
detector & detector::operator=(detector&& input)
{
  if(&input != this)
  {
    std::swap(sub_detectors, input.sub_detectors);
  }
  return *this;
} 

// Use detector
void detector::use_detector(event input)
{
  std::vector<std::shared_ptr<particle>> particles = input.get_particles();
  std::cout<<"Event "<<event_count++<<":"<<std::endl<<std::endl;

  // For each particle in the event, run it through each sub detector until it has gone through each of them.
  // Then move onto the next particle in the event and repeat until all particles have been run through
  // the detector
  for(auto particle_it{particles.begin()}; particle_it != particles.end(); particle_it++)
  {
    for(auto sub_detect_it{sub_detectors.begin()}; sub_detect_it != sub_detectors.end(); sub_detect_it++)
      (*sub_detect_it)->use_sub_detector(*particle_it);

    // Special case (tau)
    auto tau_ptr = dynamic_cast<tau*>((*particle_it).get());
    if(!tau_ptr)
    {
      print_detected_data(*particle_it);
      std::cout<<std::endl;
    }
    else
    {
      // Iterate over tau decay products and pass each through detector
      (*particle_it)->print_data();
      std::vector<std::shared_ptr<particle>> decay_prods = tau_ptr->get_decay_products();
      for(auto tau_it{decay_prods.begin()}; tau_it != decay_prods.end(); tau_it++)
      {
        for(auto sub_detect_it{sub_detectors.begin()}; sub_detect_it != sub_detectors.end(); sub_detect_it++)
          (*sub_detect_it)->use_sub_detector(*tau_it);
        print_detected_data(*tau_it);
        std::cout<<std::endl;
      }
    }
  }
  predict_particles(input);
  std::cout<<std::endl;
}

// Function to find start and end indices of a loop used in the prediction function
void determine_start_and_end_indices(std::vector<std::shared_ptr<particle>> p, int& start,
int& end, std::vector<int>& taus)
{
  // Search through particles in event for any tau particles and note the ID of them.
  // Otherwise find a start and end index which will be the limits of the for loop
  // for which energies to include in the sum since each particles detected energies
  // are indexed at its ID within each sub detector
  int n = p.size();
  for(int i{}; i < n; i++)
  {
    auto tau_ptr = dynamic_cast<tau*>((p[i]).get());
    if(tau_ptr)
    {
      taus.push_back(tau_ptr->get_particle_id());
      if(i == 0)
        start = tau_ptr->get_particle_id() + 1;
      else if(i == n - 1)
      {
        std::vector<std::shared_ptr<particle>> products = tau_ptr->get_decay_products();
        std::shared_ptr<particle> final_product = products[products.size() - 1];
        end = final_product->get_particle_id();
      }
    }
    else if(i == 0)
      start = p[i]->get_particle_id();
    else if(i == n - 1)
      end = p[n - 1]->get_particle_id();
  }
}

// Determines if particle detected by tracker
void detected_by_tracker(std::vector<int>& output, tracker* ptr, int index)
{
  if(ptr->get_total_detected_energy()[index] > 0)
    output.push_back(1);
  else output.push_back(0);
}

// Determines if particle detected by calorimeter (EM and HAD seperate)
void detected_by_calorimeter(std::vector<int>& output, calorimeter* ptr, int index)
{ 
  // EM only
  if(ptr->get_deposited_in_em()[index] == 1 && ptr->get_deposited_in_had()[index] == 0)
    output.insert(output.end(), {1, 0});
  // BOTH
  else if(ptr->get_deposited_in_em()[index] == 1 && ptr->get_deposited_in_had()[index] == 1)
    output.insert(output.end(), {1, 1});
  // NEITHER
  else
    output.insert(output.end(), {0, 0});
}

// Determines if particle detected by muon chamber
void detected_by_muon_chamber(std::vector<int>& output, muon_chamber* ptr, int index)
{
  if(ptr->get_total_detected_energy()[index] > 0)
    output.push_back(1);
  else output.push_back(0);
}

// Determines which sub-detectors each particle has been detected by
void detector::detected_by_sub_detectors(int start, int end, std::vector<int> tau_i,
std::vector<std::vector<int>>& bool_table, double& detected_energy)
{
  for(int i{start}; i <= end; i++)
  {
    // Initialize bool table for current particle
    std::vector<int> particle_bools;
    auto it = std::find(tau_i.begin(), tau_i.end(), i);
    if(it == tau_i.end())
    {
      for(auto sub_detect_it{sub_detectors.begin()}; sub_detect_it != sub_detectors.end(); sub_detect_it++)
      { 
        // Add energy detected by sub detector to total energy detected
        detected_energy += (*sub_detect_it)->get_total_detected_energy()[i];

        // Add all values to particle bools
        // Tracker
        auto tracker_ptr = dynamic_cast<tracker*>((*sub_detect_it).get());
        if(tracker_ptr)
          detected_by_tracker(particle_bools, tracker_ptr, i);

        // Calorimeter
        auto calorimeter_ptr = dynamic_cast<calorimeter*>((*sub_detect_it).get());
        if(calorimeter_ptr)
          detected_by_calorimeter(particle_bools, calorimeter_ptr, i);

        // Muon Chamber
        auto muon_chamber_ptr = dynamic_cast<muon_chamber*>((*sub_detect_it).get());
        if(muon_chamber_ptr)
          detected_by_muon_chamber(particle_bools, muon_chamber_ptr, i);
      }
      // Add sub detector bools to the bool table
      bool_table.push_back(particle_bools);
    }
  }
}

// Checks if prediction is correct
void check_prediction(particle_type prediction, particle_type correct_type, int& correct_n)
{
  if(prediction == correct_type)
    // Check if prediction is the particle 
    correct_n++;
  else
  {
    // Some cases like the anti-particles and neutrinos will not return a correct guess
    // even if the prediction is correct because of the way I have chosen to label
    // each prediction. This else statement should catch these edge cases

    // Neutrinos
    std::vector<particle_type> neutrinos{particle_type::electron_neutrino, particle_type::electron_antineutrino,
    particle_type::muon_neutrino, particle_type::muon_antineutrino, particle_type::tau_neutrino,
    particle_type::tau_antineutrino};

    // This checks if the correct and predicted particles are any neutrino type and if so 
    // it will increment the counter for correct predictions
    if(std::find(neutrinos.begin(), neutrinos.end(), correct_type) != neutrinos.end()
    && std::find(neutrinos.begin(), neutrinos.end(), prediction) != neutrinos.end())
      correct_n++;

    // Anti-particles
    if(correct_type == particle_type::antielectron && prediction == particle_type::electron)
      correct_n++;
    else if(correct_type == particle_type::antimuon && prediction == particle_type::muon)
      correct_n++;
    else if(correct_type == particle_type::antiproton && prediction == particle_type::proton)
    correct_n++;
  }
}

// Predict input particle from detector data
void detector::predict_particles(event input)
{
  // Initialize variables and find start ID, end ID and any tau ID's that will be used
  // in the for loop in the next function
  std::vector<std::shared_ptr<particle>> particles = input.get_particles();
  int start_index;
  int end_index;
  std::vector<int> tau_indices;
  determine_start_and_end_indices(particles, start_index, end_index, tau_indices);

  // Now using the indices found, iterate through each sub detector to gather the following data:
  // Whether the particle was detected by the tracker,
  // Whether the particle deposited energy in the EM calorimeter,
  // Whether the particle deposited energy in the HAD calorimeter,
  // Whether the particle was detected by the muon chamber.
  // Also find the total energy deposited per event to calculate the total detected energy,
  // invisible energy and the energy efficiency of the detector

  std::vector<std::vector<int>> sub_detector_bool_table;
  double total_detected_energy{0};
  detected_by_sub_detectors(start_index, end_index, tau_indices, sub_detector_bool_table, total_detected_energy);

  // Get total initial energy
  double total_true_energy = input.get_total_energy();
  // Get invisible energy
  double invisible_energy = total_true_energy - total_detected_energy;

  // sub_detector_bool_table is a table of bools for the following sub detector variables:
  // [Detected by Tracker, E dep. in EM cal., E dep. in HAD cal., Detected by M.C.]
  // Based off of the data in this table as well as the invisible energy of the total event
  // the detector will predict the particles in the event
  // Note: anti-particles not distinguished as they act identically within each sub-detector 
  std::vector<particle_type> predicted_particles;
  for(auto bool_table : sub_detector_bool_table)
  {
    // Initialize bools
    bool tracker_detected = bool_table[0];
    bool em_cal_detected = bool_table[1];
    bool had_cal_detected = bool_table[2];
    bool muon_cham_detected = bool_table[3];

    // Add predicted particles to vector
    if(tracker_detected)
    {
      if(em_cal_detected && !had_cal_detected)
      {
        // A large invisible energy suggests this electron is accompanied
        // by many neutrinos, and is likely due to a leptonic tau
        if(invisible_energy >= total_true_energy/2)
          predicted_particles.push_back(particle_type::leptonic_tau);
        else
          predicted_particles.push_back(particle_type::electron);
      }
      else if(muon_cham_detected)
        predicted_particles.push_back(particle_type::muon);
      else if(em_cal_detected && had_cal_detected)
      {
        // A large invisible energy suggests this hadron is accompanied
        // by a neutrino, and is likely due to a hadronic tau
        if(invisible_energy >= total_true_energy/2)
          predicted_particles.push_back(particle_type::hadronic_tau);
        else
          predicted_particles.push_back(particle_type::proton);
      }
      else
        predicted_particles.push_back(particle_type::electron);
    }
    else
    { 
      if(em_cal_detected && !had_cal_detected)
        predicted_particles.push_back(particle_type::photon);
      else if(muon_cham_detected)
        predicted_particles.push_back(particle_type::muon);
      else if(em_cal_detected && had_cal_detected)
        predicted_particles.push_back(particle_type::neutron);
      else
        // Electron neutrino is used for a 'general neutrino' as the detector
        // cannot know which flavour of neutrino has passed through
        predicted_particles.push_back(particle_type::electron_neutrino);
    }
  }

  // Now print out the predicted particles for the event and count the number of correct particles
  int correct_predictions{};
  std::cout<<"Here is a list of particles which the detector predicts has passed through (in order): "<<std::endl;
  for(int i{}; i < predicted_particles.size(); i++)
  {
    particle_type name = predicted_particles[i];
    if(name == particle_type::electron)
      std::cout<<"Electron";
    else if(name == particle_type::muon)
      std::cout<<"Muon";
    else if(name == particle_type::leptonic_tau)
      std::cout<<"Tau (Leptonic Decay)";
    else if(name == particle_type::hadronic_tau)
      std::cout<<"Tau (Hadronic Decay)";
    else if(name == particle_type::proton)
      std::cout<<"Proton";
    else if(name == particle_type::neutron)
      std::cout<<"Neutron";
    else if(name == particle_type::photon)
      std::cout<<"Photon";
    else if(name == particle_type::electron_neutrino)
      std::cout<<"Neutrino";
    std::cout<<std::endl;

    // Check if prediction is correct
    check_prediction(name, input.get_input_particle_types()[i], correct_predictions);
  }
  std::cout<<std::endl;

  // Print data relating to energy and prediction efficiencies 
  print_event_data(total_true_energy, total_detected_energy);
  double particle_n = input.get_input_particle_types().size();
  double prediction_efficiency = (correct_predictions / particle_n) * 100;
  std::cout<<"Prediction Efficiency = "<<prediction_efficiency<<"% ("<<correct_predictions
  <<"/"<<particle_n<<")"<<std::endl;
}

// Print data (prints which sub detectors are in detector)
void detector::print_detector_config(std::vector<sub_detector_type> input)
{ 
  std::cout<<"Sub Detector Configuration:"<<std::endl;
  for(auto it{input.begin()}; it != input.end(); it++)
  {
    if(*it == sub_detector_type::tracker)
      std::cout<<"Tracker"<<std::endl;
    else if(*it == sub_detector_type::calorimeter)
      std::cout<<"Calorimeter"<<std::endl;
    else if(*it == sub_detector_type::muon_chamber)
      std::cout<<"Muon Chamber"<<std::endl;
  }
  std::cout<<std::endl;
}

// Print detected data (Prints the data found after detector has been used)
void detector::print_detected_data(std::shared_ptr<particle> input)
{
  // Print particle data
  input->print_data();
  // Print sub detector data
  for(auto it{sub_detectors.begin()}; it != sub_detectors.end(); it++)
    (*it)->print_data();
}

// Print data for event (invisible energy, efficiencies)
void detector::print_event_data(double true_energy, double detected_energy)
{

  std::cout<<"Detector Details:"<<std::endl;
  // Print invisible energy
  double invisible_energy = true_energy - detected_energy;
  std::cout<<"Invisible Energy: "<<invisible_energy<<" GeV"<<std::endl;

  // Print energy efficiency of the detector
  double energy_efficiency = (detected_energy / true_energy) * 100;
  std::cout<<"Energy Efficiency: "<<energy_efficiency<<"%, ("<<detected_energy<<" GeV/"<<true_energy
  <<" GeV)"<<std::endl;
}

// Print data for total simulation (all events)
void detector::print_total_data()
{
  std::cout<<std::endl<<"Summary After All Events Have Passed Through the Detector:"<<std::endl<<std::endl;

  // Initialize counts for number of particles each sub-detector detected
  // and total energy detected
  int tracker_count{};
  double tracker_energy{};
  int calorimeter_count{};
  double calorimeter_energy{};
  int muon_chamber_count{};
  double muon_chamber_energy{};

  // Create vectors of counts and energies
  std::vector<int> counts{tracker_count, calorimeter_count, muon_chamber_count};
  std::vector<double> energies{tracker_energy, calorimeter_energy, muon_chamber_energy};

  for(int i{}; i < counts.size(); i++)
  {
    std::vector<double> detector_energies = sub_detectors[i]->get_total_detected_energy();
    for(auto it{detector_energies.begin()}; it != detector_energies.end(); it++)
    {
      // Iterate energies
      energies[i] += *it;

      // If detector energy is not 0 that means the particle has been detected
      // Therefore iterate counts
      if(*it > 0)
        counts[i]++;
    }
  }

  // Print data for each sub detector
  // Create vector of sub detector names
  std::vector<std::string> names{"Tracker", "Calorimeter", "Muon Chamber"};
  for(int i{}; i < names.size(); i++)
  {
    std::cout<<names[i]<<":"<<std::endl;
    std::cout<<"Number of Particles Interacted With: "<<counts[i]<<std::endl;
    std::cout<<"Total Energy Detected: "<<energies[i]<<" GeV"<<std::endl;
    std::cout<<std::endl;
  }
}