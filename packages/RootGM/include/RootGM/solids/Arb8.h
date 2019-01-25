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
/// \class RootGM::Arb8
///
/// VGM implementation for Root Arb8 solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ARB8_H
#define ROOT_GM_ARB8_H

#include "BaseVGM/solids/VArb8.h"

#include <string>
#include <vector>

class TGeoArb8;

namespace RootGM {

  class Arb8 : public BaseVGM::VArb8
  {
    public:
      Arb8(const std::string& name,
           double hz,
           std::vector<VGM::TwoVector> vertices);
      Arb8(TGeoArb8* arb8);
      virtual ~Arb8();

      // methods
      virtual std::string     Name() const;
      virtual int             NofVertices() const;
      virtual VGM::TwoVector  Vertex(int index) const;
      virtual double          TwistAngle(int index) const;
      virtual double          ZHalfLength() const;

    protected:
      Arb8();
      Arb8(const Arb8& rhs);

      static const int fgkNofVertices;

      TGeoArb8* fArb8;
  };

}

#endif //ROOT_GM_ARB8_H
