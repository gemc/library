#ifndef  G4DISPLAY_H
#define  G4DISPLAY_H 1

// c++
#include <string>
#include <vector>
using namespace std;

// defaults value for viewing
#define defaultGViewerDriver "OGL"
#define defaultGViewerSize   "800x800"
#define defaultGViewerPos    "+400+100"

extern vector<string> availableG4Viewers;

// mlibrary
#include "goptions.h"


class G4Display {

public:
	G4Display(GOptions* gopt);

public:
	// G4Display options
	static map<string, GOption> defineOptions();

private:
	string getViewerFromOption(vector<string> opt);
	string getGeoFromOption(vector<string> opt);
	string getPosFromOption(vector<string> opt);
};


#endif
