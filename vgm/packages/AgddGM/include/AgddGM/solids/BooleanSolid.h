// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_solids
//
/// \class AgddGM::BooleanSolid
///
/// VGM implementation of VBooleanSolid for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_BOOLEANSOLID_H
#define AGDD_GM_BOOLEANSOLID_H

#include "BaseVGM/solids/VBooleanSolid.h"

#include "CLHEP/Geometry/Transform3D.h"

#include <string>

namespace HepGeom { 
  class Transform3D; 
}

namespace AgddGM {

class BooleanSolid : public BaseVGM::VBooleanSolid
{
public:
    BooleanSolid(VGM::BooleanType type,
		 VGM::ISolid *a, VGM::ISolid *b,
		 const HepGeom::Transform3D& trana,
		 const HepGeom::Transform3D& tranb);
	
    virtual ~BooleanSolid();

    void SetName(std::string name);
    const HepGeom::Transform3D& InitialPosition() const;

    std::string Name() const;
    virtual VGM::BooleanType  BoolType() const;
    virtual VGM::ISolid*      ConstituentSolidA() const;
    virtual VGM::ISolid*      ConstituentSolidB() const;
    virtual VGM::Transform    Displacement() const;
    virtual bool              ToBeReflected() const;


private:
    std::string fName;
    VGM::BooleanType fType;
    VGM::ISolid *fA, *fB;
    HepGeom::Transform3D fPos, fDisp;
};

}

#endif  // AGDD_GM_BOOLEANSOLID_H
