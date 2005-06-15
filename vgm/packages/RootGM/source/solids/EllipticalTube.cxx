// $Id$
//
// Class EllipticalTube
// ---------------
// VGM implementation for Root elliptical tube solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/EllipticalTube.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::EllipticalTube::EllipticalTube(const std::string& name, 
                                       double dx, double dy, double hz)
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube(),
    fEllipticalTube(new TGeoEltu(name.data(), 
                    dx / RootGM::Units::Length(), 
		    dy / RootGM::Units::Length(), 
		    hz / RootGM::Units::Length()))
{
/// Standard constructor to define elliptical tube from parameters
/// \param dx the semi-axis of the ellipse along x in mm
/// \param dx the semi-axis of the ellipse along y in mm
/// \param hz half-length along the z axis in mm

  RootGM::SolidMap::Instance()->AddSolid(this, fEllipticalTube); 
}


//_____________________________________________________________________________
RootGM::EllipticalTube::EllipticalTube(TGeoEltu* eltu)
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube(),
    fEllipticalTube(eltu)
{    
/// Standard constructor to define elliptical tube from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fEllipticalTube); 
}

//_____________________________________________________________________________
RootGM::EllipticalTube::EllipticalTube() 
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::EllipticalTube::EllipticalTube(const EllipticalTube& rhs) 
  : VGM::ISolid(rhs),
    VGM::IEllipticalTube(rhs),
    BaseVGM::VEllipticalTube(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::EllipticalTube::~EllipticalTube() {
//
}    

//_____________________________________________________________________________
std::string RootGM::EllipticalTube::Name() const
{
  return fEllipticalTube->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::EllipticalTube::Dx() const
{
  return fEllipticalTube->GetA() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::EllipticalTube::Dy() const
{
  return fEllipticalTube->GetB() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::EllipticalTube::ZHalfLength() const
{
  return fEllipticalTube->GetDz() * RootGM::Units::Length();
}  
