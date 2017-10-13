// g4volume
#include "g4NativeSetupFactory.h"

// mlibrary
#include "gstring.h"
using namespace gstring;

// geant4
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4Cons.hh"
#include "G4Para.hh"
#include "G4Trd.hh"


bool G4NativeSetupFactory::buildSolid(GOptions* gopt, GVolume *s, map<string, G4Volume*> *g4s)
{
	int    verbosity = gopt->getInt("g4volumev");
	string logVolume = gopt->getString("logVolume");
	string vname = s->getName();

	bool depVerbosity = (verbosity == GVERBOSITY_ALL) || (vname == logVolume);

	// check dependencies first
	if(!checkSolidDependencies(depVerbosity, s, g4s)) return false;

	// if the g4volume doesn't exist, create one and add it to the map
	G4Volume *thisG4Volume = nullptr;

	// check if g4s already exists
	if(g4s->find(vname) != g4s->end()) {
		thisG4Volume = (*g4s)[vname];
		// if the solid is already built, nothing to do
		if(thisG4Volume->getSolid() != nullptr) return true;
	} else {
		thisG4Volume = new G4Volume();
		// adding volume to the map
		(*g4s)[vname] = thisG4Volume;
	}


	// the order of these objects is the same as on the geant4 website
	// https://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch04.html

	// check and get parameters
	vector<double> pars = checkAndReturnParameters(s);

	string type = s->getType();

	if(type == "G4Box") {
		thisG4Volume->addSolid(new G4Box(vname,      ///< name
										 pars[0],    ///< half length in X
										 pars[1],    ///< half length in Y
										 pars[2]     ///< half length in Z
										 ), verbosity
							   );
		return true;
	} else 	if(type == "G4Tubs") {
		thisG4Volume->addSolid(new G4Tubs(vname,     ///< name
										  pars[0],   ///< Inner radius
										  pars[1],   ///< Outer radius
										  pars[2],   ///< Half length in z
										  pars[3],   ///< Starting phi angle
										  pars[4]    ///< Delta Phi angle
										  ), verbosity
							   );
		return true;
	} else 	if(type == "G4CutTubs") {
		thisG4Volume->addSolid(new G4CutTubs(vname,     ///< name
											 pars[0],   ///< Inner radius
											 pars[1],   ///< Outer radius
											 pars[2],   ///< Half length in z
											 pars[3],   ///< Starting phi angle
											 pars[4],   ///< Delta Phi angle
											 G4ThreeVector(pars[5], pars[6], pars[7]),    ///< Outside Normal at -z
											 G4ThreeVector(pars[8], pars[9], pars[10])    ///< Outside Normal at +z
											 ), verbosity
							   );
		return true;
	} else 	if(type == "G4Cons") {
		thisG4Volume->addSolid(new G4Cons(vname,     ///< name
										  pars[0],   ///< Inside radius at -pDz
										  pars[1],   ///< Outside radius at -pDz
										  pars[2],   ///< Inside radius at +pDz
										  pars[3],   ///< Outside radius at +pDz
										  pars[4],   ///< Half length in z
										  pars[5],   ///< Starting phi angle
										  pars[6]    ///< Delta Phi angle
										  ), verbosity
							   );
		return true;
	} else 	if(type == "G4Para") {
		thisG4Volume->addSolid(new G4Para(vname,     ///< name
										  pars[0],   ///< Half length in x
										  pars[1],   ///< Half length in y
										  pars[2],   ///< Half length in z
										  pars[3],   ///< Angle formed by the y axis and by the plane joining the centre of the faces parallel to the z-x plane at -dy and +dy
										  pars[4],   ///< Polar angle of the line joining the centres of the faces at -dz and +dz in z
										  pars[5]    ///< Azimuthal angle of the line joining the centres of the faces at -dz and +dz in z
										  ), verbosity
							   );
		return true;
	} else 	if(type == "G4Trd") {
		thisG4Volume->addSolid(new G4Trd(vname,     ///< name
										 pars[0],   ///< Half-length along x at the surface positioned at -dz
										 pars[1],   ///< Half-length along x at the surface positioned at +dz
										 pars[2],   ///< Half-length along y at the surface positioned at -dz
										 pars[3],   ///< Half-length along y at the surface positioned at +dz
										 pars[4]    ///< Half-length along z axis
										 ), verbosity
							   );
		return true;
	}








	else {
		// PRAGMA TODO  throw exception here if solid is unknown to system
		G4cout << " " << vname << " solid " << type << " uknown! " << G4endl;
	}

	// if we are at this point the solid is not built
	if(depVerbosity) {
		G4cout << " " << vname << " solid is not built." << G4endl;
	}

	return false;
}





