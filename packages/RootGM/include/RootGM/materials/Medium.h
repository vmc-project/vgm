// $Id$
/// \ingroup RootGM_materials
//
/// \class RootGM:: Medium
///
/// VGM implementation for Root medium.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MEDIUM_H
#define ROOT_GM_MEDIUM_H

#include <string>

#include "TGeoMedium.h"

#include "BaseVGM/materials/VMedium.h"

namespace RootGM {

  class Medium : public BaseVGM::VMedium
  {
    public:
      Medium(const std::string& name, int id,
             VGM::IMaterial* material,
             int nofParameters, double* parameters);
      Medium(TGeoMedium* medium);		
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
          
      TGeoMedium*  fMedium;  
  };

}

#endif //ROOT_GM_MEDIUM_H
