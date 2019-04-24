// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::IPolyhedra
///
/// The VGM interface to polyhedra solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_POLYHEDRA_H
#define VGM_I_POLYHEDRA_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IPolyhedra : public virtual ISolid
{
 public:
  virtual ~IPolyhedra() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return starting phi angle of the segment in deg
  virtual double StartPhi() const = 0;
  ///
  /// Return opening phi angle of the segment in deg
  virtual double DeltaPhi() const = 0;
  ///
  /// Return number of sides of the cross section
  /// between the given phi limits
  virtual int NofSides() const = 0;
  ///
  /// Return number of planes perpendicular to the z axis
  virtual int NofZPlanes() const = 0;
  ///
  /// Return the array of z positions of the planes in mm
  virtual double* ZValues() const = 0;
  ///
  /// Return the array of innner radius of the planes in mm
  virtual double* InnerRadiusValues() const = 0;
  ///
  /// Return the array of outer radius of the planes in mm
  virtual double* OuterRadiusValues() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IPolyhedra& polyhedra);

#endif // VGM_I_POLYHEDRA_H
