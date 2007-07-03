// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/volumes/Placement.h>
#include <AgddGM/volumes/Volume.h>
#include <AgddGM/solids/BooleanSolid.h>

#include <ClhepVGM/transform.h>
#include <VGM/volumes/IVolume.h>

#include <CLHEP/Geometry/Transform3D.h>
#include <cassert>
#include <iostream>
using namespace std;

AgddGM::Placement::Placement(const std::string& name, 
			     AgddGM::Volume* volume, AgddGM::Volume* parent,
			     const HepGeom::Transform3D& transform)
    : VGM::IPlacement()
    , BaseVGM::VPlacement(volume,parent)
    , fName(name)
    , fCopyNo(0)
{

    if (parent) {
	fCopyNo = parent->NameCount()[name];
	parent->NameCount()[name] = fCopyNo + 1;
    }


    // Hack because AGDD booleans can carry around an initial placement
    AgddGM::BooleanSolid* bol = dynamic_cast<AgddGM::BooleanSolid*>(volume->Solid());
    if (bol) {
	fTrans = ClhepVGM::Transform(transform * bol->InitialPosition());
    }
    else {
	fTrans = ClhepVGM::Transform(transform);
    }
    // fixme: stacks need this too?


    cerr << "Place \"" << name << "\" #" << fCopyNo
	 << " of volume \"" << volume->Name() << "\" at "
	 << (void*)volume << " in parent \""
	 << (parent ? parent->Name() : "TOP") << "\" using transform: [";
    string comma = "";
    for (size_t ind=0; ind<fTrans.size(); ++ind) {
	cerr << comma << fTrans[ind];
	comma = ",";
    }
    cerr << "]\n";
}

VGM::PlacementType AgddGM::Placement::Type() const
{
    /*
      one of

      IPlacement::
      
      kSimplePlacement,
      kMultiplePlacement,
      //kParameterised,
      kUnknownPlacement
    */
    return VGM::kSimplePlacement;
}

std::string AgddGM::Placement::Name() const
{
    return fName;
}

int AgddGM::Placement::CopyNo() const
{
    return fCopyNo;
}
 
VGM::Transform AgddGM::Placement::Transformation() const
{
    return fTrans;
}

bool AgddGM::Placement::MultiplePlacementData(VGM::Axis&  /*axis*/,
					      int&     /*nofDivisions*/,
					      double&  /*width*/,
					      double&  /*offset*/) const
{
    // fixme: complete
    assert(0);
    return false;
}
    
