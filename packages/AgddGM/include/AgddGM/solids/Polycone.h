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
/// \class AgddGM::Polycone
///
/// VGM implementation of VPolycone for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_POLYCONE_H
#define AGDD_GM_POLYCONE_H

#include <BaseVGM/solids/VPolycone.h>
#include <string>

namespace agdd { class AGDD_Pcon; }

namespace AgddGM {

class Polycone : public BaseVGM::VPolycone {

public:
    Polycone(agdd::AGDD_Pcon* pcon);
    virtual ~Polycone();

    std::string Name() const;
    double  StartPhi() const;
    double  DeltaPhi() const;
    int     NofZPlanes() const;
    double* ZValues() const;
    double* InnerRadiusValues() const;
    double* OuterRadiusValues() const;
    

private:
    agdd::AGDD_Pcon* fPcon;
    double *fZ, *fIr, *fOr;
};
}

#endif  // AGDD_GM_POLYCONE_H
