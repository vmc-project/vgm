// $Id$
//
// Class IMaterial
// ---------------
// The VGM interface to materials.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MATERIAL_H
#define VGM_I_MATERIAL_H

#include <string>
#include <iostream>
#include <vector>

namespace VGM {

  class IElement;

  typedef std::vector<IElement*>  ElementVector;
  typedef std::vector<double>     MassFractionVector;

  class IMaterial
  {
    public:
      virtual ~IMaterial() {}
    
      // methods
      virtual std::string Name() const = 0;

      virtual double  Density() const = 0;
      virtual double  RadiationLength() const = 0;
      virtual double  NuclearInterLength() const = 0;
    
      virtual int        NofElements() const = 0;
      virtual IElement*  Element(int iel) const = 0;
      virtual double     MassFraction(int iel) const = 0 ;

      //virtual void  AddElements(const ElementVector& elements,
      //                          const MassFractionVector& massFractions) = 0;
  };
}  

std::ostream& operator << (std::ostream& out, const VGM::IMaterial& material);

#endif //VGM_I_MATERIAL_H
