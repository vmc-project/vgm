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
// Class ExtrudedSolid
// --------------------
// VGM implementation for Geant4 ExtrudedSolid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/ExtrudedSolid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "ClhepVGM/Units.h"

#include "G4ExtrudedSolid.hh"
#include "G4ReflectedSolid.hh"
#include "G4UnionSolid.hh"

#include <iostream>
#include <set>
#include <math.h>


//_____________________________________________________________________________
Geant4GM::ExtrudedSolid::ExtrudedSolid(const std::string& name, 
                    std::vector<VGM::TwoVector> polygon,
                    std::vector< std::vector<double> > zsections)
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(),
    fName(name),
    fExtrudedSolid(0),
    fZSections(zsections),
    fConstituents()
{
/// Standard constructor to define ExtrudedSolid from parameters
/// \param polygon the outline polygon
/// \param zsections the vector of z-sections defined via 4 double numbers:
///        z position (in mm), the polygon offset in x and y, the scale

  if ( zsections.size() < 2 ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Number of z-sections = " << zsections.size() 
              << " has to be >= 2" << std::endl;
    exit(1);
  }             

  // Fill polygon 
  std::vector<G4TwoVector> g4Polygon;
  for ( G4int i=0; i<G4int(polygon.size()); ++i ) {
    g4Polygon.push_back(
      G4TwoVector(
        polygon[i].first  / ClhepVGM::Units::Length(),
        polygon[i].second / ClhepVGM::Units::Length()));
  }

  // Check if solid has to be broken in more constituents
  // ( If some z-sections are at the same z-position )
  //
  std::set<unsigned int> toBreak;
  for ( unsigned int i=1; i<zsections.size(); ++i ) 
    if ( fabs (zsections[i][0] - zsections[i-1][0]) < 1e-09 ) toBreak.insert(i-1); 
  toBreak.insert(zsections.size()-1);
  
  // Create solid constituents
  //
  std::vector<G4ExtrudedSolid::ZSection> g4Zsections;
  for ( unsigned int iz=0; iz<zsections.size(); ++iz) {
    // Fill z-sections for this constituent
    g4Zsections.push_back(
      G4ExtrudedSolid::ZSection(
        zsections[iz][0]             / ClhepVGM::Units::Length(),
        G4TwoVector(zsections[iz][1] / ClhepVGM::Units::Length(),
                    zsections[iz][2] / ClhepVGM::Units::Length()),
        zsections[iz][3]));
    
    if ( toBreak.find(iz) != toBreak.end() ) {   
      // Create G4ExtrudedSolid   
      //G4cout << "Go to create constituent with " << g4Zsections.size()
      //       << " z-sections" << G4endl;
                            
      G4ExtrudedSolid* xtru 
        = new G4ExtrudedSolid(fName, g4Polygon, g4Zsections);
      fConstituents.push_back(xtru); 
      g4Zsections.clear();
    }
  }

  // Compose boolean solid if solid had to be broken
  //
  G4VSolid* xtruA = *fConstituents.begin();

  std::vector<G4ExtrudedSolid*>::const_iterator it;
  for ( it = fConstituents.begin()+1; it != fConstituents.end(); ++it ) { 
    G4ExtrudedSolid* xtruB = *it;
    G4VSolid* unionAB
      = new G4UnionSolid(fName, xtruA, xtruB, 0, G4ThreeVector());
    xtruA = unionAB;
  }
  fExtrudedSolid = xtruA;
  
  // G4cout << *fExtrudedSolid << G4endl;

  Geant4GM::SolidMap::Instance()->AddSolid(this, fExtrudedSolid);

}

//_____________________________________________________________________________
Geant4GM::ExtrudedSolid::ExtrudedSolid(G4ExtrudedSolid* xtru, 
                                       G4ReflectedSolid* reflXtru)
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(),
    fName(xtru->GetName()),
    fExtrudedSolid(xtru),
    fZSections(),
    fConstituents()
{    
/// Standard constructor to define ExtrudedSolid from Geant4 object

  G4double sign = 1.;
  if ( reflXtru ) sign = -1;

  // Fill z planes parameters
  for (G4int iz=0; iz<xtru->GetNofZSections(); ++iz ) {
    ZSectionType zsection(4);
    zsection[0] = sign * xtru->GetZSection(iz).fZ   / ClhepVGM::Units::Length(); 
    zsection[1] = xtru->GetZSection(iz).fOffset.x() / ClhepVGM::Units::Length(); 
    zsection[2] = xtru->GetZSection(iz).fOffset.y() / ClhepVGM::Units::Length(); 
    zsection[3] = xtru->GetZSection(iz).fScale;
    if ( ! reflXtru ) 
      fZSections.push_back(zsection);
    else   
      fZSections.insert(fZSections.begin(), zsection);
  }    
  
  // Fill constituent
  fConstituents.push_back(xtru);

  if ( reflXtru )
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflXtru);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, xtru);
}

//_____________________________________________________________________________
Geant4GM::ExtrudedSolid::ExtrudedSolid() 
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(), 
    fName(),
    fExtrudedSolid(0),
    fZSections(),
    fConstituents()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::ExtrudedSolid::ExtrudedSolid(const ExtrudedSolid& rhs) 
  : VGM::ISolid(rhs),
    VGM::IExtrudedSolid(rhs),
    BaseVGM::VExtrudedSolid(rhs), 
    fName(),
    fExtrudedSolid(0),
    fZSections(),
    fConstituents()
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::ExtrudedSolid::~ExtrudedSolid() {
//
}    

/*
//_____________________________________________________________________________
void Geant4GM::ExtrudedSolid::CreateFinalSolid()
{
/// Compose created solids in a union

  G4cout << "Geant4GM::ExtrudedSolid::CreateFinalSolid" << G4endl;

  G4VSolid* xtruA = *fConstituents.begin();
  G4double hzTotal = (*fConstituents.begin())->GetZHalfLength();

  // compose boolean solid if more then 1 constituent
  std::vector<G4ExtrudedSolid*>::const_iterator it;
  for ( it = fConstituents.begin()+1; it != fConstituents.end(); ++it ) { 
    G4ExtrudedSolid* xtruB = *it;
    G4double dz = hzTotal + xtruB->GetZHalfLength();
    G4VSolid* unionAB
      = new G4UnionSolid(fName, xtruA, xtruB, 0, G4ThreeVector(0., 0., dz));
    xtruA = unionAB;
    hzTotal += xtruB->GetZHalfLength();
  }
  
  fExtrudedSolid = xtruA;
  fZDisplacement = fZDisplacement - hzTotal; // CHECK !!!
  
  G4cout << *fExtrudedSolid << G4endl;

  // Reset VGM polygon data
  dynamic_cast<Geant4GM::Polygon*>(fPolygon)
    ->SetExtrudedSolid(*fConstituents.begin());

  Geant4GM::SolidMap::Instance()->AddSolid(this, fExtrudedSolid);
}   

//_____________________________________________________________________________
void  Geant4GM::ExtrudedSolid::AddZPlane(double zpos, 
                                         VGM::TwoVector offset, double scale)
{
  
  if ( fZSections.size() > 0) {
 
    // Set polygon 
    std::vector<G4TwoVector> polygon;
    if ( fConstituents.size() == 0 ) {
      // Fill it from VGM object if not yet defined
      for ( G4int i=0; i<fPolygon->NofVertices(); i++ ) {
        polygon.push_back(
          G4TwoVector(
            fPolygon->Vertex(i).first  / ClhepVGM::Units::Length(),
            fPolygon->Vertex(i).second / ClhepVGM::Units::Length()));
      }
    }
    else {
      // Get polygon from existing ExtrudedSolid solid
      polygon = (*fConstituents.begin())->GetPolygon();
    }  
    
    ZPlaneType zplane = fZSections[fZSections.size()-1]; 
    G4double hz = (zpos -zplane[0])/2.0 / ClhepVGM::Units::Length();
    if ( hz > 0. ) { 
      G4TwoVector off1 = G4TwoVector(
                           zplane[1]/ ClhepVGM::Units::Length(),
                           zplane[2]/ ClhepVGM::Units::Length());
      G4double scale1 = zplane[3];
      G4TwoVector off2 = G4TwoVector(
                           offset.first / ClhepVGM::Units::Length(),
                           offset.second/ ClhepVGM::Units::Length());
      G4double scale2 = scale;
    
      // Create xtru for 2 planes and save it in the map                         
      G4ExtrudedSolid* xtru 
        = new G4ExtrudedSolid(fName, polygon, hz, off1, scale1, off2, scale2);
      fConstituents.push_back(xtru); 
    }             
  }
  else  {
    // Keep starting position of the solid
    // fZDisplacement = zpos;
  }  
 
  // Keep data of this z plane
  ZPlaneType zplane(4);
  zplane[0] = zpos;
  zplane[1] = offset.first;
  zplane[2] = offset.second;
  zplane[3] = scale;
  fZSections.push_back(zplane);
  

  // If the last z plane create the final solid
  if ( G4int(fZSections.size()) == fNofZSections ) CreateFinalSolid();
}
*/

//_____________________________________________________________________________
std::string Geant4GM::ExtrudedSolid::Name() const
{
  return fExtrudedSolid->GetName();
}  
  
//_____________________________________________________________________________
int Geant4GM::ExtrudedSolid::NofVertices() const
{
  return fConstituents[0]->GetNofVertices();
}  

//_____________________________________________________________________________
VGM::TwoVector  Geant4GM::ExtrudedSolid::Vertex(int index) const
{
  if ( index < 0 || index > NofVertices() ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong vertex index: " << index << std::endl;
    exit(1);
  }  
 
  return VGM::TwoVector(
           fConstituents[0]->GetVertex(index).x() * ClhepVGM::Units::Length(),
           fConstituents[0]->GetVertex(index).y() * ClhepVGM::Units::Length());
}           

//_____________________________________________________________________________
int Geant4GM::ExtrudedSolid::NofZSections() const
{
  return fZSections.size();
}  

//_____________________________________________________________________________
double Geant4GM::ExtrudedSolid::ZPosition(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }  
 
  ZSectionType zplane = fZSections[iz];
  return zplane[0] * ClhepVGM::Units::Length(); 
}  

//_____________________________________________________________________________
VGM::TwoVector Geant4GM::ExtrudedSolid::Offset(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }  

  ZSectionType zplane = fZSections[iz];
  return VGM::TwoVector(zplane[1] * ClhepVGM::Units::Length(),
                        zplane[2] * ClhepVGM::Units::Length()); 
}  

//_____________________________________________________________________________
double Geant4GM::ExtrudedSolid::Scale(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }  

  ZSectionType zplane = fZSections[iz];
  return zplane[3]; 
}  
