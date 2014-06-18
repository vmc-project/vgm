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
/// \class RootGM::ExtrudedSolid
///
/// VGM implementation for Root extruded solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_EXTRUDED_SOLID_H
#define ROOT_GM_EXTRUDED_SOLID_H

#include "BaseVGM/solids/VExtrudedSolid.h"

#include <string>
#include <vector>

class TGeoXtru;

namespace RootGM {

  class ExtrudedSolid : public BaseVGM::VExtrudedSolid
  {
    public:
      ExtrudedSolid(const std::string& name, 
                    std::vector<VGM::TwoVector> polygon,
                    std::vector< std::vector<double> > zsections);
      ExtrudedSolid(TGeoXtru* xtru);
      virtual ~ExtrudedSolid();

      // methods
      virtual std::string     Name() const;
      inline  int             NofVertices() const;
      inline  VGM::TwoVector  Vertex(int index) const;
      virtual int             NofZSections() const;
      virtual double          ZPosition(int iz) const;
      virtual VGM::TwoVector  Offset(int iz) const;
      virtual double          Scale(int iz) const;

    protected:
      ExtrudedSolid();
      ExtrudedSolid(const ExtrudedSolid& rhs);

      TGeoXtru* fXtru;
  };

}  

#endif //ROOT_GM_EXTRUDED_SOLID_H
