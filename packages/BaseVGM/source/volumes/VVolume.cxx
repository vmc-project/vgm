// $Id$
//
// Class VVolume
// ---------------
// The abstract base class for volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/ISolid.h"
#include "VGM/volumes/IPlacement.h"

#include "BaseVGM/volumes/VVolume.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IVolume& volume)
{
  out << "Volume: " << "\"" << volume.Name() << "\""
      << " material " << "\"" << volume.MaterialName() << "\""
      << " solid " << "\""  
      << VGM::SolidTypeName(volume.Solid()->Type()) << "\"  "
      << volume.NofDaughters() << " daughters: ";
      
  for (int i=0; i<volume.NofDaughters(); i++) {
      out << "\"" << volume.Daughter(i)->Name()  << "\"  ";
  }       
  
  return out;    
}

//_____________________________________________________________________________
BaseVGM::VVolume::VVolume(VGM::ISolid* solid)
  : VGM::IVolume(),
    fSolid(solid),
    fDaughters() 
{
/// Standard constructor
}

//_____________________________________________________________________________
BaseVGM::VVolume::VVolume() 
  : VGM::IVolume() 
{
/// Protected default constructor
} 

//_____________________________________________________________________________
BaseVGM::VVolume::VVolume(const VVolume& rhs) 
  : VGM::IVolume(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VVolume::~VVolume() {
//

  // Delete daughters
  for (unsigned int i=0; i<fDaughters.size(); i++) {
    delete fDaughters[i];
  }  
}

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VVolume::Solid() const  
{ 
  return fSolid; 
}

//_____________________________________________________________________________
int BaseVGM::VVolume::NofDaughters() const
{
  return fDaughters.size();
}  

//_____________________________________________________________________________
VGM::IPlacement* 
BaseVGM::VVolume::Daughter(int i) const
{
  return fDaughters[i];
}  

//_____________________________________________________________________________
void  BaseVGM::VVolume::AddDaughter(VGM::IPlacement* daughter)
{
  fDaughters.push_back(daughter);
}  
  
