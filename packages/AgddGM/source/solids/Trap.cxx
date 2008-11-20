// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include "AgddGM/solids/Trap.h"

#include "AGDD/AGDD_Model.hh"

#include "CLHEP/Units/SystemOfUnits.h"

AgddGM::Trap::Trap(agdd::AGDD_GeneralTrapezoid* trap)
    : fTrap(trap)
{
}


std::string AgddGM::Trap::Name() const
{
    return fTrap->getName();
}


double AgddGM::Trap::ZHalfLength() const
{
    return fTrap->Z()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::Theta() const
{
    return fTrap->Theta() / CLHEP::degree;
}

double AgddGM::Trap::Phi() const
{
    return fTrap->Phi() / CLHEP::degree;
}

double AgddGM::Trap::YHalfLengthMinusZ() const
{
    return fTrap->Y1()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::XHalfLengthMinusZMinusY() const
{
    return fTrap->X1()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::XHalfLengthMinusZPlusY() const
{
    return fTrap->X2()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::AlphaMinusZ() const
{
    return fTrap->Alpha1() / CLHEP::degree;
}

double AgddGM::Trap::YHalfLengthPlusZ() const
{
    return fTrap->Y2()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::XHalfLengthPlusZMinusY() const
{
    return fTrap->X3()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::XHalfLengthPlusZPlusY() const
{
    return fTrap->X4()/2.0 / CLHEP::mm;
}

double AgddGM::Trap::AlphaPlusZ() const
{
    return fTrap->Alpha2() / CLHEP::degree;
}

