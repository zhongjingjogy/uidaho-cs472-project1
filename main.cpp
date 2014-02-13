/* Copyright 2014 Andrew Schwartzmeyer
 *
 * University of Idaho - CS 472: Evolutionary Computation by Terry Soule
 *
 * Project #1a Hill Climbing and Simulated Annealing
 *
 * This program uses C++11 extensions (array template, auto specifier,
 * range-based for loop)
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "spherical_problem.hpp"
#include "schwefel_problem.hpp"
#include "hill_climbing_algorithm.hpp"
#include "simulated_annealing_algorithm.hpp"
#include "individual.hpp"

int main(int argc, char *argv[]) {
  // seed random number generator
  std::srand(std::time(0));

  Spherical * problem = new Spherical;
  HillClimbing algorithm(problem);

  const Individual * solution = algorithm.solve();
  std::cout << solution->represent() << "\n"
	    << problem->fitness(solution) << "\n"
	    << problem->problem(solution) << "\n";

  return 0;
}
