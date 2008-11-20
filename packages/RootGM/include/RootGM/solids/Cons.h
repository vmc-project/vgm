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
/// \class RootGM:: Cons
///
/// VGM implementation for Root cons solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_CONS_H
#define ROOT_GM_CONS_H

#include "BaseVGM/solids/VCons.h"

#include <string>

class TGeoCone;

namespace RootGM {

  class Cons : public BaseVGM::VCons
  {
    public:
      Cons(const std::string& name, 
           double rin1, double rout1, double rin2, double rout2,
	   double hz, double sphi, double dphi);
      Cons(TGeoCone* cons);
      virtual ~Cons();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadiusMinusZ() const ;
      virtual double OuterRadiusMinusZ() const;
      virtual double InnerRadiusPlusZ() const;
      virtual double OuterRadiusPlusZ() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Cons();
      Cons(const Cons& rhs);

    private:
      TGeoCone* fCons;
  };

}

#endif //ROOT_GM_CONS_H
