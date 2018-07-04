/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Source file for derived genetic algorithm class
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

#include "algorithm.hpp"
#include "genetic_algorithm.hpp"
#include "aliases.hpp"
#include "individual/individual.hpp"
#include "random_generator.hpp"

using algorithm::Genetic;
using algorithm::population;
using aliases::parameter;
using individual::Individual;
using namespace random_generator;

const population Genetic::selection(const population & generation) const {
  // implements tournament selection, returning desired number of best parents
  population parents;
  int_dist population_dist(0, population_size - 1); // closed interval, so (-1)
  for (int i = 0; i < recombinator->get_size(); ++i) {
    population contestants;
    // create tournament of random members drawn from generation
    for (int i = 0; i < tournament_size; ++i)
      contestants.emplace_back(generation[population_dist(rg.engine)]);
    // select best member from each tournament
    parents.emplace_back(*std::max_element(contestants.begin(), contestants.end()));
  }
  // return best Individual from a set of contestants
  return parents;
}

const Individual Genetic::solve() const {
  // setup basic logging
  std::ofstream log("logs/" + problem.name + ".dat");
  log << "# Solving the " << problem.represent()
      << "# Using a Genetic Algorithm"
      << " with population size " << population_size
      << ", tournament size " << tournament_size
      << ", crossover size " << recombinator->get_size()
      << ", crossover chance of " << recombinator->get_chance()
      << ", mutation chance of " << 1./problem.vardimension
      << ", and elitism replacement size " << elitism << "." << std::endl;
  while(true) {
    // create initial population
    population generation;
    Individual best(problem.vardimension);
    int_dist population_dist(0, population_size - 1); // closed interval, so (-1)
    for (int i = 0; i < population_size; ++i)
      generation.emplace_back(problem.potential());
    // generations loop
    for (long i = 0; i < problem.iterations; ++i) {
      // find generation's best member
      best = *std::max_element(generation.begin(), generation.end());
      parameter sum = std::accumulate(generation.begin(), generation.end(), 0.);
      // logging
      log << i << '\t' << best.fitness << '\t' << sum / population_size << '\n';
      // terminating condition
      if (best > problem.goal) return best;
      // selection and mutation stage
      population offspring;
      while(offspring.size() != population_size) {
        // tournament selection of parents
        const population parents = selection(generation);
        // crossover
        const population children = recombinator->crossover(parents, problem);
        // add mutated children to offspring
        for (const Individual child : children) offspring.emplace_back(mutator.mutate(problem, child));
      }
      // replace generation with offspring
      generation.swap(offspring);
      // elitism replacement of random individuals
      for (int i = 0; i < elitism; ++i) {
        generation[population_dist(rg.engine)] = best;
      }
    }
    log.close();
    return best;
  }
}
