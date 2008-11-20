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
// Class BooleanSolid
// ---------------------
// VGM implementation for Geant4 Boolean solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/transform.h"

#include "Geant4GM/solids/BooleanSolid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4BooleanSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::BooleanSolid::BooleanSolid(
                            const std::string& name, 
                            VGM::BooleanType boolType,
                            VGM::ISolid* solidA, VGM::ISolid* solidB, 
                            CLHEP::HepRotation* rotation, 
			    const CLHEP::Hep3Vector& translation)
  : VGM::ISolid(), 
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid(),
    fBooleanSolid(0),
    fToBeReflected(false)
{
/// Standard constructor to define Boolean solids via constituents
/// \param boolType type of Boolean operation (kIntersection, kSubtraction,
///        kUnion)
/// \param solidA, solidB constituent solids
/// \param rotation, translation  the CLHEP rotation and translation of
///        the solidB with respect to solidA

  // Get solids from the volumes map
  G4VSolid* g4SolidA = Geant4GM::SolidMap::Instance()->GetSolid(solidA);
  G4VSolid* g4SolidB = Geant4GM::SolidMap::Instance()->GetSolid(solidB);
  
  switch (boolType) {
    case VGM::kIntersection:
      fBooleanSolid 
        = new G4IntersectionSolid(name, g4SolidA, g4SolidB, rotation, translation); 
      break;					 

    case VGM::kSubtraction:
      fBooleanSolid 
        = new G4SubtractionSolid(name, g4SolidA, g4SolidB, rotation, translation);
      break;	
					 
    case VGM::kUnion:
      fBooleanSolid 
        = new G4UnionSolid(name, g4SolidA, g4SolidB, rotation, translation); 
      break;
      
    case VGM::kUnknownBoolean:
    default:
      std::cerr << "    Geant4GM::BooleanSolid::BooleanSolid:" << std::endl; 
      std::cerr << "    Unknown Boolean solid type (solid \"" 
                << name << "\")" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
  }    		

  Geant4GM::SolidMap::Instance()->AddSolid(this, fBooleanSolid); 
}

//_____________________________________________________________________________
Geant4GM::BooleanSolid::BooleanSolid(G4BooleanSolid* booleanSolid,
                                     G4ReflectedSolid* reflectedBoolean)
  : VGM::ISolid(), 
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid(),
    fBooleanSolid(booleanSolid), 
    fToBeReflected(false)
{
/// Standard constructor to define Boolean solid via G4 object 

  if (reflectedBoolean) {
    fToBeReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflectedBoolean);
  }   
  else 
    Geant4GM::SolidMap::Instance()->AddSolid(this, fBooleanSolid); 
}

//_____________________________________________________________________________
Geant4GM::BooleanSolid::BooleanSolid() 
  : VGM::ISolid(), 
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::BooleanSolid::BooleanSolid(const BooleanSolid& rhs) 
  : VGM::ISolid(rhs), 
    VGM::IBooleanSolid(rhs),
    BaseVGM::VBooleanSolid(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::BooleanSolid::~BooleanSolid() {
//
}

// 
// private methods
//

//_____________________________________________________________________________
const G4DisplacedSolid* 
Geant4GM::BooleanSolid::DisplacedSolid() const
{
// Returns the G4 displaced solid
// ---

 G4VSolid* g4SolidB = fBooleanSolid->GetConstituentSolid(1);
 return g4SolidB->GetDisplacedSolidPtr();
} 


// 
// public methods
//

//_____________________________________________________________________________
std::string 
Geant4GM::BooleanSolid::Name() const
{
// Returns the Boolean solid name
// ---

  return fBooleanSolid->GetName();
}  

//_____________________________________________________________________________
VGM::BooleanType 
Geant4GM::BooleanSolid::BoolType() const
{
// Returns the Boolean solid type name
// ---

  if (fBooleanSolid->GetEntityType() == "G4IntersectionSolid") 
    return VGM::kIntersection;

  if (fBooleanSolid->GetEntityType() == "G4SubtractionSolid") 
    return VGM::kSubtraction;

  if (fBooleanSolid->GetEntityType() == "G4UnionSolid") 
    return VGM::kUnion;
    
  return VGM::kUnknownBoolean;
}    

//_____________________________________________________________________________
VGM::ISolid* 
Geant4GM::BooleanSolid::ConstituentSolidA() const
{
// Returns the first constituent solid.
// ---

 G4VSolid* g4SolidA = GetConstituentSolid(0, fBooleanSolid);
 VGM::ISolid* solidA = Geant4GM::SolidMap::Instance()->GetSolid(g4SolidA);
 
 return solidA;
} 

//_____________________________________________________________________________
VGM::ISolid* 
Geant4GM::BooleanSolid::ConstituentSolidB() const
{
// Returns the first constituent solid.
// ---

 G4VSolid* g4SolidB = GetConstituentSolid(1, fBooleanSolid);
 
 VGM::ISolid* solidB = Geant4GM::SolidMap::Instance()->GetSolid(g4SolidB);
 
 return solidB;
} 

//_____________________________________________________________________________
VGM::Transform 
Geant4GM::BooleanSolid::Displacement() const
{
// Returns the first constituent solid.
// ---

 const G4DisplacedSolid* g4DisplacedSolid = DisplacedSolid();
 
 if (g4DisplacedSolid) {
   return ClhepVGM::Transform(g4DisplacedSolid->GetObjectRotation(),
                              g4DisplacedSolid->GetObjectTranslation());
 } 			      
 else
   return ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector());
}    

//_____________________________________________________________________________
G4VSolid* 
Geant4GM::BooleanSolid::GetConstituentSolid(
                              int index, 
                              G4BooleanSolid* booleanSolid)
{
// Returns the constituent solid specified by index,
// if the constituent solid is displaced solid, returns
// its moved constituent
// ---

  G4VSolid* consSolid = booleanSolid->GetConstituentSolid(index);

  G4DisplacedSolid* displacedSolid = consSolid->GetDisplacedSolidPtr();
  if (displacedSolid) consSolid = displacedSolid->GetConstituentMovedSolid();
             // If displaced solid, import only its constituent
  
  return consSolid;
}  			      

