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
// Class Trd
// ---------------
// VGM implementation for Geant4 trd solid.
// If reflected, the parameters are changed as follows:
//    hx1, hy1  -->  hx2', hy2'
//    hx2, hy2  -->  hx1', hy1'
//    hz           -->  hz' 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Trd.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Trd::Trd(const std::string& name, 
                   double hx1, double hx2, double hy1, double hy2, double hz)
  : VGM::ISolid(),
    VGM::ITrd(),
    BaseVGM::VTrd(),
    fIsReflected(false),
    fTrd( new G4Trd(name, 
                    hx1 / ClhepVGM::Units::Length(), 
		    hx2 / ClhepVGM::Units::Length(), 
		    hy1 / ClhepVGM::Units::Length(), 
		    hy2 / ClhepVGM::Units::Length(), 
		    hz  / ClhepVGM::Units::Length()) )
{
/// Standard constructor to define trd from parameters
/// \param hx1 half-length along x at the surface positioned 
///	       at -hz in mm
/// \param hx2 half-length along x at the surface positioned 
///	       at +hz in mm
/// \param hy1 half-length along y at the surface positioned 
///	       at -hz in mm
/// \param hy2 half-length along y at the surface positioned 
///	       at +hz in mm
/// \param hz half-length along the z axis in mm

  Geant4GM::SolidMap::Instance()->AddSolid(this, fTrd); 
}


//_____________________________________________________________________________
Geant4GM::Trd::Trd(G4Trd* trd, 
                   G4ReflectedSolid* reflTrd)
  : VGM::ISolid(),
    VGM::ITrd(),
    BaseVGM::VTrd(),
    fIsReflected(false),
    fTrd(trd)
{    
/// Standard constructor to define trd from G4 object

  if (reflTrd) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTrd);
  }   
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, trd); 
}

//_____________________________________________________________________________
Geant4GM::Trd::Trd() 
  : VGM::ISolid(),
    VGM::ITrd(),
    BaseVGM::VTrd() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Trd::Trd(const Trd& rhs) 
  : VGM::ISolid(rhs),
    VGM::ITrd(rhs),
    BaseVGM::VTrd(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Trd::~Trd() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Trd::Name() const
{
  return fTrd->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Trd::XHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrd->GetXHalfLength1() * ClhepVGM::Units::Length();
  else  
    return fTrd->GetXHalfLength2() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::XHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrd->GetXHalfLength2() * ClhepVGM::Units::Length();
  else  
    return fTrd->GetXHalfLength1() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::YHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrd->GetYHalfLength1() * ClhepVGM::Units::Length();
  else  
    return fTrd->GetYHalfLength2() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::YHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrd->GetYHalfLength2() * ClhepVGM::Units::Length();
  else  
    return fTrd->GetYHalfLength1() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::ZHalfLength() const
{
  return fTrd->GetZHalfLength() * ClhepVGM::Units::Length();
}  


