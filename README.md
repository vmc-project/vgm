
 Virtual Geometry Model (VGM)
 ============================

 Virtual Geometry Model (VGM) is a geometry conversion tool, actually providing conversion between Geant4 and ROOT TGeo geometry models. Its design allows inclusion of another geometry model by implementing a single sub-module instead of writing bilateral converters for all already supported models.

 The reference paper: [I. Hrivnacova et al 2008 J. Phys.: Conf. Ser. 119 042016](http://iopscience.iop.org/article/10.1088/1742-6596/119/4/042016/pdf)

 [![License: GPL v2](https://img.shields.io/badge/License-GPLv2-blue.svg)](http://www.gnu.org/licenses/gpl-2.0)

 Content:

 * [Introduction](#introduction)
 * [Installation, Examples](#installation-examples)
 * [Geometry conversions](#geometry-conversions)
 * [Geometry construction via VGM](#geometry-construction-via-vgm)
 * [XML](#xml)
 * [Options](#pptions)
 * [Platforms](#platforms)
 * [Files](#files)


 ## Introduction

 The Virtual Geometry Model (VGM) has been developed as generalization
 of existing convertors roottog4, g4toxml provided within
 <a href="http://root.cern.ch/root/vmc/VirtualMC.html"> Geant4 VMC </a>
 when new directions: g4toroot, roottoxml were asked by users.
 Instead of adding other bilateral converters and multiplying
 the implementations, the abstract layer to geometry has been defined
 and the geometry models have been "mapped" to this generalized
 models. Once this is done, the geometry objects in different models
 can be handled in the same way.

 In the VGM, the abstract interfaces to geometry objects and an abstract
 factory for geometry construction, import and export are introduced.
 The interfaces to geometry objects were defined to be
 suitable to describe "geant-like" geometries with a hierarchical volume
 structure.

 The implementation of the VGM for a concrete geometry model represents
 a layer between the VGM and the particular native geometry.
 At present  this implementation is provided for the Geant4 and
 Root TGeo.

 Using the VGM factory, geometry can first be defined independently from
 a concrete geometry model, and then built by choosing a concrete
 instantiation of it. Alternatively, the import function of the VGM factory
 makes it possible to use VGM directly with native geometries (Geant4,
 TGeo). The export functions provide conversion into other native
 geometries or the XML format.

 To port a third geometry model, then providing the VGM layer for it is
 sufficient to obtain all the converters between this third geometry and
 already ported geometries (Geant4, Root).

 ## Installation, Examples

 Since version 4.0, only CMake build system is supported.
 The installation and testing procedures for this system are described in detail
 in vgm/doc/INSTALL.

 The CMT and Autoconf build systems are removed (for maintenance reasons)
 and GNUmake build system is temporarily kept.

 As the test program (being written for the purpose of testing of all
 features) is too complex, four simple examples demonstrating use
 of VGM for converting native geometries are provided in vgm/examples.
 A detailed guide how to build and run the examples is included
 in the README file in each example.


 ## Geometry conversions

 To convert native geometry from one geometry model to another,
 the geometry has to be first imported in the VGM (the native geometry
 objects are mapped to the VGM interfaces) using the concrete VGM factory
 for this geometry model, and then exported using the VGM factory for
 the other geometry model.

 To convert Geant4 geometry in Root:
```cpp
 #include "Geant4GM/volumes/Factory.h"
 #include "RootGM/volumes/Factory.h"
 #include "TGeoManager.h"

  // Import Geant4 geometry to VGM
  //
  Geant4GM::Factory g4Factory;
  g4Factory.Import(physiWorld);
     // where physiWorld is of G4VPhysicalVolume* type

  // Export VGM geometry to Root
  //
  RootGM::Factory rtFactory;
  g4Factory.Export(&rtFactory);
  gGeoManager->CloseGeometry();

  // Return top volume
  //
  return rtFactory.World();
      // returns Root top volume, of TGeoVolume* type

  The geometry conversions between Geant4 and Root
  geometry models are demonstrated in examples E01 and E02.

  Since version 4.4, it is also to use VGM to convert a single solid from one geometry
  model into another one:

  XFactory xFactory;
  YFactory yFactory;
  xFactory.Import(xsolid);
  xFactory.Export(yFactory);
  YSolid* ysolid = yFactory.Solid();
```

 ## Geometry construction via VGM

 The VGM interfaces can be used to define geometry independently
 from a concrete geometry model:

```cpp
 #include "VGM/volumes/IFactory.h"
 #include "ClhepVGM/transform.h"

 using namespace VGM;

 MyDetectorConstruction::Construct(VGM::IFactory* factory)
 {
   double wSize = 10*m;
   GISolid* worldS
     = factory->CreateBox("worldS", wSize, wSize, wSize);
                // create the world solid

   GIVolume* worldV
     = factory->CreateVolume("worldV", worldS, "Air");
                // create the world volume

   factory->CreatePlacement("world", 0, worldV, ClhepVGM::Identity());
                // place the world volume
 }    

 Choosing the concrete factory (Geant4 or Root VGM factory)
 will then build the geometry of the chosen model ( Geant4 or Root):

 #include "Geant4GM/volumes/Factory.h"
 MyDetectorConstruction myDetectorConstruction;
 Geant4GM::Factory theFactory;
 myDetectorConstruction->Construct(&theFactory);
         // Geant4 geometry will be built

 #include "RootGM/volumes/Factory.h"
 MyDetectorConstruction myDetectorConstruction;
 RootGM::Factory theFactory;
 myDetectorConstruction->Construct(&theFactory);
         // Root geometry will be built
 ```


 ## XML

 The VGM geometry can be exported to XML in the AGDD or GDML format.
 The complying with the XML schema is embedded in the VGM XML exporter
 code itself, no external XML parser is then needed.

```cpp
 #include "XmlVGM/AGDDExporter.h"
 XmlVGM::AGDDExporter xmlExporter1(&theFactory);
 xmlExporter1.GenerateXMLGeometry();
      // Export geometry to AGDD

 #include "XmlVGM/GDMLExporter.h"
 XmlVGM::GDMLExporter xmlExporter2(&theFactory);
 xmlExporter2.GenerateXMLGeometry();
      // Export geometry to GDML
 ```

 The export from native geometries (Geant4, Root) to XML
 is demonstrated in examples E03 and E04.
 The exported XML files (both AGDD, GDML) can be then viewed
 with the GraXML tool.

 ## Options

 #### Debug

 Debug printing can be switched on via VGM::IFactory::SetDebug function:

```cpp
 IFactory& myFactory;
 myFactory.SetDebug(n);
      where n=1 or 2; if 2 also object adresses are printed
```

 #### Ignore

 If geometry imported in VGM includes some solid not supported
 in VGM (eg. a user defined solid in Geant4), then VGM prints a warning
 and stops. It is however possible to let VGM continue by setting the option
 "Ignore" to the factory importing the geometry:

```cpp
 IFactory& myFactory;
 myFactory.SetIgnore(true);
```

 #### BestMatch

 This option is used only in the context of a division with gaps in Root geometry.
 As there is not an equivalent placement in Root, this feature is emulated by default via an intermediate division without gaps and a placement of the cell volumes.
 This however results in a different volume hierarchy than in the source (Geant4 geometry).

 When a new, "bestMatch" option is selected, this feature is implemented via simple placements of the cells in the mother volume, what may be however ineffiecient in case of a large number of divisions.

```cpp
 IFactory& myFactory;
 myFactory.SetBestMatch(true);
```

 ## Platforms

 Tested on platform:
 Tested platform: Mac OSX 10.14: with Apple LLVM version 10.0.0

 ## Files

    cmake    - CMake configuration files
    doc      - documents:
               INSTALL  - Installation guides (available for GNUmake, CMake,
                          Autoconf and CMT)
               INSTALL.GNUmake  - Installation guides for GNUmake (now deprecated)
               README   - VGM User's guide (This file)
               VGM.html - VGM Web page
               VGMhistory.txt  - versions description  
    examples - examples for use of VGM
    packages - source code:
         VGM       - interfaces
         ClhepVGM  - conversion functions between CLHEP and VGM
                     transformations
         BaseVGM   - common implementation
         Geant4GM  - VGM implementation for Geant4
         RootGM    - VGM implementation for Root TGeo
         XmlVGM    - XML eporters
    test     - test code
    Deprecated:
    config   - general makefiles for GNUmake build
               setup.(c)sh - script for setting environment for GNUmake build
