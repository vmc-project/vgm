//
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
// Class TstRunAction
// ----------------------------------------
// The test run action
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TstRunAction_h
#define TstRunAction_h 1

#include "G4UserRunAction.hh"

#include <TStopwatch.h>

class G4Timer;
class G4Run;

class TstRunAction : public G4UserRunAction
{
 public:
  TstRunAction();
  ~TstRunAction();

 public:
  void BeginOfRunAction(const G4Run* aRun);
  void EndOfRunAction(const G4Run* aRun);

 private:
  G4Timer* timer;
  TStopwatch timer2;
};

#endif
