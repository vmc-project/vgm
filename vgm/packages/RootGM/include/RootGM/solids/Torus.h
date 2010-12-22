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
/// \class RootGM::Torus
///
/// VGM implementation for Root torus solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TORUS_H
#define ROOT_GM_TORUS_H

#include "BaseVGM/solids/VTorus.h"

#include <string>

class TGeoTorus;

namespace RootGM {

  class Torus : public BaseVGM::VTorus
{
    public:
      Torus(const std::string& name, 
            double rin, double rout, double rax, double sphi, double dphi);
      Torus(TGeoTorus* torus);
      virtual ~Torus();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double AxialRadius() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Torus();
      Torus(const Torus& rhs);

    private:
      TGeoTorus* fTorus;
  };

}

#endif //ROOT_GM_TORUS_H
