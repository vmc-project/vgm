// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_materials
//
/// \class RootGM:: ElementGeo
///
/// VGM implementation for Root element using TGeoElement
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_GEO_H
#define ROOT_GM_ELEMENT_GEO_H

#include <string>

#include "VGM/materials/IElement.h"

class TGeoElement;

namespace RootGM {

  class ElementGeo : public virtual VGM::IElement
  {
    public:
      ElementGeo(TGeoElement* geoElement);
      ElementGeo();
      virtual ~ElementGeo();
    
      // methods
      virtual std::string Name() const;
      virtual std::string Symbol() const;

      virtual double  Z() const;     
      virtual double  N() const;     
      virtual double  A() const;     

      virtual int     NofIsotopes() const;
      virtual VGM::IIsotope*  Isotope(int /*i*/) const;
      virtual double  RelAbundance(int /*i*/) const;
    
    private:
      TGeoElement* fElement; 
  };
  
}  

#endif //ROOT_GM_ElementGeo_H
