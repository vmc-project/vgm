// $Id$
//
// Class VPlacement
// -----------------
// The abstract base class to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_PLACEMENT_H
#define BASE_VGM_V_PLACEMENT_H

#include "VGM/volumes/IPlacement.h"

namespace BaseVGM {

  class VGM::IVolume;

  class VPlacement : public virtual VGM::IPlacement
  {
    public:
      VPlacement(VGM::IVolume* volume, 
                 VGM::IVolume* motherVolume);
      virtual ~VPlacement();
    
      // methods
      virtual std::string     Name() const = 0;
      virtual VGM::IVolume*   Volume() const;
      virtual VGM::IVolume*   Mother() const;
      virtual int             CopyNo() const = 0;
      virtual VGM::Transform  Transformation() const = 0;      

      virtual bool  MultiplePlacementData(
                             VGM::Axis&  axis,
                             int&     nofDivisions,
                             double&  width,
                             double&  offset) const = 0;
			       
      void SetVolume(VGM::IVolume* volume);			       
 
    protected:
      VPlacement() : VGM::IPlacement() {}
      VPlacement(const VPlacement& rhs) : VGM::IPlacement(rhs) {}
    
    private:
      VGM::IVolume*  fVolume;
      VGM::IVolume*  fMotherVolume;
  };

}

#endif //BASE_VGM_V_PLACEMENT_H
