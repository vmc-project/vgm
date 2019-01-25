// $Id$

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Author: I. Hrivnacova, 31.03.2004
//
// Class GDMLExporter
// ------------------------------
// See the class description in the header file.

#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"
#include "VGM/volumes/IPlacement.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/GDMLExporter.h"
#include "XmlVGM/GDMLWriter.h"

//_____________________________________________________________________________
XmlVGM::GDMLExporter::GDMLExporter(const VGM::IFactory* factory)
  : VExporter(factory, new GDMLWriter())
{
/// Standard constructor

  dynamic_cast<GDMLWriter*>(fWriter)->SetMaps(&fMaps);
}

//_____________________________________________________________________________
XmlVGM::GDMLExporter::GDMLExporter()
  : VExporter()
{
/// Protected default constructor
}

//_____________________________________________________________________________
XmlVGM::GDMLExporter::GDMLExporter(const GDMLExporter& right)
  : VExporter(right)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
XmlVGM::GDMLExporter::~GDMLExporter() {
//
}

// operators

//_____________________________________________________________________________
XmlVGM::GDMLExporter&
XmlVGM::GDMLExporter::operator=(const GDMLExporter& right)
{
/// Protected assignement operator

  // check assignement to self
  if (this == &right) return *this;

  // call assignement of the base class
  VExporter::operator=(right);

  return *this;
}

//
// protected methods
//

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::GenerateGeometry(VGM::IVolume* volume)
{
// Generate XML geometry file for the geometry tree
// starting from the specified VGM volume.

  // Compose filename
  std::string fileName;
  if (fFileName == fgkUndefinedFileName) {
    fileName = volume->Name();
    fileName = fileName + ".gdml";
  }
  else
    fileName = fFileName;

  // Open XML file and document
  fWriter->OpenFile(fileName);
  fWriter->OpenDocument();

  // Generate volumes tree
  GenerateSection(volume);

  // Close XML file and document
  fWriter->CloseDocument();
  fWriter->CloseFile();

  if (fDebug > 0)
    std::cout << "File " << fileName << " has been generated." << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::GenerateSection(VGM::IVolume* volume)
{
/// Generate the XML section element containing
/// all geometry objects defined in given logical volume:
/// positions, rotations, materials, solids and volumes hierarchy

  // Create section
  fWriter->OpenSection(volume->Name());
  fWriter->WriteEmptyLine();

  // Process basic elements needed by geometry tree
  GeneratePositions(volume);
  GenerateRotations(volume);
  GenerateMaterials(volume);
  GenerateSolids(volume);

  // Process geometry tree
  fWriter->OpenStructure();
  ProcessVolume(volume);
  fWriter->CloseStructure();
  fWriter->WriteEmptyLine();
  ClearVolumeNames();

  // Close section
  fWriter->CloseSection(volume->Name());
}

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::ProcessVolume(VGM::IVolume* volume)
{
/// Process the VGM volume tree

  int nofDaughters = volume->NofDaughters();

  if (nofDaughters == 0) {
    // Open composition
    fWriter->OpenComposition(volume->Name(),
                                volume->MaterialName());
  }
  else {

    // Recursively process daughters
    //
    for (int i=0; i<nofDaughters; i++) {

      VGM::IVolume* dVolume = volume->Daughter(i)->Volume();

      if (fVolumeNames.find(dVolume->Name()) == fVolumeNames.end())
        ProcessVolume(dVolume);
    }

    // Write the volume with its childs now
    //
    // Open composition
    fWriter->OpenComposition(volume->Name(),
                             volume->MaterialName());

    // Write positions
    for (int j=0; j<nofDaughters; j++) {

      if (fDebug > 1) {
        std::cout << "processing " << j << "th daughter of "
                  << volume->Name() << std::endl;
      }

      fWriter->WritePlacement(*volume->Daughter(j));
    }
  }

  // Close composition
  fWriter->CloseComposition();
  fWriter->WriteEmptyLine();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volume->Name());
}

