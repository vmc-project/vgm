// $Id$
/// \ingroup RootGM_materials
//
/// \class RootGM:: Element
///
/// VGM implementation for Root element.
///
/// Author: Ivana Hrivnacova; IPN Orsay

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
      Element(TGeoElement* element, 
              const std::string& name, double z, double a);		
      Element(TGeoElement* element);		
      virtual ~Element();
    
      // methods
      virtual std::string Name() const;
      virtual std::string Symbol() const;

      virtual double  Z() const;     
      virtual double  N() const;     
      virtual double  A() const;     

    protected:  
      Element();
      Element(const Element& rhs);
    
    private:
      void CheckIndex(int iel) const;
  
      TGeoElement*  fElement; 
      std::string   fName;
      double  fZ;
      double  fA; 
  };
  
}  

#endif //ROOT_GM_ELEMENT_H
