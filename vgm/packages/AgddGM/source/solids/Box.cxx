// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/Box.h>

#include <AGDD/AGDD_Model.hh>

#include <CLHEP/Units/SystemOfUnits.h>

AgddGM::Box::Box(agdd::AGDD_Box* box)
    : fBox(box)
{
}


std::string AgddGM::Box::Name() const
{
    return fBox->getName();
}
double AgddGM::Box::XHalfLength() const
{
    return fBox->X()/2.0 / CLHEP::mm;
}
double AgddGM::Box::YHalfLength() const
{
    return fBox->Y()/2.0 / CLHEP::mm;
}
double AgddGM::Box::ZHalfLength() const
{
    return fBox->Z()/2.0 / CLHEP::mm;
}
