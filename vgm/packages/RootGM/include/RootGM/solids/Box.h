// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM:: Box
///
/// VGM implementation for Root box solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_BOX_H
#define ROOT_GM_BOX_H

#include "BaseVGM/solids/VBox.h"

#include <string>

class TGeoBBox;

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
