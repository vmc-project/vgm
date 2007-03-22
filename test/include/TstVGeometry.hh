// $Id$
//
// Class TstVGeometry
// --------------------------
// The interface to test geometry builders
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_V_GEOMETRY_H
#define TST_V_GEOMETRY_H

class TstVGeometry 
{
  public:
    TstVGeometry();
    virtual ~TstVGeometry();

    virtual void  DefineMaterials() = 0;
    
    virtual void* TestSolids(bool fullPhi = true) = 0;
    virtual void* TestNewSolid() = 0;
    virtual void* TestPlacements() = 0;
    virtual void* TestReflections(bool fullPhi = true) = 0;
    virtual void* TestAssemblies() = 0;
    virtual void* TestAssemblies2() = 0;
    virtual void* TestBooleanSolids1() = 0;
    virtual void* TestBooleanSolids2() = 0;
    virtual void* TestBooleanSolids3() = 0;
    virtual void* TestBooleanSolids4();
    virtual void* TestBooleanSolids5();
    virtual void* TestSpecial();
};

#endif //TST_V_GEOMETRY_BUILDER_H

