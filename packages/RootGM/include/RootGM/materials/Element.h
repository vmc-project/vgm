// $Id$
//
// Class Element
// ---------------
// VGM implementation for Root element.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_H
#define ROOT_GM_ELEMENT_H

#include <string>

#include "VGM/materials/IElement.h"

class TGeoElement;

namespace RootGM {

  class Element : public virtual VGM::IElement
  {
    public:
      Element(const std::string& name, 
              const std::string& symbol,      
              double z, double a); 
      Element(TGeoElement* element);		
      virtual ~Element();
    
      // methods
      virtual std::string Name() const;
      virtual std::string Symbol() const;

      virtual double  Z() const;     
      virtual double  N() const;     
      virtual double  A() const;     

    protected:  
      Element() : VGM::IElement() {}  
      Element(const Element& rhs) : VGM::IElement(rhs) {}
    
    private:
      void CheckIndex(int iel) const;
  
      TGeoElement*  fElement;  
  };
  
}  

#endif //ROOT_GM_ELEMENT_H
