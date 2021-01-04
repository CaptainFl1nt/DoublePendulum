#ifndef __DoublePendulum__
#define __DobulePendulum__
#include <cmath>
#include <vector>
#include "DifferentialEquation.hpp"

using namespace std;

class DoublePendulum : public DifferentialEquation {
    private:
        double m1;
	double m2;
	double L1;
	double L2;
        double g;
    public:
	DoublePendulum() { }
	DoublePendulum(double m1, double m2, double L1, double L2);

	double getMass(int i);
	double getLength(int i);
        double getG() { return g; }
	void setMass(int i, double m);
	void setLength(int i, double L);
        void setG(double g) { this->g = g; }

	vector<double> equation(vector<double> y, double t);

};

DoublePendulum::DoublePendulum(double m1, double m2, double L1, double L2) {
    this->m1 = m1;
    this->m2 = m2;
    this->L1 = L1;
    this->L2 = L2;
    g = 9.81;
}

double DoublePendulum::getMass(int i) {
    if (i == 1) {
        return m1;
    }
    return m2;
}

double DoublePendulum::getLength(int i) {
    if (i == 1) {
        return L1;
    }
    return L2;
}

void DoublePendulum::setMass(int i, double m) {
    if (i == 1) {
         m1 = m;
    }
    else {
        m2 = m;
    }
}

void DoublePendulum::setLength(int i, double L) {
    if (i == 1) {
        L1 = L;
    }
    else {
        L2 = L;
    }
}

vector<double> DoublePendulum::equation(vector<double> y, double t) {
    vector<double> yp = vector<double>(4);
    yp[0] = y[2];
    yp[1] = y[3];
    double denom, omega1, omega2;
    denom = L1*(m1 + m2*pow(sin(y[1]-y[0]),2));
    
    omega1 = m2*L2*sin(y[1]-y[0])*y[3]*y[3] - (m1 + m2)*g*sin(y[0]);
    omega1 += (m2*L1*sin(y[1]-y[0])*y[2]*y[2] + m2*g*sin(y[1]))*cos(y[1]-y[0]);
    omega1 = omega1/denom;
    
    yp[2] = omega1;

    denom = L2*(-m1*m2-m2*m2*pow(sin(y[1]-y[0]),2));
    omega2 = (m2*L2*sin(y[1]-y[0])*y[3]*y[3]-(m1+m2)*g*sin(y[0]))*m2*cos(y[1]-y[0]);
    omega2 += (m2*L1*sin(y[1]-y[0])*y[2]*y[2]+m2*g*sin(y[1]))*(m1+m2);
    omega2 = omega2/denom;

    yp[3] = omega2;
    return yp;
}

#endif
