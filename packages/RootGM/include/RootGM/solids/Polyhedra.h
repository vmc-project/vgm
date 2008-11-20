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
/// \class RootGM:: Polyhedra
///
/// VGM implementation for Root polyhedra solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_POLYHEDRA_H
#define ROOT_GM_POLYHEDRA_H

#include "BaseVGM/solids/VPolyhedra.h"

#include <string>

class TGeoPgon;

namespace RootGM {

  class Polyhedra : public BaseVGM::VPolyhedra
  {
    public:
      Polyhedra(const std::string& name, 
                double sphi, double dphi, int nofSides, int nofZPlanes,
                double* z, double* rin, double* rout);
      Polyhedra(TGeoPgon* polycone);
      virtual ~Polyhedra();

      // methods
      virtual std::string Name() const;
      virtual double  StartPhi() const;
      virtual double  DeltaPhi() const;
      virtual int     NofSides() const;
      virtual int     NofZPlanes() const;
      virtual double* ZValues() const;
      virtual double* InnerRadiusValues() const;
      virtual double* OuterRadiusValues() const;

    protected:
      Polyhedra();
      Polyhedra(const Polyhedra& rhs);

    private:
      void CreateBuffers();

      static const int fgkMaxNofZPlanes;
      static double*   fgZBuffer;
      static double*   fgRinBuffer;
      static double*   fgRoutBuffer;

      TGeoPgon* fPolyhedra;
  };

}  

#endif //ROOT_GM_POLYHEDRA_H
