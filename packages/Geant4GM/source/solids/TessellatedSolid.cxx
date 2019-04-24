// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TessellatedSolid
// --------------------
// VGM implementation for Geant4 TessellatedSolid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/TessellatedSolid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "ClhepVGM/Units.h"

#include "VGM/common/Transform.h"

#include "G4QuadrangularFacet.hh"
#include "G4ReflectedSolid.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"

#include <iostream>
#include <math.h>
#include <set>

//_____________________________________________________________________________
Geant4GM::TessellatedSolid::TessellatedSolid(
  const std::string& name, std::vector<std::vector<VGM::ThreeVector> > facets)
  : VGM::ISolid(),
    VGM::ITessellatedSolid(),
    BaseVGM::VTessellatedSolid(),
    fName(name),
    fTessellatedSolid(0)
{
  /// Standard constructor to define TessellatedSolid from parameters
  /// \param facets the vector of facets defined as a vector of
  ///        three vectors representing the facet points in mm

  fTessellatedSolid = new G4TessellatedSolid();

  // Add triangular facets
  //
  for (G4int i = 0; i < G4int(facets.size()); i++) {

    std::vector<VGM::ThreeVector> facet = facets[i];

    // check number of vertices
    if (facet.size() != 3 && facet.size() != 4) {
      std::cerr << "+++ Error  +++" << std::endl;
      std::cerr << "    Number of vertices in a facet = " << facet.size()
                << " has to be == 3 or 4" << std::endl;
      exit(1);
    }

    if (facet.size() == 3) {
      VGM::ThreeVector vertex0 = facet[0];
      VGM::ThreeVector vertex1 = facet[1];
      VGM::ThreeVector vertex2 = facet[2];

      fTessellatedSolid->AddFacet(new G4TriangularFacet(
        G4ThreeVector(vertex0[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex0[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex0[VGM::kDz] / ClhepVGM::Units::Length()),
        G4ThreeVector(vertex1[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex1[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex1[VGM::kDz] / ClhepVGM::Units::Length()),
        G4ThreeVector(vertex2[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex2[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex2[VGM::kDz] / ClhepVGM::Units::Length()),
        ABSOLUTE));
    }
  }

  // Add quadrangular facets
  //
  for (G4int i = 0; i < G4int(facets.size()); i++) {

    std::vector<VGM::ThreeVector> facet = facets[i];

    if (facet.size() == 4) {
      VGM::ThreeVector vertex0 = facet[0];
      VGM::ThreeVector vertex1 = facet[1];
      VGM::ThreeVector vertex2 = facet[2];
      VGM::ThreeVector vertex3 = facet[3];

      fTessellatedSolid->AddFacet(new G4QuadrangularFacet(
        G4ThreeVector(vertex0[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex0[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex0[VGM::kDz] / ClhepVGM::Units::Length()),
        G4ThreeVector(vertex1[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex1[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex1[VGM::kDz] / ClhepVGM::Units::Length()),
        G4ThreeVector(vertex2[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex2[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex2[VGM::kDz] / ClhepVGM::Units::Length()),
        G4ThreeVector(vertex3[VGM::kDx] / ClhepVGM::Units::Length(),
          vertex3[VGM::kDy] / ClhepVGM::Units::Length(),
          vertex3[VGM::kDz] / ClhepVGM::Units::Length()),
        ABSOLUTE));
    }
  }

  fTessellatedSolid->SetSolidClosed(true);

  // G4cout << *fTessellatedSolid << G4endl;

  Geant4GM::SolidMap::Instance()->AddSolid(this, fTessellatedSolid);
}

//_____________________________________________________________________________
Geant4GM::TessellatedSolid::TessellatedSolid(
  G4TessellatedSolid* tessellated, G4ReflectedSolid* reflTessellated)
  : VGM::ISolid(),
    VGM::ITessellatedSolid(),
    BaseVGM::VTessellatedSolid(),
    fName(tessellated->GetName()),
    fIsReflected(false),
    fTessellatedSolid(tessellated)
{
  /// Standard constructor to define TessellatedSolid from Geant4 object

  if (reflTessellated) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTessellated);
  }
  else {
    Geant4GM::SolidMap::Instance()->AddSolid(this, tessellated);
  }
}

//_____________________________________________________________________________
Geant4GM::TessellatedSolid::TessellatedSolid()
  : VGM::ISolid(),
    VGM::ITessellatedSolid(),
    BaseVGM::VTessellatedSolid(),
    fName(),
    fIsReflected(false),
    fTessellatedSolid(0)
{
  /// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::TessellatedSolid::TessellatedSolid(const TessellatedSolid& rhs)
  : VGM::ISolid(rhs),
    VGM::ITessellatedSolid(rhs),
    BaseVGM::VTessellatedSolid(rhs),
    fName(),
    fIsReflected(false),
    fTessellatedSolid(0)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::TessellatedSolid::~TessellatedSolid()
{
  //
}

//_____________________________________________________________________________
void Geant4GM::TessellatedSolid::CheckFacetIndex(int ifacet) const
{
  if (ifacet < 0 || ifacet > NofFacets()) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong facet index: " << ifacet << std::endl;
    exit(1);
  }

  G4VFacet* facet = fTessellatedSolid->GetFacet(ifacet);
  if (!facet) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Facet with index: " << ifacet << " not found."
              << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
void Geant4GM::TessellatedSolid::CheckVertexIndex(int ifacet, int index) const
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
std::string Geant4GM::TessellatedSolid::Name() const
{
  return fTessellatedSolid->GetName();
}

//_____________________________________________________________________________
int Geant4GM::TessellatedSolid::NofFacets() const
{
  return fTessellatedSolid->GetNumberOfFacets();
}

//_____________________________________________________________________________
int Geant4GM::TessellatedSolid::NofVertices(int ifacet) const
{
  CheckFacetIndex(ifacet);

  G4VFacet* facet = fTessellatedSolid->GetFacet(ifacet);

  return facet->GetNumberOfVertices();
}

//_____________________________________________________________________________
VGM::ThreeVector Geant4GM::TessellatedSolid::Vertex(int ifacet, int index) const
{
  CheckVertexIndex(ifacet, index);

  G4VFacet* facet = fTessellatedSolid->GetFacet(ifacet);

  VGM::ThreeVector vertex;
  vertex.push_back(facet->GetVertex(index).x() * ClhepVGM::Units::Length());
  vertex.push_back(facet->GetVertex(index).y() * ClhepVGM::Units::Length());
  vertex.push_back(facet->GetVertex(index).z() * ClhepVGM::Units::Length());

  if (fIsReflected) vertex[VGM::kDz] = -vertex[VGM::kDz];

  return vertex;
}
