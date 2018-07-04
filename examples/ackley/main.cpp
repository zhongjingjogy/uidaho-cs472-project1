/* Copyright 2014 Andrew Schwartzmeyer
 *
 * University of Idaho - CS 472: Evolutionary Computation by Terry Soule
 *
 * Project #1 Genetic Algorithm
 *
 * This program uses C++11 extensions (array template, range-based for
 * loop, random library)
 */

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>

// aliases
#include "aliases.hpp"

// individual
#include "individual/individual.hpp"

// algorithms
#include "algorithm/algorithm.hpp"
#include "algorithm/genetic_algorithm.hpp"
#include "algorithm/hill_climbing_algorithm.hpp"
#include "algorithm/simulated_annealing_algorithm.hpp"
#include "algorithm/mutator/mutator.hpp"
#include "algorithm/mutator/mutator_creep.hpp"
#include "algorithm/mutator/mutator_gaussian.hpp"
#include "algorithm/mutator/mutator_jumping.hpp"
#include "algorithm/recombinator/recombinator.hpp"
#include "algorithm/recombinator/recombinator_arithmetic.hpp"
#include "algorithm/recombinator/recombinator_two_point.hpp"
#include "algorithm/recombinator/recombinator_uniform.hpp"

#include "ackley_problem.hpp"

using namespace std;
using aliases::parameter;
using namespace algorithm;
using namespace problem;

int main() {

    // setup mutator
    unique_ptr<const Mutator> working_mutator;
    working_mutator = unique_ptr<const Mutator>(new mutator::Creep());
    // working_mutator = unique_ptr<const Mutator>(new mutator::Gaussian());
    // working_mutator = unique_ptr<const Mutator>(new mutator::Jumping());

    // setup recombinator
    shared_ptr<const Recombinator> working_recombinator;
    working_recombinator = shared_ptr<const Recombinator>(new recombinator::Arithmetic());
    // working_recombinator = shared_ptr<const Recombinator>(new recombinator::TwoPoint());
    // working_recombinator = shared_ptr<const Recombinator>(new recombinator::Uniform());

    // setup each problem and run the GA on it
    unique_ptr<Problem> working_problem;

    working_problem = unique_ptr<Problem>(new Ackley(256, 0));
    
    // Run GA on problem
    if (working_problem != nullptr) {
        Genetic algorithm(*working_problem, *working_mutator, working_recombinator);
        const Individual solution = algorithm.solve();
        cout << working_problem->represent() << solution.represent()
        << "Raw fitness: " << solution.fitness << '\n' << endl;
    }
    return 0;
}