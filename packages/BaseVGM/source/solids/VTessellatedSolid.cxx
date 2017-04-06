// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VTessellatedSolid
// ---------------------
// The ABC for TessellatedSolid solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VTessellatedSolid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITessellatedSolid& xtru)
{
  const VGM::ISolid& xtruSolid = xtru;
  out << xtruSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VTessellatedSolid::VTessellatedSolid()
  : VGM::ITessellatedSolid() 
{
/// Default constructor  
}


//_____________________________________________________________________________
BaseVGM::VTessellatedSolid::~VTessellatedSolid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTessellatedSolid::Put(std::ostream& out) const
{
  out << std::endl;
  out << NofFacets() << " facets:" << std::endl;
  for (int i=0; i< NofFacets(); i++ ) {
    out << "Facet #" << i << ": " <<  std::endl;

    out << "   " << NofVertices(i) << " vertices:" << std::endl;  
    for (int j=0; j< NofVertices(i); j++ ) {
      out << "     (" 
          << Vertex(i, j)[VGM::kDx]  << ", " 
          << Vertex(i, j)[VGM::kDy]  << ", " 
          << Vertex(i, j)[VGM::kDz]  << ")";  
      out << " mm" << std::endl;               
    }      
  }
  return out; 
}

