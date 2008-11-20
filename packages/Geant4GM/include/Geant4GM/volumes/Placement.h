// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_volumes
//
/// \class Geant4GM::Placement
///
/// VGM implementation for Geant4 positions of volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PLACEMENT_H
#define GEANT4_GM_PLACEMENT_H

#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

#include "geomdefs.hh"

#include <string>

class G4VPhysicalVolume;

namespace VGM {
  class IVolume;
}

namespace Geant4GM {

  class Placement : public BaseVGM::VPlacement
  {
    public:
      Placement(VGM::IVolume* volume, 
                VGM::IVolume* motherVolume,
                G4VPhysicalVolume* pv);
      virtual ~Placement();
    
      // static methods
      static EAxis GetAxis(VGM::Axis axis);
      static VGM::Axis GetAxis(EAxis axis);

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
      Placement();
      Placement(const Placement& rhs);
      
    private:
      G4VPhysicalVolume*  fPhysicalVolume;
  };

}

#endif //GEANT4_GM_PLACEMENT_H
