// $Id$
//
// Class Box
// ---------------
// VGM implementation for Root box solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Box.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Box::Box(const std::string& name, 
                 double hx, double hy, double hz)
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox(),
    fBox(new TGeoBBox(name.data(), 
                      hx / RootGM::Units::Length(), 
		      hy / RootGM::Units::Length(), 
		      hz / RootGM::Units::Length()))
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fBox); 
}


//_____________________________________________________________________________
RootGM::Box::Box(TGeoBBox* box)
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox(),
    fBox(box)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fBox); 
}

//_____________________________________________________________________________
RootGM::Box::Box() 
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox() 
{
//
}

//_____________________________________________________________________________
RootGM::Box::Box(const Box& rhs) 
  : VGM::ISolid(rhs),
    VGM::IBox(rhs),
    BaseVGM::VBox(rhs) 
{
//
}

//_____________________________________________________________________________
RootGM::Box::~Box() {
//
}    

//
// public methods
//

//_____________________________________________________________________________
std::string RootGM::Box::Name() const
{
  return fBox->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Box::XHalfLength() const
{
  return fBox->GetDX()*RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Box::YHalfLength() const
{
  return fBox->GetDY()*RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Box::ZHalfLength() const
{
  return fBox->GetDZ()*RootGM::Units::Length();
}  


