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
// Class VMedium
// ---------------
// The ABC for tracking medium.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"

#include "BaseVGM/materials/VMedium.h"

const int BaseVGM::VMedium::fgkParamSize = 20;

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IMedium& medium)
{
  out << "Medium: " << "\"" << medium.Name() << "\""
      << "  material " << medium.Name() << " g/cm3"
      << "  parameters:";

  for (int i=0; i<medium.NofParameters(); i++)
    out << "  " << medium.Parameter(i);

  return out;
}

//_____________________________________________________________________________
BaseVGM::VMedium::VMedium(VGM::IMaterial* material)
  : VGM::IMedium(),
    fMaterial(material)
{
/// Standard constructor
}


//_____________________________________________________________________________
BaseVGM::VMedium::VMedium()
  : VGM::IMedium()
{
/// Protected default constructor
}

//_____________________________________________________________________________
BaseVGM::VMedium::VMedium(const VMedium& rhs)
  : VGM::IMedium(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VMedium::~VMedium() {
//
}

//_____________________________________________________________________________
VGM::IMaterial*
BaseVGM::VMedium::Material() const
{
//
  return fMaterial;
}

//_____________________________________________________________________________
int  BaseVGM::VMedium::NofParameters() const
{
  return fgkParamSize;
}

