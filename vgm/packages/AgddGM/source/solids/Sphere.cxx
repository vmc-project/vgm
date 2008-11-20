// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include "AgddGM/solids/Sphere.h"

#include "AGDD/AGDD_Model.hh"

#include "CLHEP/Units/SystemOfUnits.h"


AgddGM::Sphere::Sphere(agdd::AGDD_Sphere* sphere)
    : fSphere(sphere)
{
}

std::string AgddGM::Sphere::Name() const
{
    return fSphere->getName();
}

double AgddGM::Sphere::InnerRadius() const
{
    return fSphere->InnerRadius() / CLHEP::mm;
}

double AgddGM::Sphere::OuterRadius() const
{
    return fSphere->OuterRadius() / CLHEP::mm;
}

double AgddGM::Sphere::StartPhi() const
{
    return fSphere->ProfileStart() / CLHEP::degree;
}

double AgddGM::Sphere::DeltaPhi() const
{
    return fSphere->DeltaProfile() / CLHEP::degree;
}

double AgddGM::Sphere::StartTheta() const
{
    return fSphere->SliceStart() / CLHEP::degree;
}

double AgddGM::Sphere::DeltaTheta() const
{
    return fSphere->DeltaSlice() / CLHEP::degree;
}

