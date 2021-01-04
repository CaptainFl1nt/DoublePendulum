#ifndef __ODESolver__
#define __ODESolver__
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "DifferentialEquation.hpp"

using namespace std;

class ODESolver {
    protected:
        int dim;
        vector<double> yinitial;
        double dt;
        double timetotal;
        
        vector<double> (*f)(vector<double>, double);
        DifferentialEquation* eqnObj;
        vector<double> wrap(vector<double>, double);
        bool useFunc;
        
        vector<vector<double>> solution;
    public:
        ODESolver() { }
        ODESolver(vector<double> (*func)(vector<double>, double), vector<double> y0);
        ODESolver(DifferentialEquation* diffEqn, vector<double> y0);
        
        void setDimension(double d);
        void setY0(vector<double> y0);
        void setDt(double dt) { this->dt = dt; }
        void setTMax(double tmax) { timetotal = tmax; }
        void setFunc(vector<double> (*func)(vector<double>, double));
        void setDiffEqn(DifferentialEquation* diffEqn);
        
        void output(string filename);
        
        vector<vector<double>>* getSolution() { return &solution; }
        
        virtual void Solve() = 0;
        
        ~ODESolver() { }
};

ODESolver::ODESolver(vector<double> (*func)(vector<double>, double), vector<double> y0) {
    dim = (int) y0.size();
    yinitial.resize(dim);
    f = func;
    yinitial = y0;
    useFunc = true;
}

ODESolver::ODESolver(DifferentialEquation* diffEqn, vector<double> y0) {
    dim = (int) y0.size();
    yinitial.resize(dim);
    yinitial = y0;
    eqnObj = diffEqn;
    useFunc = false;
}

vector<double> ODESolver::wrap(vector<double> y, double t) {
    if (useFunc) {
        return f(y,t);
    }
    return eqnObj->equation(y,t);
}

void ODESolver::setDimension(double d) {
    dim = d;
    yinitial.resize(dim);
}

void ODESolver::setY0(vector<double> y0) {
    dim = (int) y0.size();
    yinitial.resize(dim);
    yinitial = y0;
}

void ODESolver::setFunc(vector<double> (*func)(vector<double>, double)) {
    f = func;
    useFunc = true;
}

void ODESolver::setDiffEqn(DifferentialEquation* diffEqn) {
    eqnObj = diffEqn;
    useFunc = false;
}

void ODESolver::output(string filename) {
    ofstream outputfile;
    outputfile.open(filename);
    for (int i = 0; i*dt <= timetotal; i++) {
        outputfile << i*dt;
        for (int j = 0; j < dim; j++) {
            outputfile << "," << solution.at(i).at(j);
        }
        outputfile << endl;
    }
}
#endif