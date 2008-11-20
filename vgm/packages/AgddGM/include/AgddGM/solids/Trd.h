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
/// \class AgddGM::Trd
///
/// VGM implementation of VTrd for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_TRD_H
#define AGDD_GM_TRD_H

#include "BaseVGM/solids/VTrd.h"

#include <string>

namespace agdd { class AGDD_Trapezoid; }

namespace AgddGM {

class Trd : public BaseVGM::VTrd {
public:
    Trd(agdd::AGDD_Trapezoid* trap);
    virtual ~Trd() {}

    std::string Name() const;
    double XHalfLengthMinusZ() const;
    double XHalfLengthPlusZ() const;
    double YHalfLengthMinusZ() const;
    double YHalfLengthPlusZ() const;
    double ZHalfLength() const;
    
private:
    agdd::AGDD_Trapezoid* fTrd;

};

}


#endif  // AGDD_GM_TRD_H
