// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::Element
///
/// VGM implementation for Geant4 element.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ELEMENT_H
#define GEANT4_GM_ELEMENT_H

#include "VGM/materials/IElement.h"

#include <string>

class G4Element;

namespace Geant4GM {

  class Element : public virtual VGM::IElement
  {
    public:
      Element(const std::string& name,
              const std::string& symbol,
              double z, double a);

      Element(const std::string& name,
              const std::string& symbol,
	      const VGM::IsotopeVector& isotopes,
              const VGM::RelAbundanceVector& relAbundances);

      Element(G4Element* element);
      virtual ~Element();

      // methods
      virtual std::string Name() const;
      virtual std::string Symbol() const;

      virtual double  Z() const;
      virtual double  N() const;
      virtual double  A() const;

      virtual int     NofIsotopes() const;
      virtual VGM::IIsotope*  Isotope(int i) const;
      virtual double  RelAbundance(int i) const;

    protected:
      Element();
      Element(const Element& rhs);

    private:
      void CheckIndex(int iel) const;

      G4Element*  fElement;
  };

}

#endif //GEANT4_GM_ELEMENT_H
