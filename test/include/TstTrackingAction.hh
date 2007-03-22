// $Id$
//
// Class TstTrackingtAction
// -------------------------------
// The test tracking action
//
// Author: Ivana Hrivnacova; IPN Orsay

 
#ifndef TST_TRACKING_ACTION_H
#define TST_TRACKING_ACTION_H

#include "G4UserTrackingAction.hh"

class G4Track;

class TstTrackingAction : public G4UserTrackingAction
{
  public:
    TstTrackingAction();
   ~TstTrackingAction();

  public:
    virtual void PreUserTrackingAction(const G4Track*);
};

#endif

    
