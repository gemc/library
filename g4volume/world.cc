// g4volume
#include "g4volume.h"

// geant4
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// mlibrary
#include "gstring.h"
using namespace gstring;


void G4Setup::buildWorld(GOptions* gopt)
{
//	bool gui = gopt->getOption("gui").getBoolValue();

	G4NistManager* NISTman = G4NistManager::Instance();
	G4Material* air  = NISTman->FindOrBuildMaterial("G4_AIR");

	// for now the hall is a box
	G4ThreeVector worldSize = vectorFromStringVector(gopt->getStringVectorValue("hall"));

	G4Box * solidWorld = new G4Box(WORLDNAME, worldSize.x(), worldSize.y(), worldSize.z());
	G4LogicalVolume * logicWorld = new G4LogicalVolume(solidWorld, air, WORLDNAME, 0, 0, 0);

	G4VPhysicalVolume * physiWorld
	= new G4PVPlacement(0,               // no rotation
						G4ThreeVector(), // at (0,0,0)
						logicWorld,      // its logical volume
						WORLDNAME,         // its name
						0,               // its mother  volume
						false,           // no boolean operations
						0);              // copy number


	(*g4setup)[WORLDNAME] = new G4Volume(solidWorld, logicWorld, physiWorld);
}
