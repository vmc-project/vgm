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
// Class Hype
// -----------------
// VGM implementation for Geant4 hyperboloid solid.
// If reflected, the parameters are not changed.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Hype.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4Hype.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::Hype::Hype(const std::string& name, 
                     double r1, double r2, double stereo1, double stereo2,
                     double hz)
  : VGM::ISolid(),
    VGM::IHype(),
    BaseVGM::VHype(),
    fHype( new G4Hype(name, 
                      r1      / ClhepVGM::Units::Length(), 
                      r2      / ClhepVGM::Units::Length(), 
                      stereo1 / ClhepVGM::Units::Angle(), 
                      stereo2 / ClhepVGM::Units::Angle(), 
		      hz      / ClhepVGM::Units::Length()))
{
/// Standard constructor to define hyperboloid from parameters
/// Standard constructor to define hyperboloid from parameters
/// \param r1 radius of the inner hyperbolic surface in mm
/// \param r2 radius of the outer hyperbolic surface in mm
/// \param stereo1 stereo angle for the inner hyperbolic surface in deg
/// \param stereo2 stereo angle for the outer hyperbolic surface in deg
/// \param hz half-length along the z axis in mm

  Geant4GM::SolidMap::Instance()->AddSolid(this, fHype); 
}


//_____________________________________________________________________________
Geant4GM::Hype::Hype(G4Hype* hype, 
                     G4ReflectedSolid* reflHype)
  : VGM::ISolid(),
    VGM::IHype(),
    BaseVGM::VHype(),
    fHype(hype)
{    
/// Standard constructor to define hyperboloid from G4 object

  if (reflHype) {
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflHype); 
  }  
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, hype); 
      
}

//_____________________________________________________________________________
Geant4GM::Hype::Hype() 
  : VGM::ISolid(),
    VGM::IHype(),
    BaseVGM::VHype() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Hype::Hype(const Hype& rhs) 
  : VGM::ISolid(rhs),
    VGM::IHype(rhs),
    BaseVGM::VHype(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Hype::~Hype() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Hype::Name() const
{
  return fHype->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Hype::InnerRadius() const
{
  return fHype->GetInnerRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Hype::InnerStereoAngle() const
{
  return fHype->GetInnerStereo() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Hype::OuterRadius() const
{
  return fHype->GetOuterRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Hype::OuterStereoAngle() const
{
  return fHype->GetOuterStereo() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Hype::ZHalfLength() const
{
  return fHype->GetZHalfLength() * ClhepVGM::Units::Length();
}  
