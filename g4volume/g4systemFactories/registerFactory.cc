// g4volume
#include "g4SetupFactory.h"
#include "native/g4NativeSetupFactory.h"

void G4Setup::registerFactoriesAndBuildG4Volumes(GSetup* gsetup, GOptions* gopt)
{
	map<string, G4SetupFactory*> g4setupactory;

	// registering factories in the manager
	// and adding them to systemFactory
	for(auto &s : gsetup->getSetup()) {
		string factory = s.second->getFactory();

		// text
		// ----
		if(factory == "text") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4setupactory.find(factory) == g4setupactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4NativeSetupFactory>("G4NativeSetupFactory");
				g4setupactory[factory] = g4SystemManager.CreateObject<G4SetupFactory>("G4NativeSetupFactory");
			}
		}
	}

	// now building geant4 objects
	int remainingVolumes;
	do {
		remainingVolumes = 0;
		// looping over systems
		for(auto &s : gsetup->getSetup()) {
			string factory = s.second->getFactory();
			// looping over volumes in that system
			for(auto &v : s.second->getSytems()) {
				if(g4setupactory.find(factory) != g4setupactory.end()) {
					if(g4setupactory[factory]->loadG4Setup(gopt, v.second, g4setup) == false) remainingVolumes = remainingVolumes + 1;
				} else {
					G4cerr << " !!! Fatal Error: g4setupactory factory <" << factory << "> not found." << G4endl;
					exit(0);
				}
			}
		}
	} while (remainingVolumes > 0);
}
