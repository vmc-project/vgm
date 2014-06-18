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
/// \class RootGM::Hype
///
/// VGM implementation for Root hyperboloid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_HYPE_H
#define ROOT_GM_HYPE_H

#include "BaseVGM/solids/VHype.h"

#include <string>

class TGeoHype;

namespace RootGM {

  class Hype : public BaseVGM::VHype
  {
    public:
      Hype(const std::string& name, 
           double r1, double r2, double stereo1, double stereo2, double hz);
      Hype(TGeoHype* hype);
      virtual ~Hype();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double InnerStereoAngle() const;
      virtual double OuterRadius() const;
      virtual double OuterStereoAngle() const;
      virtual double ZHalfLength() const;

    protected:
      Hype();
      Hype(const Hype& rhs);

    private:
      TGeoHype* fHype;
  };

}

#endif //ROOT_GM_HYPE_H
