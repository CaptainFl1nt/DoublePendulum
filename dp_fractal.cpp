#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "RungeKuttaSolver.hpp"
#include "DoublePendulum.hpp"
using namespace std;

int main() {
    // get file setup
    ifstream infile;
    infile.open("input1.txt");

    string filename;
    getline(infile,filename,'\n');

    double low1, low2, high1, high2;
    infile >> low1 >> high1 >> low2 >> high2;

    double Tmax = 360;
    double dt = 0.015;
    int N = 1000;

    double dx1, dx2;
    dx1 = (high1 - low1) / N;
    dx2 = (high2 - low2) / N;

    DoublePendulum system = DoublePendulum(1.0,1.0,1.0,1.0);

    vector<double> y0(4);
    y0[2] = 0;
    y0[3] = 0;

    double** flips = new double*[N];
    for (int i = 0; i < N; ++i) {
        flips[i] = new double[N];
    }

    RungeKuttaSolver solver;
    solver.setDiffEqn(&system);
    solver.setDt(dt);
    solver.setTMax(Tmax);	
    double flip_time;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            y0[0] = low1 + i*dx1;
	    y0[1] = low2 + j*dx2;
	    if (j % 100 == 0) {
	        cout << "Phi_1 = " << y0[0] << ", Phi_2 = " << y0[1] << endl;
	    }
	    if (2*cos(y0[0]) + cos(y0[1]) > 1) {
	        flips[i][j] = -1;
		continue;
	    }
            solver.setY0(y0);
	    vector<double> y = y0;
	    flip_time = -1;
	    for (int i = 0; i*dt < Tmax; ++i) {
	        y = solver.next(y,i*dt);
		if (abs(y[0]) > M_PI || abs(y[1]) > M_PI) {
		    flip_time = (i+1)*dt;
		    break;
		}
	    }
            flips[i][j] = flip_time;
	}
    }

    ofstream output;
    output.open(filename);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N-1; ++j) {
	    output << flips[i][j] << ",";
	}
	output << flips[i][N-1] << endl;
    }

    ofstream output2;
    output2.open("phi_"+filename);
    for (int i = 0; i < N; ++i) {
        output2 << low1 + i*dx1 << "," << low2 + i*dx2 << endl;
    }

    for (int i = 0; i < N; ++i) {
	delete[] flips[i];
    }
    delete[] flips;    
}
