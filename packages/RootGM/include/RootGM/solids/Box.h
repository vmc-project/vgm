// $Id$
//
// Class Box
// ---------------
// VGM implementation for Root box solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_BOX_H
#define ROOT_GM_BOX_H

#include <string>

#include "TGeoBBox.h"

#include "BaseVGM/solids/VBox.h"

namespace RootGM {

  class Box : public BaseVGM::VBox
  {
    public:
      Box(const std::string& name, double hx, double hy, double hz);
      Box(TGeoBBox* box);
      virtual ~Box();

      // methods
      virtual std::string Name() const;
      virtual double XHalfLength() const;
      virtual double YHalfLength() const;
      virtual double ZHalfLength() const;

    protected:
      Box();
      Box(const Box& rhs);
    
    private:
      TGeoBBox*  fBox;
  };

}

#endif //ROOT_GM_BOX_H
