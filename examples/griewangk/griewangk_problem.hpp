/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Header file for base problem class
 */

#ifndef _GRIEWANGK_PROBLEM_H_
#define _GRIEWANGK_PROBLEM_H_

#include "problem.hpp"
#include "individual/individual.hpp"
#include "aliases.hpp"

namespace problem {
  using aliases::parameter;
  using individual::Individual;

  class Griewangk: public Problem {
  public:
    Griewangk(const long i = 1000000,
	      const parameter g = 0.9999,
	      const parameter f = 0.65,
	      const parameter d = 0.1,
	      const parameter h = 0.5,
	      const int c = 10000): Problem(3, "Griewangk",
					    -600, 600, 0, 1700, true,
					    i, g, f, d, h, c) {};
    parameter fitness(const Individual & subject) const;
  };
}

#endif /* _GRIEWANGK_PROBLEM_H_ */
