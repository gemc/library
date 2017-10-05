// g4volume
#include "g4NativeSetupFactory.h"

// mlibrary
#include "gstring.h"
using namespace gstring;

// check that the number of parameters matches the geant4 constructor
vector<double> G4NativeSetupFactory::checkAndReturnParameters(GVolume *s)
{

	// PRAGMA TODO: check non zero pars for various constructor
	// Check that the pars are not zero, for example:
	// checking that G4Box does not have null dimensions
	//	for(unsigned i=0; i<parameters.size(); i++) {
	//		if(getG4Number(parameters[i]) == 0) {
	//			cout <<   " !! Warning: G4Box has one side null!" << endl;
	//		}
	//	}


	set<int> possibleNumberOfParameters;
	string type = s->getType();
	string name = s->getName();

	vector<double> parameters = getG4NumbersFromString(s->getParameters());

	int actualNumberOfParameters = (int) parameters.size();

		 if(type == "G4Box")     possibleNumberOfParameters = {3};
	else if(type == "G4Tubs")    possibleNumberOfParameters = {5};
	else if(type == "G4CutTubs") possibleNumberOfParameters = {11};
	else if(type == "G4Cons")    possibleNumberOfParameters = {7};
	else if(type == "G4Para")    possibleNumberOfParameters = {6};
	else if(type == "G4Trd")     possibleNumberOfParameters = {5};
	else if(type == "G4Trap")    possibleNumberOfParameters = {4, 11};
	else if(type == "G4Sphere")  possibleNumberOfParameters = {6};
	else if(type == "G4Orb")     possibleNumberOfParameters = {1};
	else if(type == "G4Torus")   possibleNumberOfParameters = {5};

	// polycons are special
	else if(type == "G4Polycone" || type == "G4GenericPolycone")  {
		// the first constructor must have a number of pars multiple of 3
		// the second constructor must have a number of pars (-3) multiple of 2
		if(actualNumberOfParameters%3 !=0 && (actualNumberOfParameters - 3)%2 != 0) {
			cerr << " !!! Fatal Error: the number of parameters in the constructor of " << name << ", " << type
			<< " is " << actualNumberOfParameters <<  ":" << s->getParameters() << endl;

			cerr << "      This does not match a " << type <<". Exiting." << endl << endl;
			exit(99);
		} else {
			return parameters;
		}
	}

	// polyhedras are special
	else if(type == "G4Polyhedra") {
		// the first constructor must have a number of pars (-4) multiple of 3
		// the second constructor must have a number of pars (-4) multiple of 2
		if((actualNumberOfParameters - 4)%3 !=0 && (actualNumberOfParameters - 3)%2 != 0) {
			cerr << " !!! Fatal Error: the number of parameters in the constructor of " << name << ", " << type
			<< " is " << actualNumberOfParameters <<  ":" << s->getParameters() << endl;

			cerr << "      This does not match a " << type <<". Exiting." << endl << endl;
			exit(99);
		} else {
			return parameters;
		}
	}
	
	else if(type == "G4EllipticalTube") possibleNumberOfParameters = {3};
	else if(type == "G4Ellipsoid")      possibleNumberOfParameters = {5};
	else if(type == "G4EllipticalCone") possibleNumberOfParameters = {4};
	else if(type == "G4Paraboloid")     possibleNumberOfParameters = {3};
	else if(type == "G4Hype")           possibleNumberOfParameters = {5};
	else if(type == "G4Tet")            possibleNumberOfParameters = {12, 13};
	else if(type == "G4TwistedBox")     possibleNumberOfParameters = {4};
	else if(type == "G4TwistedTrap")    possibleNumberOfParameters = {5, 11};
	else if(type == "G4TwistedTrd")     possibleNumberOfParameters = {6};
	else if(type == "G4TwistedTubs")    possibleNumberOfParameters = {5};


	if(possibleNumberOfParameters.find(actualNumberOfParameters) == possibleNumberOfParameters.end() ) {
		cerr << " !!! Fatal Error: the number of parameters in the constructor of " << name << ", " << type
		<< " is " << actualNumberOfParameters <<  ":" << s->getParameters() << endl;

		cerr << "      This does not match a " << type <<". Exiting." << endl << endl;
		exit(99);
	}

	return parameters;
}




