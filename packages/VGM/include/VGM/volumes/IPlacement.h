// $Id$
//
// Class IPlacement
// -----------------
// The VGM interface to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_PLACEMENT_H
#define VGM_I_PLACEMENT_H

#include <string>

#include "VGM/common/Axis.h"
#include "VGM/common/ThreeVector.h"
#include "VGM/common/Rotation.h"

namespace VGM {

  enum PlacementType {
    kSimplePlacement,
    kMultiplePlacement,
    //kParameterised,
    kUnknownPlacement
  };  

  class IVolume;

  class IPlacement
  {
    public:
      virtual ~IPlacement() {}
    
      // methods
      virtual PlacementType Type() const = 0;

      virtual std::string  Name() const = 0;
      virtual IVolume*     Volume() const = 0;
      virtual IVolume*     Mother() const = 0;
      virtual int          CopyNo() const = 0;

      virtual Rotation     ObjectRotation() const = 0;      
      virtual Rotation     FrameRotation() const = 0;      
      virtual ThreeVector  ObjectTranslation() const = 0;
      virtual ThreeVector  FrameTranslation() const = 0;
      virtual bool         ReflectionZ() const = 0;

      virtual bool  MultiplePlacementData(
                           Axis&   axis,
                           int&    nofItems,
                           double& width,
                           double& offset) const = 0;
  };

}

#endif //VGM_I_PLACEMENT_H
