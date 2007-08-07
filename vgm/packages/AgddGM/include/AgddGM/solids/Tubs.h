// $Id: $

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
/// \class AgddGM::Tubs
///
/// VGM implementation of VTubs for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_TUBS_H
#define AGDD_GM_TUBS_H

#include <BaseVGM/solids/VTubs.h>

namespace agdd { class AGDD_Tube; }

namespace AgddGM {

class Tubs : public BaseVGM::VTubs
{
public:
    Tubs(agdd::AGDD_Tube* tub);

    virtual ~Tubs() {}

    std::string Name() const;
    double InnerRadius() const;
    double OuterRadius() const;
    double ZHalfLength() const;
    double StartPhi() const;
    double DeltaPhi() const;
private:
    agdd::AGDD_Tube* fTub;
};

}


#endif  // AGDD_GM_TUBS_H
