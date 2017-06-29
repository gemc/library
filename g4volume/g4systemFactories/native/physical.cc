// g4volume
#include "g4NativeSetupFactory.h"

// geant4

bool G4NativeSetupFactory::buildPhysical(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s)
{
	int    verbosity = gopt->getInt("vsetup");
	string logVolume = gopt->getString("logVolume");
	string vname = s->getName();

	bool depVerbosity = (verbosity > 2) || (vname == logVolume);
	// check dependencies first
	// gvolume
	// logical volume must exist
	// logical mother must exist
	if(!checkPhysicalDependencies(depVerbosity, s, g4s)) return false;

	// if it's a component, do nothing
	string matName = s->getMaterial();
	if(matName == "component") return true;



	// First  G4 Constructor
	//	G4PVPlacement(G4RotationMatrix *pRot,
	//				  const G4ThreeVector &tlate,
	//				  G4LogicalVolume *pCurrentLogical,
	//				  const G4String& pName,
	//				  G4LogicalVolume *pMotherLogical,
	//				  G4bool pMany,
	//				  G4int  pCopyNo,
	//				  G4bool pSurfChk=false);
	// Initialise a single volume, positioned in a frame which is rotated by
	// *pRot and traslated by tlate, relative to the coordinate system of the
	// mother volume pMotherLogical.
	// If pRot=0 the volume is unrotated with respect to its mother.
	// The physical volume is added to the mother's logical volume.
	// Arguments particular to G4PVPlacement:
	//   pMany Currently NOT used. For future use to identify if the volume
	//         is meant to be considered an overlapping structure, or not.
	//   pCopyNo should be set to 0 for the first volume of a given type.
	//   pSurfChk if true activates check for overlaps with existing volumes.
	// This is a very natural way of defining a physical volume, and is
	// especially useful when creating subdetectors: the mother volumes are
	// not placed until a later stage of the assembly program.

	bool checkForOverlaps = false;
	if(gopt->getInt("checkOverlaps") > 0) checkForOverlaps = true;

	G4Volume *thisG4Volume = (*g4s)[vname];

	thisG4Volume->addPhysical(new G4PVPlacement(getRotation(s),
												getPosition(s),
												thisG4Volume->getLogical(),
												vname,
												getLogicalFromMap(s->getMother(), g4s),
												false,
												s->getPCopyNo(),
												checkForOverlaps
												)
							  );

	return true;
}
