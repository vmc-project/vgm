// $Id$
//
// Class Trap
// ---------------
// VGM implementation for Root trap solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TRAP_H
#define ROOT_GM_TRAP_H

#include <string>

#include "TGeoArb8.h"

#include "BaseVGM/solids/VTrap.h"

namespace RootGM {

  class Trap : public BaseVGM::VTrap
  {
    public:
      Trap(const std::string& name, 
           double hz, double theta, double phi,
           double dy1, double dx1, double dx2, double alpha1, 
           double dy2, double dx3, double dx4, double alpha2);
      Trap(TGeoTrap* trap);
      virtual ~Trap();

      // methods
      virtual std::string Name() const;
      virtual double ZHalfLength() const;
      virtual double Theta() const;
      virtual double Phi() const;
      virtual double YHalfLengthMinusZ() const;
      virtual double XHalfLengthMinusZMinusY() const;
      virtual double XHalfLengthMinusZPlusY() const;
      virtual double AlphaMinusZ() const;
      virtual double YHalfLengthPlusZ() const;
      virtual double XHalfLengthPlusZMinusY() const;
      virtual double XHalfLengthPlusZPlusY() const;
      virtual double AlphaPlusZ() const;

    protected:
      Trap();
      Trap(const Trap& rhs);

    private:
      TGeoTrap* fTrap;
  };

}

#endif //ROOT_GM_TRAP_H
