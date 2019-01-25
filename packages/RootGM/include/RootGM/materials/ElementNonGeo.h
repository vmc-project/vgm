// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2010 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_materials
//
/// \class RootGM::ElementNonGeo
///
/// VGM implementation for Root element which is not represented via TGeoElement
/// object in Root geometry
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_NON_GEO_H
#define ROOT_GM_ELEMENT_NON_GEO_H

#include "VGM/materials/IElement.h"

#include <string>

namespace RootGM {

  class ElementNonGeo : public virtual VGM::IElement
  {
    public:
      ElementNonGeo(const std::string& name,
              const std::string& symbol,
              double z, double a);
      virtual ~ElementNonGeo();

      // methods
      virtual std::string Name() const;
      virtual std::string Symbol() const;

      virtual double  Z() const;
      virtual double  N() const;
      virtual double  A() const;

      virtual int     NofIsotopes() const;
      virtual VGM::IIsotope*  Isotope(int i) const;
      virtual double  RelAbundance(int i) const;

    private:
      ElementNonGeo(const ElementNonGeo& rhs);
      ElementNonGeo();

      void   CheckIndex(int iel) const;

      std::string   fName;
      std::string   fSymbol;
      double  fZ;
      double  fN;
      double  fA;
  };

}

#endif //ROOT_GM_ELEMENT_NON_GEO_H
