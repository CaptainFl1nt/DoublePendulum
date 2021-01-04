#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "RungeKuttaSolver.hpp"
#include "DoublePendulum.hpp"
using namespace std;

int main() {
    // read setup from file
    ifstream infile;
    infile.open("input.txt");

    // get output file name
    string id;
    getline(infile,id,'\n');

    // read data
    double dt, Tmax, L1, L2, m1, m2;
    infile >> dt >> Tmax >> L1 >> L2 >> m1 >> m2;

    vector<double> y0(4);
    infile >> y0.at(0) >> y0.at(1) >> y0.at(2) >> y0.at(3);

    // setup system and solver
    DoublePendulum pend = DoublePendulum(m1,m2,L1,L2);
    RungeKuttaSolver solver = RungeKuttaSolver(&pend, y0);
    solver.setDt(dt);
    solver.setTMax(Tmax);

    // run and save simulation
    solver.Solve();
    solver.output("output_"+id+".csv");

    // save input params
    ofstream params;
    params.open("params_"+id+".csv");
    params << L1 << "," << L2 << "," << m1 << "," << m2 << endl;
    params.close();

    return 0;
}
