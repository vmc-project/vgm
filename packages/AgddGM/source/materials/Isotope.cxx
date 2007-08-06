// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/materials/Isotope.h>
#include <AGDD/AGDD_Material_Model.hh>


AgddGM::Isotope::Isotope(agdd::AGDD_Isotope* iso)
    : fIsotope(iso)
{
    *iso;
}

AgddGM::Isotope::~Isotope() 
{
    delete fIsotope; fIsotope = 0;
}

std::string AgddGM::Isotope::Name() const
{
    return fIsotope->m_name;
}

int AgddGM::Isotope::Z() const
{
    return (int)fIsotope->m_z;
}

int AgddGM::Isotope::N() const
{
    return fIsotope->m_n;
}

double  AgddGM::Isotope::A() const
{
    return fIsotope->m_a;
}
