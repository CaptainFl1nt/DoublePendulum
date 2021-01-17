#ifndef __RungeKuttaSolver__
#define __RungeKuttaSolver__
#include "ODESolver.hpp"
#include <iostream>
#include <vector>
using namespace std;

class RungeKuttaSolver : public ODESolver {
    public:
        RungeKuttaSolver() : ODESolver() { }
        RungeKuttaSolver(vector<double> (*func)(vector<double>, double), vector<double> y0) : ODESolver(func,y0) { }
        RungeKuttaSolver(DifferentialEquation* diffEqn, vector<double> y0) : ODESolver(diffEqn,y0) { }
        vector<double> next(vector<double> y, double t);
};

vector<double> RungeKuttaSolver::next(vector<double> y, double t) {
    vector<double> dy(dim);
    vector<double> k1(dim);
    vector<double> k2(dim);
    vector<double> k3(dim);
    vector<double> k4(dim);
    vector<double> ytemp1(dim);
    vector<double> ytemp2(dim);
    vector<double> ytemp3(dim);

    vector<double> fval = wrap(y,t);
    for(int i=0; i<dim; i++) {
        k1[i] = dt*fval[i];
        ytemp1[i] = y[i] + 0.5*k1[i];
    }
    fval = wrap(ytemp1,t+dt/2.0);
    for(int i=0; i<dim; i++) {
        k2[i] = dt*fval[i];
        ytemp2[i] = y[i] + 0.5*k2[i];
    }
    fval = wrap(ytemp2,t+dt/2.0);
    for(int i=0; i<dim; i++) {
        k3[i] = dt*fval[i];
        ytemp3[i] = y[i] + k3[i];
    }
    fval = wrap(ytemp3,t+dt);
    for(int i=0; i<dim; i++) {
        k4[i] = dt*fval[i];
    }
    for(int i=0; i<dim; i++) {
        dy[i] = (k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i])/6.0;
    }
    for(int i=0; i<dim; i++) {
        y[i] += dy[i];
    }
    return y;
}
#endif
