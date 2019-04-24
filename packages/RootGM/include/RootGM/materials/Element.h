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
/// \class RootGM::Element
///
/// VGM implementation for Root element using TGeoElement object
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_H
#define ROOT_GM_ELEMENT_H

#include "VGM/materials/IElement.h"

#include <string>

class TGeoElement;

namespace RootGM {

class Element : public virtual VGM::IElement
{
 public:
  Element(
    const std::string& name, const std::string& symbol, double z, double a);

  Element(const std::string& name, const std::string& symbol,
    const VGM::IsotopeVector& isotopes,
    const VGM::RelAbundanceVector& relAbundances);

  Element(TGeoElement* geoElement);
  virtual ~Element();

  // operators
  Element& operator=(const Element& rhs);

  // methods
  virtual std::string Name() const;
  virtual std::string Symbol() const;

  virtual double Z() const;
  virtual double N() const;
  virtual double A() const;

  virtual int NofIsotopes() const;
  virtual VGM::IIsotope* Isotope(int i) const;
  virtual double RelAbundance(int i) const;

 private:
  // not implemented
  Element(const Element& rhs);
  Element();

  void CheckIndex(int iel) const;

  TGeoElement* fElement;
};

} // namespace RootGM

#endif // ROOT_GM_ELEMENT_H
