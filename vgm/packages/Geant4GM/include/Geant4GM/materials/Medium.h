// $Id$
/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::Medium
///
/// The VGM implementation of interface to tracking medium.
/// As there is no equivalent object in Geant4, the tracking medium
/// parameters are store in data members of this class.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MEDIUM_H
#define GEANT4_GM_MEDIUM_H

#include <string>

#include "BaseVGM/materials/VMedium.h"

namespace Geant4GM {

  class Medium : public BaseVGM::VMedium
  {
    public:
      Medium(const std::string& name, 
             int id,
             VGM::IMaterial* material,
             int nofParameters, double* parameters);
      virtual ~Medium();
    
      // methods
      virtual std::string Name() const;

      virtual int     Id() const;
      virtual double  Parameter(int i) const;

    protected:  
      Medium();
      Medium(const Medium& rhs); 
    
    private:
      void CheckIndex(int iel) const;

      // data members
      static  const int fgkParamSize;  
          
      G4String     fName;
      G4Material * fMaterial;
      G4int        fId;
      G4double*    fParameters;
  };

}

#endif //GEANT4_GM_MEDIUM_H
