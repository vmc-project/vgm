// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_solids
//
/// \class AgddGM::Cons
///
/// VGM implementation of VCons for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_CONS_H
#define AGDD_GM_CONS_H

#include "BaseVGM/solids/VCons.h"

namespace agdd { 
  class AGDD_Cone; 
}

namespace AgddGM {

class Cons : public BaseVGM::VCons {
public:
    Cons(agdd::AGDD_Cone* cone);
    virtual ~Cons() {}

    std::string Name() const;
    double InnerRadiusMinusZ() const ;
    double OuterRadiusMinusZ() const;
    double InnerRadiusPlusZ() const;
    double OuterRadiusPlusZ() const;
    double ZHalfLength() const;
    double StartPhi() const;
    double DeltaPhi() const;
private:
    agdd::AGDD_Cone* fCone;
};

}

#endif  // AGDD_GM_CONS_H
