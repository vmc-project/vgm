// $Id$
/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::Isotope
///
/// VGM implementation for Geant4 Isotope.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ISOTOPE_H
#define GEANT4_GM_ISOTOPE_H

#include <string>

#include "G4Isotope.hh"

#include "VGM/materials/IIsotope.h"

namespace Geant4GM {

  class Isotope : public virtual VGM::IIsotope
  {
    public:
      Isotope(const std::string& name, int z, int n, double a); 
      Isotope(G4Isotope* Isotope);		
      virtual ~Isotope();
    
      // methods
      virtual std::string Name() const;

      virtual int     Z() const;     
      virtual int     N() const;     
      virtual double  A() const;     

    protected:  
      Isotope();
      Isotope(const Isotope& rhs);
    
    private:
      G4Isotope*  fIsotope;  
  };

}

#endif //GEANT4_GM_ISOTOPE_H
