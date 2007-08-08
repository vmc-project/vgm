// $Id: $

// -----------------------------------------------------------------------
// The example program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova, Brett Viren            
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr, bv@bnl.gov
// -----------------------------------------------------------------------

#include <AGDD/XercesParser.hh>
#include <AGDD/IDocument.hh>
#include <AGDD/AGDD_DocumentVisitor.hh>
#include <AGDD/AGDD_Description.hh>
#include <AGDD/AGDD_Model.hh>
#include <AGDD/AGDD_Dumper.hh>

#include <AgddGM/volumes/Factory.h>
#include <RootGM/volumes/Factory.h>
#include <TGeoManager.h>

#include <iostream>

using namespace std;

int main()
{
  // Parse AGDD file
  //
  agdd::XercesParser p;
  agdd::IDocument* doc = p.Parse("geometry.agdd");

  agdd::AGDD_DocumentVisitor dv;

  doc->Visit(&dv);

  // have to break const, AGDD is not very const correct.
  agdd::AGDD* agdd = const_cast<agdd::AGDD*>(dv.agdd->evaluate());

  //agdd::AGDD_Dumper dumper(cout);
  //dumper.dump(agdd);

  // Import AGDD in VGM
  //
  AgddGM::Factory agddFactory;
  if ( ! agddFactory.Import(agdd) ) {
     cerr << "AgddGM::Factory::Import failed" << endl;
     exit(1);
  }

  // Export in Root
  //
  RootGM::Factory rootFactory;
  agddFactory.Export(&rootFactory);
  if ( ! rootFactory.Top() ) {
      cerr << "No top placement for root factory.";
      exit(1);
  }
  gGeoManager->CloseGeometry();
  gGeoManager->Export("geometry.root");
  return 0;
}
