// $Id$
//
// Class IMedium
// ---------------
// The VGM interface to tracking medium.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MEDIUM_H
#define VGM_I_MEDIUM_H

#include <string>
#include <iostream>

namespace VGM {

  class IMaterial;

  class IMedium
  {
    public:
      virtual ~IMedium() {}
    
      // methods
      virtual std::string Name() const = 0;

      virtual IMaterial*  Material() const = 0;

      virtual int     Id() const = 0;
      virtual int     NofParameters() const = 0;
      virtual double  Parameter(int i) const = 0;
  };
}  

std::ostream& operator << (std::ostream& out, const VGM::IMedium& medium);

#endif //VGM_I_MEDIUM_H
