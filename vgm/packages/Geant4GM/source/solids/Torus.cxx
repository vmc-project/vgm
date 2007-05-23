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
// Class Torus
// ---------------
// VGM implementation for Geant4 torus solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Torus.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Torus::Torus(const std::string& name, 
                       double rin, double rout, double rax, 
		       double sphi, double dphi)
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus(),
    fTorus( new G4Torus(name, 
                        rin  / ClhepVGM::Units::Length(), 
			rout / ClhepVGM::Units::Length(), 
			rax  / ClhepVGM::Units::Length(), 
			sphi / ClhepVGM::Units::Angle(), 
			dphi / ClhepVGM::Units::Angle()) )
{
/// Standard constructor to define torus from parameters
/// \param rin inside radius of the torus in mm
/// \param rout outside radius of the torus in mm
/// \param rax axial (swept) radius of the torus in mm
/// \param sphi starting angle of the segment in deg
///	   (with 0 being the +x axis)
/// \param dphi opening angle of the segment in deg

  Geant4GM::SolidMap::Instance()->AddSolid(this, fTorus); 
}


//_____________________________________________________________________________
Geant4GM::Torus::Torus(G4Torus* torus, 
                       G4ReflectedSolid* reflTorus)
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus(),
    fTorus(torus)
{    
/// Standard constructor to define torus from G4 object

  if (reflTorus)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTorus);
  else  
    Geant4GM::SolidMap::Instance()->AddSolid(this, torus);
}

//_____________________________________________________________________________
Geant4GM::Torus::Torus() 
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Torus::Torus(const Torus& rhs) 
  : VGM::ISolid(rhs),
    VGM::ITorus(rhs),
    BaseVGM::VTorus(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Torus::~Torus() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Torus::Name() const
{
  return fTorus->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Torus::InnerRadius() const
{
  return fTorus->GetRmin() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::OuterRadius() const
{
  return fTorus->GetRmax() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::AxialRadius() const
{
  return fTorus->GetRtor() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::StartPhi() const
{
  return fTorus->GetSPhi() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::DeltaPhi() const
{
  return fTorus->GetDPhi() * ClhepVGM::Units::Angle();
}  
