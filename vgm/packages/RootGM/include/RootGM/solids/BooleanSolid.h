// $Id$
//
// Class BooleanSolid
// ---------------------
// VGM implementation for Root Boolean solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_BOOLEAN_SOLID_H
#define ROOT_GM_BOOLEAN_SOLID_H

#include <iostream>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "BaseVGM/solids/VBooleanSolid.h"

class TGeoCompositeShape;

namespace RootGM {

  class BooleanSolid : public BaseVGM::VBooleanSolid
  {
    public:
      BooleanSolid(const std::string& name, 
                   VGM::BooleanType boolType,
                   VGM::ISolid* solidA, VGM::ISolid* solidB, 
                   HepRotation* rotation, const Hep3Vector& translation);
      BooleanSolid(const std::string& name, 
                   VGM::BooleanType boolType,
                   VGM::ISolid* solidA, VGM::ISolid* solidB, 
                   const HepTransform3D& transform3D);
      BooleanSolid(TGeoCompositeShape* compositeShape);
      virtual ~BooleanSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::BooleanType BoolType() const;
      virtual VGM::ISolid* ConstituentSolidA() const;
      virtual VGM::ISolid* ConstituentSolidB() const;
      virtual HepRotation  DisplacementObjectRotation() const;      
      virtual HepRotation  DisplacementFrameRotation() const;      
      virtual Hep3Vector   DisplacementObjectTranslation() const;
      virtual Hep3Vector   DisplacementFrameTranslation() const;
      virtual bool         DisplacementReflectionZ() const;

      // utility method
      static TGeoShape* GetConstituentSolid(
                           int index, 
                           TGeoCompositeShape* compositeShape);

    protected:
      BooleanSolid() : BaseVGM::VBooleanSolid() {}
      BooleanSolid(const BooleanSolid& rhs) : BaseVGM::VBooleanSolid(rhs) {}

    private:
      void  CreateBooleanSolid(
                       const std::string& name, 
                       VGM::BooleanType boolType,
                       VGM::ISolid* solidA, VGM::ISolid* solidB,
		       TGeoMatrix* displacementB);

      HepTransform3D  Displacement() const;
  
      static const char fgkIntersectionChar; 
      static const char fgkSubtractionChar; 
      static const char fgkUnionChar; 
      static const char fgkSeparator; 
  
      TGeoCompositeShape* fCompositeShape;
  };

}

#endif //ROOT_GM_BOOLEAN_SOLID_H
