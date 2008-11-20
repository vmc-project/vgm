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
/// \class AgddGM::Torus
///
/// VGM implementation of VTorus for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_TORUS_H
#define AGDD_GM_TORUS_H

#include "BaseVGM/solids/VTorus.h"

#include <string>

namespace agdd { 
  class AGDD_Torus; 
}

namespace AgddGM {

class Torus : public BaseVGM::VTorus
{
public:
    Torus(agdd::AGDD_Torus* torus);
    virtual ~Torus() {}

    std::string Name() const;
    double InnerRadius() const;
    double OuterRadius() const;
    double AxialRadius() const;
    double StartPhi() const;
    double DeltaPhi() const;


private:
    agdd::AGDD_Torus* fTorus;
};

}

#endif  // AGDD_GM_TORUS_H
