// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TessellatedSolid
// ----------------------
// VGM implementation for Root Tessellated solid.
//
// Author: Ivana Hrivnacova; IJCLab Orsay

#include "RootGM/solids/TessellatedSolid.h"
#include "RootGM/common/Units.h"
#include "RootGM/solids/SolidMap.h"

#include "VGM/common/Transform.h"

#include "TGeoTessellated.h"

#include <cstdlib>
#include <iostream>
#include <math.h>

using ROOT::Geom::Vertex_t;

//_____________________________________________________________________________
RootGM::TessellatedSolid::TessellatedSolid(const std::string& name,
    std::vector<std::vector<VGM::ThreeVector> > facets)
  : VGM::ISolid(), VGM::ITessellatedSolid(), BaseVGM::VTessellatedSolid(),
    fTessellated(0)
{
  /// Standard constructor to define TessellatedSolid from parameters
  /// \param facets the vector of facets defined as a vector of
  ///        three vectors representing the facet points in mm

  fTessellated = new TGeoTessellated();
  fTessellated->SetName(name.data());

  // Add triangular facets
  //
  for (Int_t i = 0; i < Int_t(facets.size()); i++) {

    std::vector<VGM::ThreeVector> facet = facets[i];

    // check number of vertices
    if (facet.size() != 3 && facet.size() != 4) {
      std::cerr << "+++ Error  +++" << std::endl;
      std::cerr << "    Number of vertices in a facet = " << facet.size()
                << " has to be == 3 or 4" << std::endl;
      exit(1);
    }

    if (facet.size() == 3 ) {
      // Triangular facet
      VGM::ThreeVector vertex0 = facet[0];
      VGM::ThreeVector vertex1 = facet[1];
      VGM::ThreeVector vertex2 = facet[2];

      fTessellated->AddFacet(
        Vertex_t(vertex0[VGM::kDx] / RootGM::Units::Length(),
          vertex0[VGM::kDy] / RootGM::Units::Length(),
          vertex0[VGM::kDz] / RootGM::Units::Length()),
        Vertex_t(vertex1[VGM::kDx] / RootGM::Units::Length(),
          vertex1[VGM::kDy] / RootGM::Units::Length(),
          vertex1[VGM::kDz] / RootGM::Units::Length()),
        Vertex_t(vertex2[VGM::kDx] / RootGM::Units::Length(),
          vertex2[VGM::kDy] / RootGM::Units::Length(),
          vertex2[VGM::kDz] / RootGM::Units::Length()));
    }
    else {
      // Quadrilateral facet
      VGM::ThreeVector vertex0 = facet[0];
      VGM::ThreeVector vertex1 = facet[1];
      VGM::ThreeVector vertex2 = facet[2];
      VGM::ThreeVector vertex3 = facet[3];

      fTessellated->AddFacet(
        Vertex_t(vertex0[VGM::kDx] / RootGM::Units::Length(),
          vertex0[VGM::kDy] / RootGM::Units::Length(),
          vertex0[VGM::kDz] / RootGM::Units::Length()),
        Vertex_t(vertex1[VGM::kDx] / RootGM::Units::Length(),
          vertex1[VGM::kDy] / RootGM::Units::Length(),
          vertex1[VGM::kDz] / RootGM::Units::Length()),
        Vertex_t(vertex2[VGM::kDx] / RootGM::Units::Length(),
          vertex2[VGM::kDy] / RootGM::Units::Length(),
          vertex2[VGM::kDz] / RootGM::Units::Length()),
        Vertex_t(vertex3[VGM::kDx] / RootGM::Units::Length(),
          vertex3[VGM::kDy] / RootGM::Units::Length(),
          vertex3[VGM::kDz] / RootGM::Units::Length()));
    }
  }
  fTessellated->CloseShape();

  RootGM::SolidMap::Instance()->AddSolid(this, fTessellated);
}

//_____________________________________________________________________________
RootGM::TessellatedSolid::TessellatedSolid(TGeoTessellated* tessellated)
  : VGM::ISolid(), VGM::ITessellatedSolid(), BaseVGM::VTessellatedSolid(),
    fTessellated(tessellated)
{
  /// Standard constructor to define TessellatedSolid from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fTessellated);
}

//_____________________________________________________________________________
RootGM::TessellatedSolid::TessellatedSolid()
  : VGM::ISolid(), VGM::ITessellatedSolid(), BaseVGM::VTessellatedSolid(), fTessellated(0)
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::TessellatedSolid::TessellatedSolid(const TessellatedSolid& rhs)
  : VGM::ISolid(rhs),
    VGM::ITessellatedSolid(rhs),
    BaseVGM::VTessellatedSolid(rhs),
    fTessellated(0)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::TessellatedSolid::~TessellatedSolid()
{
  //
}

//_____________________________________________________________________________
void RootGM::TessellatedSolid::CheckFacetIndex(int ifacet) const
{
  if (ifacet < 0 || ifacet > NofFacets()) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong facet index: " << ifacet << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
void RootGM::TessellatedSolid::CheckVertexIndex(int ifacet, int index) const
{
  CheckFacetIndex(ifacet);

  if (index < 0 || index > NofVertices(ifacet)) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong vertex index: " << index << " in " << ifacet
              << " th facet." << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
std::string RootGM::TessellatedSolid::Name() const { return fTessellated->GetName(); }

//_____________________________________________________________________________
int RootGM::TessellatedSolid::NofFacets() const { return fTessellated->GetNfacets(); }

//_____________________________________________________________________________
int RootGM::TessellatedSolid::NofVertices(int ifacet) const
{
  CheckFacetIndex(ifacet);

  const TGeoFacet& facet = fTessellated->GetFacet(ifacet);

  return facet.GetNvert();
}

//_____________________________________________________________________________
VGM::ThreeVector RootGM::TessellatedSolid::Vertex(int ifacet, int index) const
{
  CheckVertexIndex(ifacet, index);

#if ROOT_VERSION_CODE > ROOT_VERSION(6, 30, 4)
  const auto& rvertex =  fTessellated->GetVertex((fTessellated->GetFacet(ifacet))[index]);
#else
  const auto& rvertex =  fTessellated->GetFacet(ifacet).GetVertex(index);
#endif

  VGM::ThreeVector vertex;
  vertex.push_back(rvertex.fVec[0] * RootGM::Units::Length());
  vertex.push_back(rvertex.fVec[1] * RootGM::Units::Length());
  vertex.push_back(rvertex.fVec[2] * RootGM::Units::Length());

  return vertex;
}
