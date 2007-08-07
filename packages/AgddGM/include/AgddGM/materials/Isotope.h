// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_materials
//
/// \class AgddGM::Isotope
///
/// VGM implementation for AGDD_Isotope.
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_ISOTOPE_H
#define AGDD_GM_ISOTOPE_H


#include <VGM/materials/IIsotope.h>

namespace agdd {
    class AGDD_Isotope;
}

namespace AgddGM {

class Isotope : public virtual VGM::IIsotope
{
    agdd::AGDD_Isotope* fIsotope;
    
public:
    Isotope(agdd::AGDD_Isotope* iso);
    virtual ~Isotope();
    virtual std::string Name() const;
    virtual int     Z() const;
    virtual int     N() const;
    virtual double  A() const;
};
}
#endif // AGDD_GM_ISOTOPE_H
