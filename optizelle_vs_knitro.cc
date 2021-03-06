#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "optizelle/json.h"
#include "optizelle/optizelle.h"
#include "optizelle/vspaces.h"


// Squares its input
template <typename T> T sq(T const &x) { return x * x; }

// Define a simple objective where
//
// f(x,y)=x^2+y^2
//
struct MyObj : public Optizelle::ScalarValuedFunction<double, Optizelle::Rm> {
    typedef Optizelle::Rm<double> X;

    // Evaluation
    double eval(const X::Vector &x) const {
        return sq(x[0]) + sq(x[1]);
    }

    // Gradient
    void grad(X::Vector const &x, X::Vector &grad) const {
        grad[0] = 2. * x[0];
        grad[1] = 2. * x[1];
    }

    // Hessian-vector product
    void hessvec(X::Vector const &x, X::Vector const &dx, X::Vector &H_dx) const {
        H_dx[0] = 2. * dx[0];
        H_dx[1] = 2. * dx[1];
    }
};

// Define simple inequalities
//
// h(x,y)= [ x + 2y >= 1  ]
//         [ 2x + y >= 1  ]
//         [ x      >= 0.5]
//         [      y <  0.2]
//
struct MyIneq : public Optizelle::VectorValuedFunction<double, Optizelle::Rm, Optizelle::Rm> {
    typedef Optizelle::Rm<double> X;
    typedef Optizelle::Rm<double> Y;

    // y=h(x)
    void eval(X::Vector const &x, Y::Vector &y) const {
        y[0] = x[0] + 2. * x[1] -1;
        y[1] = 2. * x[0] + x[1] -1;
        y[2] = x[0] - 0.3;
        y[3] = x[1] * (-1.) + 0.2;
    }

    // y=h'(x)dx
    void p(X::Vector const &x, X::Vector const &dx, Y::Vector &y) const {
        y[0] = dx[0] + 2. * dx[1];
        y[1] = 2. * dx[0] + dx[1];
        y[2] = dx[0];
        y[3] = dx[1] * (-1.);
    }

    // z=h'(x)*dy
    void ps(X::Vector const &x, Y::Vector const &dy, X::Vector &z) const {
        z[0] = dy[0] + 2. * dy[1] + dy[2] ;
        z[1] = 2. * dy[0] + dy[1] - dy[3] ;
    }

    // z=(h''(x)dx)*dy
    void pps(X::Vector const &x, X::Vector const &dx, Y::Vector const &dy,
                     X::Vector &z) const {
        X::zero(z);
    }
};

int optizelle_run() {
    auto fname = "inputs/newton_cg.json" ;

    // Create a type shortcut
    using Optizelle::Rm;

    // Generate an initial guess
    auto x = std::vector<double>{2.1, 0.1};

    // Allocate memory for the inequality multipler
    auto z = std::vector<double>(4);

    // Create an optimization state
    Optizelle::InequalityConstrained<double, Rm, Rm>::State::t state(x, z);

    // Read the parameters from file
    Optizelle::json::InequalityConstrained<double, Optizelle::Rm, Optizelle::Rm>::read(fname, state);

    // Create a bundle of functions
    Optizelle::InequalityConstrained<double, Rm, Rm>::Functions::t fns;
    fns.f.reset(new MyObj);
    fns.h.reset(new MyIneq);

    // Solve the optimization problem
    Optizelle::InequalityConstrained<double, Rm, Rm>::Algorithms ::getMin(
            Optizelle::Messaging::stdout, fns, state);

    // Print out the reason for convergence
    std::cout << "The algorithm converged due to: "
                        << Optizelle::OptimizationStop::to_string(state.opt_stop)
                        << std::endl;

    // Print out the final answer
    std::cout << std::scientific << std::setprecision(5)
                        << "The optimal point is: (" << state.x[0] << ',' << state.x[1] << ')' << std::endl;
    std::cout << std::scientific << std::setprecision(5)
                        << "min f(x) : " << fns.f->eval(state.x) << std::endl;

    // Write out the final answer to file
    Optizelle::json::InequalityConstrained<double, Rm, Rm>::write_restart(
            "solution.json", state);

    // Return that the program exited properly
    return EXIT_SUCCESS;
}



int main(int argc, char *argv[]) {
    int exec_code = optizelle_run();
    return exec_code;

}