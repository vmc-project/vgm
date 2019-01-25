// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VPlacement
// -----------------
// The abstract base class to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/volumes/IVolume.h"
#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

#include <iostream>

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement(VGM::IVolume* volume,
                                VGM::IVolume* motherVolume)
  : VGM::IPlacement(),
    fVolume(volume),
    fMotherVolume(motherVolume)
{
/// Standard constructor

  // Update mother volume
  if (motherVolume)
    motherVolume->AddDaughter(this);
  else {
    // check if top volume not yet set and
    // set top volume here
  }
}

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement()
  : VGM::IPlacement()
{
/// Protected default constructor
}

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement(const VPlacement& rhs)
  : VGM::IPlacement(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VPlacement::~VPlacement() {
//
}

//_____________________________________________________________________________
VGM::IVolume* BaseVGM::VPlacement::Volume() const
{
//
  return fVolume;
}

//_____________________________________________________________________________
VGM::IVolume* BaseVGM::VPlacement::Mother() const
{
//
  return fMotherVolume;
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VPlacement::Put(std::ostream& out) const
{
  out << "\"" << Name() << "\"";

  if ( Volume() )
      out << "  volume: \"" << Volume()->Name() << "\"";
  else
      out << "  volume: \"-\"";

  if ( Mother() )
      out << "  mother: \"" << Mother()->Name() << "\"";
  else
      out << "  mother: \"-\"";

  out << "  type:  \"" << VGM::PlacementTypeName(Type()) << "\"";

  if ( Type() == VGM::kSimplePlacement ) {
     out << "  copyNo: " << CopyNo()
         << "  transform: " << Transformation();
  }

  if ( Type() == VGM::kMultiplePlacement ) {
     VGM::Axis axis;
     int nofItems;
     double width;
     double offset;
     double halfGap;
     MultiplePlacementData(axis, nofItems, width, offset, halfGap);

     out << "  axis: \""  << VGM::AxisTypeName(axis) << "\""
         << "  ndiv: "    << nofItems
         << "  width: "   << width
         << "  offset: "  << offset
         << "  halfGap: " << halfGap;
  }

  return out;
}

//_____________________________________________________________________________
void BaseVGM::VPlacement::SetVolume(VGM::IVolume* volume)
{
/// Set the associated volume
/// (Needed in a special case when a volume is
///  created only when it is being placed)
///

  fVolume = volume;
}

//_____________________________________________________________________________
std::string VGM::PlacementTypeName(VGM::PlacementType typeId)
{
  // Returns the placement type name for specified typeId
  switch (typeId) {
    case kSimplePlacement:   return "Simple";    break;
    case kMultiplePlacement: return "Multiple";  break;
    //case kParameterised: return "Parameterised";  break;
    default:            return "Undefined"; break;
  };
}

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IPlacement& placement)
{
  return placement.Put(out);
}

