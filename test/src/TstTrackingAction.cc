// $Id$
//
// Class TstTrackingAction
// -------------------------------
// The test tracking action
//
// Author: Ivana Hrivnacova; IPN Orsay

 
#include "TstTrackingAction.hh"

#include "G4Track.hh"
#include "G4ios.hh"
 
TstTrackingAction::TstTrackingAction()
{}

TstTrackingAction::~TstTrackingAction()
{}

void TstTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4cout << "Track position: " << track->GetPosition() 
         << " momentum direction: " <<  track->GetMomentumDirection()
	 << G4endl;
}
