// $Id$
/// \ingroup Geant4GM_volumes
//
/// \class Geant4GM::Placement
///
/// VGM implementation for Geant4 positions of volumes.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PLACEMENT_H
#define GEANT4_GM_PLACEMENT_H

#include <string>

#include "G4VPhysicalVolume.hh"
#include "geomdefs.hh"

#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

class VGM::IVolume;

namespace Geant4GM {

  class Placement : public BaseVGM::VPlacement
  {
    public:
      Placement(const std::string& name, 
                int copyNo,
                VGM::IVolume* volume, 
		VGM::IVolume* motherVolume,
                HepRotation* rotation, const Hep3Vector& translation);
      Placement(const std::string& name,
                VGM::IVolume* volume, 
		VGM::IVolume* motherVolume,
                VGM::Axis axis, int nofItems, double  width, double offset);
      Placement(VGM::IVolume* volume, 
                VGM::IVolume* motherVolume,
                G4VPhysicalVolume* pv);
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
      Placement();
      Placement(const Placement& rhs);
      
    private:
      EAxis GetAxis(VGM::Axis axis) const;
      VGM::Axis GetAxis(EAxis axis) const;
  
      G4VPhysicalVolume*  fPhysicalVolume;
  };

}

#endif //GEANT4_GM_PLACEMENT_H
