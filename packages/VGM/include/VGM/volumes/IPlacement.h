// $Id$
/// \ingroup VGM_volumes
//
/// \class VGM::IPlacement
///
/// The VGM interface to positions of volumes.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_PLACEMENT_H
#define VGM_I_PLACEMENT_H

#include <string>

#include "VGM/common/Axis.h"
#include "VGM/common/Transform.h"

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
			     ///
                             /// Return the type of this placement
      virtual PlacementType Type() const = 0;
			     ///
                             /// Return the name of this placement
      virtual std::string   Name() const = 0;

                             ///
			     /// Return the associated volume
      virtual IVolume*      Volume() const = 0;
			     ///
                             /// Return the associated mother volume
      virtual IVolume*      Mother() const = 0;
			     ///
                             /// Return the copy number of this placement
      virtual int           CopyNo() const = 0;

			     ///
                             /// Return the 3D transformation
			     /// (if simple placement)
      virtual Transform     Transformation() const = 0;      
			     ///
                             /// Fill the multiple placement data
			     /// if relevant and return true;
                             /// return false if not multiple placement
      virtual bool  MultiplePlacementData(
                           VGM::Axis&  axis,
                           int&        nofItems,
                           double&     width,
                           double&     offset) const = 0;
  };

}

#endif //VGM_I_PLACEMENT_H
