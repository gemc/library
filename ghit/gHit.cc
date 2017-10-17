// gemc
#include "gHit.h"

// geant4
#include "G4VVisManager.hh"

// MT definitions, as from:
// https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
G4ThreadLocal G4Allocator<GHit>* GHitAllocator = 0;

GHit::GHit(GTouchable gt, string cScheme) : touchableId(gt), colorSchema(cScheme)
{
	
}



bool GHit::setColorSchema()
{

	return false;
}


void GHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

	if(pVVisManager) {
		setColorSchema();
		
//		G4Circle circle(pos[0]);
//		circle.SetFillStyle(G4Circle::filled);
//
//
//		// summing all energies
//		double Etot = 0;
//		for(unsigned int i=0; i<edep.size(); i++)
//			Etot += edep[i];
//
//		if(Etot > SID.signalThreshold)
//		{
//			circle.SetVisAttributes(G4VisAttributes(colour_hit));
//			circle.SetScreenSize(5);
//		}
//		else if(Etot > 0 && Etot <= SID.signalThreshold)
//		{
//			circle.SetVisAttributes(G4VisAttributes(colour_touch));
//			circle.SetScreenSize(4);
//		}
//		else if(Etot == 0)
//		{
//			circle.SetVisAttributes(G4VisAttributes(colour_passby));
//			circle.SetScreenSize(3);
//		}
//
//		if(PID[0] != 0) {
//			pVVisManager->Draw(circle);
//		}
	}
}

