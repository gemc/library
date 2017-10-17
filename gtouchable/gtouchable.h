#ifndef  GTOUCHABLE_H
#define  GTOUCHABLE_H 1

// c++
#include <vector>
#include <string>  // < not needed with clang but needed on Linux gcc 4.8.5
using namespace std;

enum GType { readout, flux, counter };

class GTouchable {

public:
	GTouchable(string sensitivity, string gtouchableString, double tWindow);

private:
	GType       gType;
	double       time;   ///< Time of the first step
	double timeWindow;   ///< System Time Window, used to determine if steps belong to the same hit
	int       trackId;   ///< Used to determine if steps belong to the same hit for flux detectors
	double  eFraction;   ///< Energy sharing Fraction
	vector<int>  gTid;   ///< Uniquely identify a sensitive element

};


#endif
