// $Id$
/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::BooleanSolid
///
/// VGM implementation for Geant4 Boolean solid
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_BOOLEAN_SOLID_H
#define GEANT4_GM_BOOLEAN_SOLID_H

#include <iostream>

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VBooleanSolid.h"

class G4BooleanSolid;

namespace Geant4GM {

  class BooleanSolid : public BaseVGM::VBooleanSolid
  {
    public:
      BooleanSolid(const std::string& name, 
                   VGM::BooleanType boolType,
                   VGM::ISolid* solidA, 
		   VGM::ISolid* solidB, 
                   HepRotation* rotation, 
		   const Hep3Vector& translation);
      BooleanSolid(G4BooleanSolid* booleanSolid);
      virtual ~BooleanSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::BooleanType BoolType() const;
      virtual VGM::ISolid*     ConstituentSolidA() const;
      virtual VGM::ISolid*     ConstituentSolidB() const;
      virtual VGM::Transform   Displacement() const;      

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
  };
  
}  

#endif //GEANT4_GM_BOOLEAN_SOLID_H
