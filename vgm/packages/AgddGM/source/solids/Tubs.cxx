// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include "AgddGM/solids/Tubs.h"

#include "AGDD/AGDD_Model.hh"

#include "CLHEP/Units/SystemOfUnits.h"


AgddGM::Tubs::Tubs(agdd::AGDD_Tube* tub)
    :fTub(tub)
{
}


std::string AgddGM::Tubs::Name() const
{
    return fTub->getName();
}

// FIXME: units????

double AgddGM::Tubs::InnerRadius() const
{
    return fTub->InnerRadius() / CLHEP::mm;
}
double AgddGM::Tubs::OuterRadius() const
{
    return fTub->OuterRadius() / CLHEP::mm;
}
double AgddGM::Tubs::ZHalfLength() const
{
    return fTub->TotalLength()/2.0 / CLHEP::mm;
}
double AgddGM::Tubs::StartPhi() const
{
    return fTub->StartingAngle() / CLHEP::degree;
}
double AgddGM::Tubs::DeltaPhi() const
{
    return fTub->Angle() / CLHEP::degree;
}
