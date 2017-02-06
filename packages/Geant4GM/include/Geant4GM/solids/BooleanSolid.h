// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::BooleanSolid
///
/// VGM implementation for Geant4 Boolean solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_BOOLEAN_SOLID_H
#define GEANT4_GM_BOOLEAN_SOLID_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VBooleanSolid.h"

#include <iostream>

class G4VSolid;
class G4BooleanSolid;
class G4DisplacedSolid;
class G4ReflectedSolid;

namespace Geant4GM {

  class BooleanSolid : public BaseVGM::VBooleanSolid
  {
    public:
      BooleanSolid(const std::string& name, 
                   VGM::BooleanType boolType,
                   VGM::ISolid* solidA, 
                   VGM::ISolid* solidB, 
                   CLHEP::HepRotation* rotation, 
                   const CLHEP::Hep3Vector& translation);
      BooleanSolid(G4BooleanSolid* booleanSolid,
                   G4ReflectedSolid* reflectedBoolean);
      virtual ~BooleanSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::BooleanType BoolType() const;
      virtual VGM::ISolid*     ConstituentSolidA() const;
      virtual VGM::ISolid*     ConstituentSolidB() const;
      virtual VGM::Transform   Displacement() const;      
      virtual bool             ToBeReflected() const;     

      // utility method
      static G4VSolid* GetConstituentSolid(
                               int index, 
                               G4BooleanSolid* booleanSolid);

    protected:
      BooleanSolid();
      BooleanSolid(const BooleanSolid& rhs);

    private:
      const G4DisplacedSolid* DisplacedSolid() const;

      G4BooleanSolid* fBooleanSolid;
      bool            fToBeReflected;
  };
  
}  

inline bool Geant4GM::BooleanSolid::ToBeReflected() const
{ return fToBeReflected; }     

#endif //GEANT4_GM_BOOLEAN_SOLID_H
