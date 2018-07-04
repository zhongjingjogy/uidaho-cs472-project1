/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Header file for base problem class
 */

#ifndef _Quadratic_PROBLEM_H_
#define _Quadratic_PROBLEM_H_

#include "problem.hpp"
#include "individual/individual.hpp"
#include "aliases.hpp"

namespace problem {
  using aliases::parameter;
  using individual::Individual;

  class Quadratic: public Problem {
  public:
    Quadratic(const long i = 100000000,
	   const parameter g = 0.99,
	   const parameter f = 0.65,
	   const parameter d = 0.1,
	   const parameter h = 0.5,
	   const int c = 10): Problem("Quadratic",
					 -1000, 100000, 0, 0.1, true,
					 i, g, f, d, h, c) {}
    parameter fitness(const Individual & subject) const;
  };
}

#endif /* _Quadratic_PROBLEM_H_ */
