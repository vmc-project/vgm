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

#include <TGeoMatrix.h>

#include "VGM/common/ThreeVector.h"
#include "VGM/common/Rotation.h"

#include "BaseVGM/solids/VBooleanSolid.h"

class TGeoCompositeShape;

namespace RootGM {

  class BooleanSolid : public BaseVGM::VBooleanSolid
  {
    public:
      BooleanSolid(const std::string& name, 
                   VGM::BooleanType boolType,
                   VGM::ISolid* solidA, VGM::ISolid* solidB, 
                   TGeoMatrix* displacementB);
      BooleanSolid(TGeoCompositeShape* compositeShape);
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

      TGeoHMatrix  Displacement() const;
  
      static const char fgkIntersectionChar; 
      static const char fgkSubtractionChar; 
      static const char fgkUnionChar; 
      static const char fgkSeparator; 
  
      TGeoCompositeShape* fCompositeShape;
  };

}

#endif //ROOT_GM_BOOLEAN_SOLID_H
