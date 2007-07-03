// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/BooleanSolid.h>
#include <CLHEP/Geometry/Transform3D.h>
#include <ClhepVGM/transform.h>

using namespace std;

static string boolean_name(VGM::BooleanType type)
{
    switch (type) {
    case VGM::kIntersection: return "intersection";
    case VGM::kSubtraction: return "subtraction";
    case VGM::kUnion: return "union";
    default: return "boolean";
    }
}

AgddGM::BooleanSolid::BooleanSolid(VGM::BooleanType type,
				   VGM::ISolid *a, VGM::ISolid *b,
				   const HepGeom::Transform3D& trana,
				   const HepGeom::Transform3D& tranb)
    : fName(boolean_name(type)), fType(type), fA(a), fB(b)
    , fPos(trana)
    , fDisp(trana.inverse()*tranb)
{
    fName += "_";
    fName += a->Name();
    fName += "_";
    fName += b->Name();
}

AgddGM::BooleanSolid::~BooleanSolid()
{
}

const HepGeom::Transform3D& AgddGM::BooleanSolid::InitialPosition() const
{
    return fPos;
}

std::string AgddGM::BooleanSolid::Name() const
{
    return fName;
}
void AgddGM::BooleanSolid::SetName(string name)
{
    fName = name;
}

VGM::BooleanType AgddGM::BooleanSolid::BoolType() const
{
    return fType;
}

VGM::ISolid* AgddGM::BooleanSolid::ConstituentSolidA() const
{
    return fA;
}
VGM::ISolid* AgddGM::BooleanSolid::ConstituentSolidB() const
{
    return fB;
}

VGM::Transform AgddGM::BooleanSolid::Displacement() const
{
    return ClhepVGM::Transform(fDisp);
}

bool AgddGM::BooleanSolid::ToBeReflected() const
{
    return false;
}



