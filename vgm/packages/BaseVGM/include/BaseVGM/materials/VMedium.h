// $Id$
/// \ingroup BaseVGM_materials
//
/// \class BaseVGM::VMedium
///
/// The ABC for tracking medium.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_MEDIUM_H
#define BASE_VGM_V_MEDIUM_H

#include <string>
#include <iostream>

#include "VGM/materials/IMedium.h"
#include "VGM/materials/IMaterial.h"

namespace BaseVGM {

  class VMedium : public virtual VGM::IMedium
  {
    public:
      VMedium(VGM::IMaterial* material);
      virtual ~VMedium();
    
      // methods
      virtual VGM::IMaterial* Material() const ;
      virtual int  NofParameters() const;

    protected:   
      VMedium();
      VMedium(const VMedium& rhs);
    
      // data members
      static const int fgkParamSize;  
          
      VGM::IMaterial* fMaterial;
  };
  
}  

#endif //BASE_VGM_V_MEDIUM_H
