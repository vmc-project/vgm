// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::ITessellatedSolid
/// 
/// The VGM interface to extruded solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TESSELLATED_SOLID_H
#define VGM_I_TESSELLATED_SOLID_H

#include <iostream>

#include "VGM/common/ThreeVector.h"
#include "VGM/solids/ISolid.h"

namespace VGM {

  class ITessellatedSolid : public virtual ISolid
  {
    public:
      virtual ~ITessellatedSolid() {}

      // methods

      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		           /// 
		           /// Return the number of facets
      virtual int         NofFacets() const = 0;
		           /// 
		           /// Return the number of vertices in the the ifacet-th facet
      virtual int         NofVertices(int ifacet) const = 0;
		           /// 
		           /// Return the index-th vertex in the ifacet-th facet
      virtual ThreeVector Vertex(int ifacet, int index) const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::ITessellatedSolid& xtru);

#endif //VGM_I_EXTRUDED_SOLID_H
