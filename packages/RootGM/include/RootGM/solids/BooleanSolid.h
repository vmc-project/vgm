// $Id$
/// \ingroup RootGM_solids
//
/// \class RootGM:: BooleanSolid
///
/// VGM implementation for Root Boolean solid
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_BOOLEAN_SOLID_H
#define ROOT_GM_BOOLEAN_SOLID_H

#include <iostream>

#include <TGeoMatrix.h>

#include "VGM/common/Transform.h"

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

      virtual VGM::BooleanType  BoolType() const;
      virtual VGM::ISolid*      ConstituentSolidA() const;
      virtual VGM::ISolid*      ConstituentSolidB() const;
      virtual VGM::Transform    Displacement() const;      

      // utility method
      static TGeoShape* GetConstituentSolid(
                                int index, 
                                TGeoCompositeShape* compositeShape);
 
    protected:
      BooleanSolid();
      BooleanSolid(const BooleanSolid& rhs);

    private:
      static const char fgkIntersectionChar; 
      static const char fgkSubtractionChar; 
      static const char fgkUnionChar; 
      static const char fgkSeparator; 
  
      TGeoCompositeShape* fCompositeShape;
  };

}

#endif //ROOT_GM_BOOLEAN_SOLID_H
