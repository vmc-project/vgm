// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

// VGM::IMaterial output stream
// ------------------------
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IElement.h"

#include <string>

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IMaterial& material)
{
  std::string stateName;
  switch ( material.State() ) {
    case VGM::kSolid:     stateName = "Solid"; break;
    case VGM::kLiquid:    stateName = "Liquid"; break;
    case VGM::kGas:       stateName = "Gas"; break;
    case VGM::kUndefined:
    default:              stateName = "Undefined";
  }

  out << "Material: " << "\"" << material.Name() << "\""
      << "  density " << material.Density() << " g/cm3"
      << "  radlen "  << material.RadiationLength()/10.  << " cm"
      << "  intlen "  << material.NuclearInterLength()/10. << " cm"
      << "  state "   << "\"" << stateName << "\""
      << "  temperature " << material.Temperature() << " kelvin"
      << "  pressure "    << material.Pressure() << " atm"
      << std::endl;

  for (int i=0; i<material.NofElements(); i++) {
    out << "   "
        << i << "th element: " << *material.Element(i)
        << "  Elm mass fraction: " <<  material.MassFraction(i) * 100. << " %";
    if (i<material.NofElements()-1) out <<std::endl;
  }

  return out;
}
