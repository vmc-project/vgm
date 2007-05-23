// $Id$

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstVisManager
// -------------------
// The test visualisation manager
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TST_VIS_MANAGER_H
#define TST_VIS_MANAGER_H

#ifdef G4VIS_USE

#include "G4VisManager.hh"

class TstVisManager: public G4VisManager 
{
  public:
    TstVisManager ();

  private:
    void RegisterGraphicsSystems ();
};

#endif //G4VIS_USE
#endif //TST_VIS_MANAGER_H
