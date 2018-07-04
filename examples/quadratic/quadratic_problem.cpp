/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Source file for Quadratic problem derived class
 */

#include <cmath>
#include <iostream>

#include "Quadratic_problem.hpp"
#include "problem.hpp"
#include "aliases.hpp"
#include "individual/individual.hpp"

using namespace problem;
using aliases::parameter;
using individual::Individual;

parameter Quadratic::fitness(const Individual & subject) const {
  double target[100] = {-100};
  parameter sum = 0;
  for (unsigned long i = 0; i < subject.size(); ++i) {
    sum += std::pow(subject[i] - target[i], 2);
  }
  // std::cout << subject.size() << ": " << sum << std::endl;
  return sum;
}
