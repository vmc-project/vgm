// $Id$
/// \ingroup RootGM_solids
//
/// \class RootGM:: Trd
///
/// VGM implementation for Root trd solid.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TRD_H
#define ROOT_GM_TRD_H

#include <string>

#include "TGeoTrd1.h"
#include "TGeoTrd2.h"

#include "BaseVGM/solids/VTrd.h"

namespace RootGM {

  class Trd : public BaseVGM::VTrd
  {
    public:
      Trd(const std::string& name, 
          double hx1, double hx2, double hy1, double hy2, double hz);
      Trd(TGeoTrd2* trd);
      Trd(TGeoTrd1* trd);
      virtual ~Trd();

      // methods
      virtual std::string Name() const;
      virtual double XHalfLengthMinusZ() const;
      virtual double XHalfLengthPlusZ() const;
      virtual double YHalfLengthMinusZ() const;
      virtual double YHalfLengthPlusZ() const;
      virtual double ZHalfLength() const;

    protected:
      Trd();
      Trd(const Trd& rhs);

    private:
      TGeoTrd2* fTrd;
      bool      fIsOwner;
  };

}

#endif //ROOT_GM_TRD_H
