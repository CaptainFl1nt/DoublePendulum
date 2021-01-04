#ifndef __DifferentialEquation__
#define __DifferentialEquation__
#include <vector>
using namespace std;

class DifferentialEquation {
	public:
		virtual vector<double> equation(vector<double> y, double t) = 0;
};
#endif
