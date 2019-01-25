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
/// \class RootGM::Para
///
/// VGM implementation for Root para solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PARA_H
#define ROOT_GM_PARA_H

#include "BaseVGM/solids/VPara.h"

#include <string>

class TGeoPara;

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
      Para();
      Para(const Para& rhs);

    private:
      TGeoPara* fPara;
  };

}

#endif //ROOT_GM_PARA_H
