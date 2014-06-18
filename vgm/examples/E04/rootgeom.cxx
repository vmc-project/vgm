// $Id$

// -----------------------------------------------------------------------
// The example program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

// VGM demo
#include "RootGM/volumes/Factory.h"
#include "XmlVGM/AGDDExporter.h"
#include "XmlVGM/GDMLExporter.h"
// end VGM demo

#include "TApplication.h"
#include "TROOT.h"
#include "TInterpreter.h"
#include "TGeoManager.h"

int main(int argc,char** argv)
{
  TApplication theApp("otherwise it does not work", &argc, argv);

  // Create Root geometry by running Root macro
  //
  gROOT->LoadMacro("rootgeom.C");
  gInterpreter->ProcessLine("rootgeom()");
  
  // Draw ROOT geometry
  //
  gGeoManager->SetVisLevel(4);
  gGeoManager->GetTopVolume()->Draw();

  // VGM demo
  // Import Root geometry to VGM
  //
  RootGM::Factory factory;
  factory.Import(gGeoManager->GetTopNode());
  
  // Export geometry to AGDD
  //
  XmlVGM::AGDDExporter xmlExporter1(&factory);
  xmlExporter1.GenerateXMLGeometry();

  // Export geometry to AGDD
  //
  XmlVGM::GDMLExporter xmlExporter2(&factory);
  xmlExporter2.GenerateXMLGeometry();
  // end VGM demo

  theApp.Run();

  return 0;
}  
