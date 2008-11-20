// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include "AgddGM/volumes/Factory.h"
#include "AgddGM/materials/MaterialFactory.h"


AgddGM::Factory::Factory()
    : BaseVGM::VFactory("agdd",new AgddGM::MaterialFactory)
    , fTop(0)
    , fAgdd(0)
{
}
AgddGM::Factory::~Factory()
{
}
AgddGM::Factory::Factory(const Factory& rhs)
    : VGM::IFactory(rhs)
    , BaseVGM::VFactory(rhs)
{
}
    
//
// methods
//
    

// top volume
//
VGM::IPlacement* AgddGM::Factory::Top() const
{
    return fTop;
}







