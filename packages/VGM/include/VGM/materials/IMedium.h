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
/// \class VGM::IMedium
///
/// The VGM interface to tracking medium.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MEDIUM_H
#define VGM_I_MEDIUM_H

#include <string>
#include <iostream>

namespace VGM {

  class IMaterial;

  class IMedium
  {
    public:
      virtual ~IMedium() {}

      // metods
			   ///
                           /// Return its name
      virtual std::string Name() const = 0;
			   ///
                           /// Return its associated material
      virtual IMaterial*  Material() const = 0;
	                   ///
                           /// Return its unique identifier
      virtual int     Id() const = 0;
	                   ///
                           /// Return the number of defined parameters
      virtual int     NofParameters() const = 0;
	                   ///
                           /// Return the i-th parameter
      virtual double  Parameter(int i) const = 0;
  };
}

std::ostream& operator << (std::ostream& out, const VGM::IMedium& medium);

#endif //VGM_I_MEDIUM_H
