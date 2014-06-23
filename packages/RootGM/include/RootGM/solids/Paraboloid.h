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
/// \class RootGM::Paraboloid
///
/// VGM implementation for Root paraboloid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PARABOLOID_H
#define ROOT_GM_PARABOLOID_H

#include "BaseVGM/solids/VParaboloid.h"

#include <string>

class TGeoParaboloid;

namespace RootGM {

  class Paraboloid : public BaseVGM::VParaboloid
  {
    public:
      Paraboloid(const std::string& name, 
                 double r1, double r2, double hz);
      Paraboloid(TGeoParaboloid* paraboloid);
      virtual ~Paraboloid();

      // methods
      virtual std::string Name() const;
      virtual double RadiusMinusZ() const ;
      virtual double RadiusPlusZ() const;
      virtual double ZHalfLength() const;

    protected:
      Paraboloid();
      Paraboloid(const Paraboloid& rhs);

    private:
      TGeoParaboloid* fParaboloid;
  };

}

#endif //ROOT_GM_PARABOLOID_H
