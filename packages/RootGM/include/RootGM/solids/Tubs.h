// $Id$
//
// Class Tubs
// ---------------
// VGM implementation for Root tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TUBS_H
#define ROOT_GM_TUBS_H

#include <string>

#include "TGeoTube.h"

#include "BaseVGM/solids/VTubs.h"

namespace RootGM {

  class Tubs : public BaseVGM::VTubs
  {
    public:
      Tubs(const std::string& name, 
           double rin, double rout, double hz, double sphi, double dphi);
      Tubs(TGeoTube* tubs);
      virtual ~Tubs();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Tubs();
      Tubs(const Tubs& rhs);

    private:
      TGeoTube* fTubs;
  };

}

#endif //ROOT_GM_TUBS_H
