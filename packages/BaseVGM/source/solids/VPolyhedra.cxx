// $Id$
//
// Class VPolyhedra
// ---------------
// The ABC for polyhedra solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <math.h>

#include "BaseVGM/solids/VPolyhedra.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IPolyhedra& polyhedra)
{
  const VGM::ISolid& polyhedraSolid = polyhedra;
  out << polyhedraSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VPolyhedra::VPolyhedra()
  : VGM::IPolyhedra() 
{
/// Default constructor  
}


//_____________________________________________________________________________
BaseVGM::VPolyhedra::~VPolyhedra() {
//
}

//_____________________________________________________________________________
double BaseVGM::VPolyhedra::ConvertRadiusFactor() const
{
// 
  double phiTotal = DeltaPhi();
  if ( (phiTotal <=0) || (phiTotal >= 2*M_PI*(1-1e-16)) )
    phiTotal = 2*M_PI;
  
  return cos(0.5*phiTotal/NofSides());
}  

//_____________________________________________________________________________
std::ostream& BaseVGM::VPolyhedra::Put(std::ostream& out) const
{
  out << "  sphi = "   << StartPhi() << "deg" 
      << "  dphi = "   << DeltaPhi() << "deg"
      << "  nsides = " << NofSides()
      << "  nz = "     << NofZPlanes()
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

