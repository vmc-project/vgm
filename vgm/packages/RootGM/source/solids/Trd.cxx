// $Id$
//
// Class Trd
// ---------------
// VGM implementation for Root trd solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Trd.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Trd::Trd(const std::string& name, 
                 double hx1, double hx2, double hy1, double hy2, double hz)
  : BaseVGM::VTrd(),
    fTrd(new TGeoTrd2(name.data(), 
                      hx1 / RootGM::Units::Length(), 
		      hx2 / RootGM::Units::Length(), 
		      hy1 / RootGM::Units::Length(), 
		      hy2 / RootGM::Units::Length(), 
		      hz  / RootGM::Units::Length())),
    fIsOwner(false)
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fTrd); 
}


//_____________________________________________________________________________
RootGM::Trd::Trd(TGeoTrd2* trd)
  : BaseVGM::VTrd(),
    fTrd(trd),
    fIsOwner(false)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fTrd); 
}

//_____________________________________________________________________________
RootGM::Trd::Trd(TGeoTrd1* trd)
  : BaseVGM::VTrd(),
    fTrd(new TGeoTrd2(trd->GetName(), 
                      trd->GetDx1(), trd->GetDx2(),
		      trd->GetDy(), trd->GetDy(), 
		      trd->GetDz())),
    fIsOwner(true)
		      
{    
  RootGM::SolidMap::Instance()->AddSolid(this, trd); 
}

//_____________________________________________________________________________
RootGM::Trd::~Trd() {
//
  if (fIsOwner) delete fTrd;
}    

//_____________________________________________________________________________
std::string RootGM::Trd::Name() const
{
  return fTrd->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Trd::XHalfLengthMinusZ() const
{
  return fTrd->GetDx1() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Trd::XHalfLengthPlusZ() const
{
  return fTrd->GetDx2() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Trd::YHalfLengthMinusZ() const
{
  return fTrd->GetDy1() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Trd::YHalfLengthPlusZ() const
{
  return fTrd->GetDy2() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Trd::ZHalfLength() const
{
  return fTrd->GetDz() * RootGM::Units::Length();
}  


