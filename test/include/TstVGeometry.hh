// $Id$

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstVGeometry
// --------------------------
// The interface to test geometry builders
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_V_GEOMETRY_H
#define TST_V_GEOMETRY_H

#include "VGM/solids/ISolid.h"

class TstVGeometry
{
  public:
    TstVGeometry();
    virtual ~TstVGeometry();

    virtual void  DefineMaterials() = 0;

    virtual void* TestSolids(bool fullPhi = true) = 0;
    virtual void* TestExtraSolid(VGM::SolidType solidType) = 0;
    virtual void* TestNewSolid() = 0;
    virtual void* TestNewSolid2() = 0;
    virtual void* TestPlacements() = 0;
    virtual void* TestPlacements2(bool bestMatch = false) = 0;
    virtual void* TestReflections(bool fullPhi = true) = 0;
    virtual void* TestScaledSolids(bool fullPhi = true) = 0;
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1() = 0;
    virtual void* TestBooleanSolids2() = 0;
    virtual void* TestBooleanSolids3() = 0;
    virtual void* TestBooleanSolids4();
    virtual void* TestBooleanSolids5();
    virtual void* TestBooleanSolids6();
    virtual void* TestBooleanSolids7();
    virtual void* TestDisplacedSolids1();
    virtual void* TestDisplacedSolids2();
    virtual void* TestSpecial();
};

#endif //TST_V_GEOMETRY_BUILDER_H

