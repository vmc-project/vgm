// $Id$
//
// Class BooleanSolid
// ---------------------
// VGM implementation for Geant4 Boolean solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_BOOLEAN_SOLID_H
#define GEANT4_GM_BOOLEAN_SOLID_H

#include <iostream>

#include "VGM/common/Rotation.h"
#include "VGM/common/ThreeVector.h"

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
      virtual VGM::ISolid* ConstituentSolidA() const;
      virtual VGM::ISolid* ConstituentSolidB() const;
      virtual VGM::Rotation     DisplacementObjectRotation() const;      
      virtual VGM::Rotation     DisplacementFrameRotation() const;      
      virtual VGM::ThreeVector  DisplacementObjectTranslation() const;
      virtual VGM::ThreeVector  DisplacementFrameTranslation() const;
      virtual bool              DisplacementReflectionZ() const;

      // utility method
      static G4VSolid* GetConstituentSolid(
                          int index, 
                          G4BooleanSolid* booleanSolid);

    protected:
      BooleanSolid() : BaseVGM::VBooleanSolid() {}
      BooleanSolid(const BooleanSolid& rhs) : BaseVGM::VBooleanSolid(rhs) {}

    private:
      const G4DisplacedSolid* DisplacedSolid() const;

      G4BooleanSolid* fBooleanSolid;
  };
  
}  

#endif //GEANT4_GM_BOOLEAN_SOLID_H
