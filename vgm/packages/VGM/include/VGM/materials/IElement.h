// $Id$
//
// Class IElement
// ---------------
// The VGM interface to elements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ELEMENT_H
#define VGM_I_ELEMENT_H

#include <string>
#include <iostream>

namespace VGM {
  class IElement
  {
    public:
      virtual ~IElement() {}
    
      // methods
      virtual std::string Name() const = 0;
      virtual std::string Symbol() const = 0;

      virtual double  Z() const = 0;     
      virtual double  N() const = 0;     
      virtual double  A() const = 0; 
  };       
} 

std::ostream& operator << (std::ostream& out, const VGM::IElement& element);

#endif //VGM_I_ELEMENT_H
