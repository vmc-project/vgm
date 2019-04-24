// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_volumes
//
/// \class BaseVGM::VPlacement
///
/// The abstract base class to positions of volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_PLACEMENT_H
#define BASE_VGM_V_PLACEMENT_H

#include "VGM/volumes/IPlacement.h"

namespace VGM {
class IVolume;
}

namespace BaseVGM {

class VPlacement : public virtual VGM::IPlacement
{
 public:
  VPlacement(VGM::IVolume* volume, VGM::IVolume* motherVolume);
  virtual ~VPlacement();

  // methods

  virtual std::string Name() const = 0;
  virtual VGM::IVolume* Volume() const;
  virtual VGM::IVolume* Mother() const;
  virtual int CopyNo() const = 0;
  virtual VGM::Transform Transformation() const = 0;

  virtual bool MultiplePlacementData(VGM::Axis& axis, int& nofDivisions,
    double& width, double& offset, double& halfGap) const = 0;

  /// Put the printing of the placement parameters
  /// in the out stream
  virtual std::ostream& Put(std::ostream& out) const;

  void SetVolume(VGM::IVolume* volume);

 protected:
  VPlacement();
  VPlacement(const VPlacement& rhs);

 private:
  VGM::IVolume* fVolume;
  VGM::IVolume* fMotherVolume;
};

} // namespace BaseVGM

#endif // BASE_VGM_V_PLACEMENT_H
