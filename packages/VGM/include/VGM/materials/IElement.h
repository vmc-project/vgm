// $Id$
/// \ingroup VGM_materials
//
/// \class VGM::IElement
///
/// The VGM interface to elements.
///
/// Author: Ivana Hrivnacova; IPN Orsay

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
			   ///
                           /// Return the name of this element
      virtual std::string Name() const = 0;
			   ///
                           /// Return the symbol of this element
      virtual std::string Symbol() const = 0;
		           ///
                           /// Return the effective atomic number
      virtual double  Z() const = 0;     
		           ///
                           /// Return the effective number of nucleons
      virtual double  N() const = 0;     
		           ///
                           /// Return the effective effective mass of a mole 
			   /// in g/mole
      virtual double  A() const = 0; 
  };       
} 

std::ostream& operator << (std::ostream& out, const VGM::IElement& element);

#endif //VGM_I_ELEMENT_H
