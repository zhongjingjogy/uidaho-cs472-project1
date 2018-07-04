Genetic Algorithm
--------------------

A code for real code genetic algorithm, where the genes are represented by array of numerical number rather than the binary string. 

Custom problem
^^^^^^^^^^^^^^^^^^^^^^

A new problem should be derived from the Problem class,

.. code:: C++

    // quadratic_problem.hpp
    #ifndef _Quadratic_PROBLEM_H_
    #define _Quadratic_PROBLEM_H_

    #include "problem.hpp"
    #include "individual/individual.hpp"
    #include "aliases.hpp"

    namespace problem {
    using aliases::parameter;
    using individual::Individual;

    // g: the target of objective function
    // f:
    // d: delta for the mutation process 
    class Quadratic: public Problem {
    public:
        Quadratic(const long i = 100000000,
        const parameter g = 0.99,
        const parameter f = 0.65,
        const parameter d = 0.01,
        const parameter h = 0.5,
        const int c = 10): Problem(3, "Quadratic",
                        -100, 100, 0, 0.1, true,
                        i, g, f, d, h, c) {}
        parameter fitness(const Individual & subject) const;
    };
    }

    #endif /* _Quadratic_PROBLEM_H_ */

    // quadratic_problem.cpp
    
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
    double target[3] = {0, 10, 20};
    parameter sum = 0;
    for (unsigned long i = 0; i < subject.size(); ++i) {
        sum += std::pow(subject[i] - target[i], 2);
    }
    // std::cout << subject.size() << ": " << sum << std::endl;
    return sum;
    }

As the problem has been setup, one can use it in the framework of the current project,

.. code: C++

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

    #include "quadratic_problem.hpp"

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

        // Quadratic(maxiterations, )
        working_problem = unique_ptr<Problem>(new Quadratic(245, 0.0, 0.65, 0.01));
        
        // Run GA on problem
        if (working_problem != nullptr) {
            Genetic algorithm(*working_problem, *working_mutator, working_recombinator);
            const Individual solution = algorithm.solve();
            cout << working_problem->represent() << solution.represent()
            << "Raw fitness: " << solution.fitness << '\n' << endl;
        }
        return 0;
    }

`CMake` is used to generate the `Makefile`. Anyone who wants to use it as  a third part library should custom the `include` and `library` directories correctly in the `CMakeLists.txt` following the example in this project.

More details
^^^^^^^^^^^^^^^^^^^^

Please refer to `uidaho-cs472-project1`_ for more details.

.. _uidaho-cs472-project1: https://github.com/andschwa/uidaho-cs472-project1