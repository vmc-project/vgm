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
/// \class RootGM::TessellatedSolid
///
/// VGM implementation for Root tessellated solid.
///
/// \author Ivana Hrivnacova; IJCLab Orsay

#ifndef ROOT_GM_TESSELLATED_SOLID_H
#define ROOT_GM_TESSELLATED_SOLID_H

#include "BaseVGM/solids/VTessellatedSolid.h"

#include <string>
#include <vector>

class TGeoTessellated;

namespace RootGM {

class TessellatedSolid : public BaseVGM::VTessellatedSolid
{
 public:
  TessellatedSolid(const std::string& name,
    std::vector<std::vector<VGM::ThreeVector> > facets);
  TessellatedSolid(TGeoTessellated* tessellated);
  virtual ~TessellatedSolid();

  // methods
  virtual std::string Name() const;
  virtual int NofFacets() const;
  virtual int NofVertices(int ifacet) const;
  virtual VGM::ThreeVector Vertex(int ifacet, int index) const;

 protected:
  TessellatedSolid();
  TessellatedSolid(const TessellatedSolid& rhs);

 private:
  // methods
  void CheckFacetIndex(int ifacet) const;
  void CheckVertexIndex(int ifacet, int index) const;

  // data members
  TGeoTessellated* fTessellated;
};

} // namespace RootGM

#endif // ROOT_GM_TESSELLATED_SOLID_H
