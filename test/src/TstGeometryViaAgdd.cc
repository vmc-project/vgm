// $Id: TstGeometryViaAgdd.cc,v 1.13 2007/05/23 08:41:32 ivana Exp $

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

#include "TstGeometryViaAgdd.hh"

#include <AGDD/XercesParser.hh>
#include <AGDD/IDocument.hh>
#include <AGDD/AGDD_DocumentVisitor.hh>
#include <AGDD/AGDD_Description.hh>
#include <AGDD/AGDD_Dumper.hh>

const std::string TstGeometryViaAgdd::fgkDir = "agddv6/";
const std::string TstGeometryViaAgdd::fgkMaterialFileName = "Materials.agdd";
const std::string TstGeometryViaAgdd::fgkSolidsFileName = "Solids.agdd";
const std::string TstGeometryViaAgdd::fgkSolids2FileName = "Solids2.agdd";
const std::string TstGeometryViaAgdd::fgkNewSolidFileName = "NewSolid.agdd";
const std::string TstGeometryViaAgdd::fgkPlacementsFileName = "Placements.agdd";
const std::string TstGeometryViaAgdd::fgkReflectionsFileName = "Reflections.agdd";
const std::string TstGeometryViaAgdd::fgkReflections2FileName = "Reflections2.agdd";
const std::string TstGeometryViaAgdd::fgkAssemblies1FileName = "Assemblies1.agdd";
const std::string TstGeometryViaAgdd::fgkAssemblies2FileName = "Assemblies2.agdd";
const std::string TstGeometryViaAgdd::fgkBooleanSolids1FileName = "BooleanSolids1.agdd";
const std::string TstGeometryViaAgdd::fgkBooleanSolids2FileName = "BooleanSolids2.agdd";
const std::string TstGeometryViaAgdd::fgkBooleanSolids3FileName = "BooleanSolids3.agdd";

//_____________________________________________________________________________
TstGeometryViaAgdd::TstGeometryViaAgdd()
  : TstVGeometry()
{
//
}  

//_____________________________________________________________________________
TstGeometryViaAgdd::~TstGeometryViaAgdd()
{
}

//
// private methods
// 

//_____________________________________________________________________________
agdd::AGDD*  TstGeometryViaAgdd::LoadFile(const std::string& fileName)
{
  agdd::XercesParser p;
  std::string filePath = fgkDir + fileName; 
  agdd::IDocument* doc = p.Parse(filePath.c_str());

  agdd::AGDD_DocumentVisitor dv;

  doc->Visit(&dv);

  // have to break const, AGDD is not very const correct.
  return const_cast<agdd::AGDD*>(dv.agdd->evaluate());
}  

//
// public methods
// 

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestSolids(bool fullPhi)
{
  if ( fullPhi )
    return LoadFile(fgkSolidsFileName);
  else  
    return LoadFile(fgkSolids2FileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestExtraSolid(VGM::SolidType /*solidType*/)
{
  std::cout << "TestExtraSolids: not available in AGDD v6" << std::endl;
  return 0;
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestNewSolid()
{
  return LoadFile(fgkNewSolidFileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestNewSolid2()
{
  std::cout << "TestExtraSolids: not available in AGDD v6" << std::endl;
  return 0;
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestPlacements()
{
  return LoadFile(fgkPlacementsFileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestReflections(bool /*fullPhi*/)
{
/*
  if ( fullPhi )
    return LoadFile(fgkReflectionsFileName);
  else  
    return LoadFile(fgkReflections2FileName);
*/

  std::cout << "TestReflections: reflections not available in AGDD v6" << std::endl;

  return 0;
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestAssemblies()
{
  return LoadFile(fgkAssemblies1FileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestAssemblies2()
{
  std::cout << "TestAssemblies2: not available via AGDD" << std::endl;

  return 0;
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestBooleanSolids1()
{
  return LoadFile(fgkBooleanSolids1FileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestBooleanSolids2()
{
  return LoadFile(fgkBooleanSolids2FileName);
}

//_____________________________________________________________________________
void* TstGeometryViaAgdd::TestBooleanSolids3()
{
  return LoadFile(fgkBooleanSolids3FileName);
}
