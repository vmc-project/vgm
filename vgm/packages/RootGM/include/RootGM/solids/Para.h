// $Id$
//
// Class Para
// ---------------
// VGM implementation for Root para solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PARA_H
#define ROOT_GM_PARA_H

#include <string>

#include "TGeoPara.h"

#include "BaseVGM/solids/VPara.h"

namespace RootGM {

  class Para : public BaseVGM::VPara
  {
    public:
      Para(const std::string& name, 
           double dx, double dy, double dz,
	   double alpha, double theta, double phi);
      Para(TGeoPara* para);
      virtual ~Para();

      // methods
      virtual std::string Name() const;

      virtual double XHalfLength() const;
      virtual double YHalfLength() const;
      virtual double ZHalfLength() const;
      virtual double Alpha() const;
      virtual double Theta() const;
      virtual double Phi() const;

    protected:
      Para() : BaseVGM::VPara() {}
      Para(const Para& rhs) : BaseVGM::VPara(rhs) {}

    private:
      TGeoPara* fPara;
  };

}

#endif //ROOT_GM_PARA_H
