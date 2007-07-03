// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/Cons.h>
#include <AGDD/AGDD_Model.hh>
#include <CLHEP/Units/SystemOfUnits.h>

AgddGM::Cons::Cons(agdd::AGDD_Cone* cone)
    : fCone(cone)
{
}


std::string AgddGM::Cons::Name() const
{
    return fCone->getName();
}
    
double AgddGM::Cons::InnerRadiusMinusZ() const
{
    return fCone->InnerBottomRadius() / CLHEP::mm;
}

double AgddGM::Cons::OuterRadiusMinusZ() const
{
    return fCone->OuterBottomRadius() / CLHEP::mm;
}

double AgddGM::Cons::InnerRadiusPlusZ() const
{
    return fCone->InnerTopRadius() / CLHEP::mm;
}

double AgddGM::Cons::OuterRadiusPlusZ() const
{
    return fCone->OuterTopRadius() / CLHEP::mm;
}

double AgddGM::Cons::ZHalfLength() const
{
    return fCone->TotalLength()/2.0 / CLHEP::mm;
}

double AgddGM::Cons::StartPhi() const
{
    return fCone->StartingAngle() / CLHEP::degree;
}

double AgddGM::Cons::DeltaPhi() const
{
    return fCone->Angle() / CLHEP::degree;
}

