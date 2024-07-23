// PHYS 30762 Programming in C++
// Project
// Harry Taylor - 10837736
// Bool detector (abstract) class member function implementation

#include<cstdlib>
#include<ctime>
#include<iostream>
#include"bool_detector.h"

// Move constructor
bool_detector::bool_detector(bool_detector&& input)
: sub_detector(std::move(input)), detection_layers(input.get_detection_layers()) 
{
  // Reset original values
  detection_layers = std::vector<int>{0};
}

// Deep copy assignment operator
bool_detector & bool_detector::operator=(const bool_detector& input)
{
  if(&input != this)
  {
    sub_detector::operator=(input);
    detection_layers = input.get_detection_layers();
  }
  return *this;
}

// Move assignment operator
bool_detector & bool_detector::operator=(bool_detector&& input)
{
  if(&input != this)
  {
    sub_detector::operator=(std::move(input));
    std::swap(detection_layers, input.detection_layers);
  }
  return *this;
}

// Detection layers setter
void bool_detector::set_detection_layers()
{ 
  // Randomly assign values to detection layers
  for(int i{}; i < detection_layers.size(); i++)
  {
    double rand_num = static_cast<double>(std::rand()) / RAND_MAX;
    if(rand_num > 0.5)
      detection_layers[i] = 1;
    else detection_layers[i] = 0;
  }
}