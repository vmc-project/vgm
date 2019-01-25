// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_materials
//
/// \class VGM::IIsotope
///
/// The VGM interface to elements.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ISOTOPE_H
#define VGM_I_ISOTOPE_H

#include <string>
#include <iostream>

namespace VGM {
  class IIsotope
  {
    public:
      virtual ~IIsotope() {}

      // methods
			   ///
                           /// Return the name of this element
      virtual std::string Name() const = 0;
		           ///
                           /// Return the effective atomic number
      virtual int     Z() const = 0;
		           ///
                           /// Return the effective number of nucleons
      virtual int     N() const = 0;
		           ///
                           /// Return the effective effective mass of a mole
			   /// in g/mole
      virtual double  A() const = 0;
  };
}

std::ostream& operator << (std::ostream& out, const VGM::IIsotope& isotope);

#endif //VGM_I_ISOTOPE_H
