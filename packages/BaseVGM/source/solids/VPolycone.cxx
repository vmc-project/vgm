// $Id$
//
// Class VPolycone
// ---------------
// The ABC for polycone solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VPolycone.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IPolycone& polycone)
{
  const VGM::ISolid& polyconeSolid = polycone;
  out << polyconeSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VPolycone::VPolycone()
  : VGM::IPolycone() 
{
/// Default constructor  
}


//_____________________________________________________________________________
BaseVGM::VPolycone::~VPolycone() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VPolycone::Put(std::ostream& out) const
{
  out << "  sphi = " << StartPhi() << "deg"
      << "  dphi = " << DeltaPhi() << "deg"
      << "  nz = "   << NofZPlanes()
      << std::endl;
      
  double* zvalues    = ZValues();
  double* rinvalues  = InnerRadiusValues();
  double* routvalues = OuterRadiusValues();   
 
  for (int i=0; i<NofZPlanes(); i++) {
    out << "   "
        << i << "th plane: "        
        << " z = "    << zvalues[i]    << "mm"  
        << " rin = "  << rinvalues[i]  << "mm"  
        << " rout = " << routvalues[i] << "mm"; 

    if (i<NofZPlanes()-1) out << std::endl;
  }
      
  return out; 
}

