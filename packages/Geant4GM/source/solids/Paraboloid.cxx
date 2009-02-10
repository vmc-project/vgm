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
// Class Paraboloid
// -----------------
// VGM implementation for Geant4 paraboloid solid.
// If reflected, the parameters are changed as follows:
//    r1  -->  r2'
//    r2  -->  r1'
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Paraboloid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4Paraboloid.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::Paraboloid::Paraboloid(const std::string& name, 
                                 double r1, double r2, double hz)
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid(),
    fIsReflected(false),
    fParaboloid(0)
{
/// Standard constructor to define paraboloid from parameters
/// \param r1 radius at -hz in mm
/// \param r2 radius at +hz in mm
/// \param hz half-length along the z axis in mm

  if ( r2 > r1 ) {
    fParaboloid = new G4Paraboloid(name, 
		        hz / ClhepVGM::Units::Length(), 
                        r1 / ClhepVGM::Units::Length(), 
		        r2 / ClhepVGM::Units::Length());
    fIsReflected = false;
    Geant4GM::SolidMap::Instance()->AddSolid(this, fParaboloid); 
  }
  else {
    fParaboloid = new G4Paraboloid(name, 
		        hz / ClhepVGM::Units::Length(), 
                        r2 / ClhepVGM::Units::Length(), 
		        r1 / ClhepVGM::Units::Length());

    G4ReflectedSolid* reflParaboloid
                = new G4ReflectedSolid(name, fParaboloid, G4ReflectZ3D());
                            
                        
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflParaboloid); 
  }  
}


//_____________________________________________________________________________
Geant4GM::Paraboloid::Paraboloid(G4Paraboloid* paraboloid, 
                                 G4ReflectedSolid* reflParaboloid)
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid(),
    fIsReflected(false),
    fParaboloid(paraboloid)
{    
/// Standard constructor to define paraboloid from G4 object

  if (reflParaboloid) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflParaboloid); 
  }  
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, paraboloid); 
      
}

//_____________________________________________________________________________
Geant4GM::Paraboloid::Paraboloid() 
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Paraboloid::Paraboloid(const Paraboloid& rhs) 
  : VGM::ISolid(rhs),
    VGM::IParaboloid(rhs),
    BaseVGM::VParaboloid(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Paraboloid::~Paraboloid() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Paraboloid::Name() const
{
  return fParaboloid->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Paraboloid::RadiusMinusZ() const
{
  if ( ! fIsReflected )
    return fParaboloid->GetRadiusMinusZ() * ClhepVGM::Units::Length();
  else    
    return fParaboloid->GetRadiusPlusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Paraboloid::RadiusPlusZ() const
{
  if ( ! fIsReflected )
    return fParaboloid->GetRadiusPlusZ() * ClhepVGM::Units::Length();
  else    
    return fParaboloid->GetRadiusMinusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Paraboloid::ZHalfLength() const
{
  return fParaboloid->GetZHalfLength() * ClhepVGM::Units::Length();
}  
