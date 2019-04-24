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
/// \class VGM::IExtrudedSolid
///
/// The VGM interface to extruded solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_EXTRUDED_SOLID_H
#define VGM_I_EXTRUDED_SOLID_H

#include "VGM/common/TwoVector.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IExtrudedSolid : public virtual ISolid
{
 public:
  virtual ~IExtrudedSolid() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the number of vertices of outline polygon
  virtual int NofVertices() const = 0;
  ///
  /// Return the index-th vertex of outline polygon
  virtual TwoVector Vertex(int index) const = 0;
  ///
  /// Return the number of planes perpendicular to the z axis
  virtual int NofZSections() const = 0;
  ///
  /// Return the z position of the iz-th plane in mm
  virtual double ZPosition(int iz) const = 0;
  ///
  /// Return the polygon offset in iz-th side
  virtual TwoVector Offset(int iz) const = 0;
  ///
  /// Return the polygon scale in iz-th side
  virtual double Scale(int iz) const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IExtrudedSolid& xtru);

#endif // VGM_I_EXTRUDED_SOLID_H
