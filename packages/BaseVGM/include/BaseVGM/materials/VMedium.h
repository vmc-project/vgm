// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_materials
//
/// \class BaseVGM::VMedium
///
/// The ABC for tracking medium.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_MEDIUM_H
#define BASE_VGM_V_MEDIUM_H

#include "VGM/materials/IMedium.h"

#include <iostream>
#include <string>

namespace VGM {
class IMaterial;
}

namespace BaseVGM {

class VMedium : public virtual VGM::IMedium
{
 public:
  VMedium(VGM::IMaterial* material);
  virtual ~VMedium();

  // methods
  virtual VGM::IMaterial* Material() const;
  virtual int NofParameters() const;

 protected:
  VMedium();
  VMedium(const VMedium& rhs);

  // data members
  static const int fgkParamSize;

  VGM::IMaterial* fMaterial;
};

} // namespace BaseVGM

#endif // BASE_VGM_V_MEDIUM_H
