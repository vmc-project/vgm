// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_materials
//
/// \class RootGM:: Medium
///
/// VGM implementation for Root medium.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MEDIUM_H
#define ROOT_GM_MEDIUM_H

#include "BaseVGM/materials/VMedium.h"

#include <string>

class TGeoMedium;

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
