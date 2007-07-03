// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/Torus.h>

#include <AGDD/AGDD_Model.hh>

#include <CLHEP/Units/SystemOfUnits.h>


AgddGM::Torus::Torus(agdd::AGDD_Torus* torus)
    : fTorus(torus)
{
}


std::string AgddGM::Torus::Name() const
{
    return fTorus->getName();
}

double AgddGM::Torus::InnerRadius() const
{
    return fTorus->InnerRadius() / CLHEP::mm;
}

double AgddGM::Torus::OuterRadius() const
{
    return fTorus->OuterRadius() / CLHEP::mm;
}

double AgddGM::Torus::AxialRadius() const
{
    return fTorus->RingRadius() / CLHEP::mm;
}

double AgddGM::Torus::StartPhi() const
{
    return fTorus->ProfileStart() / CLHEP::degree;
}

double AgddGM::Torus::DeltaPhi() const
{
    return fTorus->DeltaProfile() / CLHEP::degree;
}


