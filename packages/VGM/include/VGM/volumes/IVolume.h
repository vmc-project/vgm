// $Id$
//
// Class IVolume
// ---------------
// The VGM interface to volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_VOLUME_H
#define VGM_I_VOLUME_H

#include <string>
#include <iostream>

namespace VGM {

  class ISolid;
  class IPlacement;

  class IVolume
  {
    public:
      virtual ~IVolume() {}
    
      // methods
      virtual std::string  Name() const = 0;
      virtual std::string  MaterialName() const = 0;
      virtual std::string  MediumName() const = 0;

      virtual ISolid*      Solid() const = 0;
      virtual int          NofDaughters() const = 0;
      virtual IPlacement*  Daughter(int i) const = 0;
    
      virtual void  AddDaughter(IPlacement* daughter) = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IVolume& volume);

#endif //VGM_I_VOLUME_H
