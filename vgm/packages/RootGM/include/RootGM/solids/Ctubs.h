// $Id$
/// \ingroup RootGM_solids
//
/// \class RootGM:: Ctubs
///
/// VGM implementation for Root cut tubs solid.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_CTUBS_H
#define ROOT_GM_CTUBS_H

#include <string>

#include "TGeoTube.h"

#include "BaseVGM/solids/VCtubs.h"

namespace RootGM {

  class Ctubs : public BaseVGM::VCtubs
  {
    public:
      Ctubs(const std::string& name, 
           double rin, double rout, double hz, double sphi, double dphi,
	   double nxlow, double nylow, double nzlow,
	   double nxhigh, double nyhigh, double nzhigh);
      Ctubs(TGeoCtub* ctubs);
      virtual ~Ctubs();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;
      virtual double NxLow() const;
      virtual double NyLow() const;
      virtual double NzLow() const;
      virtual double NxHigh() const;
      virtual double NyHigh() const;
      virtual double NzHigh() const;

    protected:
      Ctubs();
      Ctubs(const Ctubs& rhs);

    private:
      TGeoCtub* fCtubs;
  };

}

#endif //ROOT_GM_CTUBS_H
