#ifndef SYSTEMTEXTFACTORY_H
#define SYSTEMTEXTFACTORY_H 1

// gvolume
#include "../systemFactory.h"

// system factory
class GSystemTextFactory : GSystemFactory
{
public:
	void loadSystem(GOptions* gopt, GSystem *s) {
		verbosity = gopt->getInt("vsetup");
		if(verbosity > 1) {
			cout << setupLogHeader << " Loading <text> system " << s->getName() << endl;
		}
		loadMaterial(gopt, s);
		loadGeometry(gopt, s);
	}

private:
	vector<string> paths; // Paths to system data
	int verbosity;

private:
	virtual void loadMaterial(GOptions* gopt, GSystem *s);
	virtual void loadGeometry(GOptions* gopt, GSystem *s);

};


#endif