// $Id: TstGeometryViaAgdd.hh,v 1.7 2007/05/23 08:41:31 ivana Exp $

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstGeometryViaAgdd
// -------------------------------
// Class for building geometry via AGDD
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_GEOMETRY_VIA_AGDD_H
#define TST_GEOMETRY_VIA_AGDD_H

#include "TstVGeometry.hh"

#include <AGDD/AGDD_Model.hh>

#include <string>

class TstGeometryViaAgdd : public TstVGeometry 
{
  public:
    TstGeometryViaAgdd();
    virtual ~TstGeometryViaAgdd();

    virtual void  DefineMaterials() {}

    virtual void* TestSolids(bool fullPhi);
    virtual void* TestNewSolid();
    virtual void* TestPlacements();
    virtual void* TestReflections(bool fullPhi);
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();

  private:
    // methods
    agdd::AGDD* LoadFile(const std::string& fileName);
  
    // static data members
    static const std::string fgkDir;
    static const std::string fgkMaterialFileName;
    static const std::string fgkSolidsFileName;
    static const std::string fgkSolids2FileName;
    static const std::string fgkNewSolidFileName;
    static const std::string fgkPlacementsFileName;
    static const std::string fgkReflectionsFileName;
    static const std::string fgkReflections2FileName;
    static const std::string fgkAssemblies1FileName;
    static const std::string fgkAssemblies2FileName;
    static const std::string fgkBooleanSolids1FileName;
    static const std::string fgkBooleanSolids2FileName;
    static const std::string fgkBooleanSolids3FileName;
};

#endif //TST_GEOMETRY_VIA_GEANT4_H

