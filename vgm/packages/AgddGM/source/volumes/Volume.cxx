// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/volumes/Volume.h>
#include <AGDD/AGDD_Model.hh>

AgddGM::Volume::Volume(VGM::ISolid* solid, agdd::AGDD_Solid* agdd_sol)
    : BaseVGM::VVolume(solid), fSol(agdd_sol)
{
    fName = fSol->getName();
}
AgddGM::Volume::~Volume() 
{
}
std::string AgddGM::Volume::Name() const
{
    return fName;
}
void AgddGM::Volume::SetName(std::string name)
{
    fName = name;
}
std::string AgddGM::Volume::MaterialName() const
{
    // fixme: diff between mat and med?
    return fSol->m_material_name;
}
std::string AgddGM::Volume::MediumName() const
{
    // fixme: diff between mat and med?
    return fSol->m_material_name;
}
