// $Id$

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup XmlVGM
//
/// \class XmlVGM::GDMLExporter
///
/// Class for generation of geometry data files in XML,
/// in the GDML format.
///
/// \author I. Hrivnacova, 31.03.2004

#ifndef XML_VGM_GDML_EXPORTER_H
#define XML_VGM_GDML_EXPORTER_H

#include "XmlVGM/VExporter.h"

namespace VGM {
  class IFactory;
  class IVolume;
}

namespace XmlVGM {

  class GDMLExporter : public VExporter
  {
    public:
      GDMLExporter(const VGM::IFactory* factory);
      // --> protected
      // GDMLExporter(const GDMLExporter& right);
      virtual ~GDMLExporter();

    protected:
      GDMLExporter();
      GDMLExporter(const GDMLExporter& right);

      // operators
      GDMLExporter& operator=(const GDMLExporter& right);

      // methods
      // (specific to XML definition)
      //
      virtual void GenerateGeometry(VGM::IVolume* volume);
      virtual void GenerateSection(VGM::IVolume* volume);
      virtual void ProcessVolume(VGM::IVolume* volume);
  };

}

#endif //XML_VGM_GDML_EXPORTER_H

