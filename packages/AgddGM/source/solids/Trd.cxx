// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/Trd.h>
#include <AGDD/AGDD_Model.hh>
#include <CLHEP/Units/SystemOfUnits.h>

AgddGM::Trd::Trd(agdd::AGDD_Trapezoid* trap)
    : fTrd(trap)
{
}


std::string AgddGM::Trd::Name() const
{
    return fTrd->getName();
}


double AgddGM::Trd::XHalfLengthMinusZ() const
{
    return fTrd->BottomXLength()/2.0 / CLHEP::mm;
}

double AgddGM::Trd::XHalfLengthPlusZ() const
{
    return fTrd->TopXLength()/2.0 / CLHEP::mm;
}

double AgddGM::Trd::YHalfLengthMinusZ() const
{
    return fTrd->BottomYLength()/2.0 / CLHEP::mm;
}

double AgddGM::Trd::YHalfLengthPlusZ() const
{
    return fTrd->TopYLength()/2.0 / CLHEP::mm;
}

double AgddGM::Trd::ZHalfLength() const
{
    return fTrd->Height()/2.0 / CLHEP::mm;
}

