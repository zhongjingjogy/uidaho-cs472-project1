/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Source file for base problem class
 */

#include <cassert>
#include <cmath>
#include <string>

#include "problem.hpp"
#include "aliases.hpp"
#include "individual/individual.hpp"

using namespace problem;
using aliases::parameter;
using individual::Individual;

Problem::Problem(const std::string & n,
		 const parameter dn, const parameter dx,
		 const parameter rn, const parameter rx,
		 const bool z,
		 const long i,
		 const parameter g, const parameter f,
		 const parameter d, const parameter h,
		 const int c):
  range_min(rn), range_max(rx), minimize(z), range_dist(dn, dx),
  name(n), domain_min(dn), domain_max(dx), goal(g),
  filter(f), delta(d), chance(h), constant(c), iterations(i) {};

parameter Problem::normal(const Individual & subject) const {
  // Scales problem value [min, max] to parameter [0, 1] with 1 being max fitness
  parameter normal = std::abs(subject.fitness - range_min) / (range_max - range_min);
  if (minimize) {
    if (normal > 1) normal = 1; // truncate worst end of fitnesses to 1
    assert(normal >= 0);	// fail if best fitness is < 0
    normal = 1. - normal;	// inverse if trying to minimize
  } else {
    if (normal < 0) normal = 0; // truncate worst end of fitnesses to 0
    assert(normal <= 1);	// fail if best fitness is > 1
  }
  return normal;
}

const Individual Problem::worst() const {
  Individual worst = this->potential();
  for (int i = 0; i < iterations; ++i) {
    const Individual subject = this->potential();
    if (subject < worst) worst = subject;
  }
  return worst;
}

const Individual Problem::potential() const {
  Individual potential(domain_min, domain_max, minimize, range_dist);
  potential.fitness = fitness(potential);
  return potential;
}

const std::string Problem::represent() const {
  std::string representation = name + " problem with domain ["
    + std::to_string(domain_min) + ", " + std::to_string(domain_max)
    + "] seeking goal of " + std::to_string(goal)
    + " using a maximum of " + std::to_string(iterations) + " iterations.\n";
  return representation;
}

bool Problem::compare(const std::string & c) const {
  // true if string matches name or allc
  return name.compare(c) == 0;
}
