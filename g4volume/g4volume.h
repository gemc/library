#ifndef  G4VOLUME_H
#define  G4VOLUME_H

// geant4
#include "G4PVPlacement.hh"
#include "G4VisManager.hh"

// c++
#include <map>
using namespace std;

// mlibrary
#include "goptions.h"
#include "gfactory.h"
#include "gsystem.h"

class G4Volume {

public:
	G4Volume(G4VSolid* s, G4LogicalVolume* l, G4VPhysicalVolume* p) : solidVolume(s), logicalVolume(l), physicalVolume(p) { ; }

public:
	G4VSolid*          getSolid()    const { return solidVolume;}
	G4LogicalVolume*   getLogical()  const { return logicalVolume;}
	G4VPhysicalVolume* getPhysical() const { return physicalVolume;}

private:
	G4VSolid*             solidVolume;   ///< Solid
	G4LogicalVolume*    logicalVolume;   ///< Logical Volume
	G4VPhysicalVolume* physicalVolume;   ///< Physical Volume
};


class G4Setup {

public:
	G4Setup(GSetup* gsetup, GOptions* gopt) {
		g4setup = new map<string, G4Volume*>;
		buildSetup(gsetup, gopt);
	}

	G4VPhysicalVolume* getPhysical(string vname) const;

private:

	// the key has the form system/volumename
	map<string, G4Volume*> *g4setup;
	void buildSetup(GSetup* gsetup, GOptions* gopt);
	G4Volume* getG4Volume(string name) const;

	// manager to register the factories
	GManager g4SystemManager;
	void registerFactoriesAndBuildG4Volumes(GSetup* gsetup, GOptions* gopt);
	void buildWorld(GOptions* gopt);

public:
	void createG4Volume(G4Volume *g4v, string name);

	// G4Setup options - defined in utilities.cc
	static map<string, GOption> defineOptions();


};

#endif
