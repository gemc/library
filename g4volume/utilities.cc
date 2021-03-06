// g4volume
#include "g4volume.h"


/*! \fn map<string, GOption> G4Setup::defineOptions()

 \return defines G4Setup specific options

 */
map<string, GOption> G4Setup::defineOptions()
{
	map<string, GOption> optionsMap;

	optionsMap["hall"]          = GOption("Hall Dimensions",    "20*m 20*m 20*m", "g4volumes");
	optionsMap["defaultMat"]    = GOption("Default Material",   "G4_AIR",         "g4volumes");
	optionsMap["checkOverlaps"] = GOption("Check for overlaps", 0,                "g4volumes");

	optionsMap["g4volumev"] = GOption("Geant4 Volume Verbosity", 0, "verbosity");
	optionsMap["g4volumev"].addHelp("Possible values:\n");
	optionsMap["g4volumev"].addHelp(GVERBOSITY_SILENT_D);
	optionsMap["g4volumev"].addHelp(GVERBOSITY_SUMMARY_D);
	optionsMap["g4volumev"].addHelp(GVERBOSITY_DETAILS_D);
	optionsMap["g4volumev"].addHelp(GVERBOSITY_ALL_D);

	return optionsMap;
}


