// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM::Tubs
///
/// VGM implementation for Root tubs solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TUBS_H
#define ROOT_GM_TUBS_H

#include "BaseVGM/solids/VTubs.h"

#include <string>

class TGeoTube;

namespace RootGM {

class Tubs : public BaseVGM::VTubs
{
 public:
  Tubs(const std::string& name, double rin, double rout, double hz, double sphi,
    double dphi);
  Tubs(TGeoTube* tubs);
  virtual ~Tubs();

  // methods
  virtual std::string Name() const;
  virtual double InnerRadius() const;
  virtual double OuterRadius() const;
  virtual double ZHalfLength() const;
  virtual double StartPhi() const;
  virtual double DeltaPhi() const;

 protected:
  Tubs();
  Tubs(const Tubs& rhs);

 private:
  TGeoTube* fTubs;
};

} // namespace RootGM

#endif // ROOT_GM_TUBS_H
