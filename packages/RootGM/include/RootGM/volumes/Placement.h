// $Id$
//
// Class Placement
// ------------------
// VGM implementation for Root positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PLACEMENT_H
#define ROOT_GM_PLACEMENT_H

#include <string>

#include <TGeoMatrix.h>
#include <TGeoNode.h>

#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

class TGeoPatternFinder;

class VGM::IVolume;

namespace RootGM {

  class Placement : public BaseVGM::VPlacement
  {
    public:
      Placement(
         const std::string& name, 
	 int copyNo,
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
	 TGeoMatrix* transformation);
      Placement(
         const std::string& name, 
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
         VGM::Axis axis, int nofItems, double  width, double offset);
      Placement(
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
         TGeoNode* node);
      virtual ~Placement();
    
      // methods
      virtual VGM::PlacementType Type() const;
      virtual std::string        Name() const;
      virtual int                CopyNo() const;
      virtual VGM::Transform     Transformation() const;      

      virtual bool  MultiplePlacementData(
                                VGM::Axis&  axis,
                                int&     nofItems,
                                double&  width,
                                double&  offset) const;

    protected:
      Placement(const Placement& rhs) : BaseVGM::VPlacement(rhs) {}
      Placement() : BaseVGM::VPlacement() {}

    private:
      // data members
      TGeoNode*    fGeoNode;
      std::string  fName;
  };

}

#endif //ROOT_GM_PLACEMENT_H
