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
/// \class XmlVGM::AGDDExporter
///
/// Class for generation of geometry data files in XML,
/// in the AGDD XML format.
///
/// \author I. Hrivnacova, 19.1.2004

#ifndef XML_VGM_AGDD_EXPORTER_H
#define XML_VGM_AGDD_EXPORTER_H

#include "XmlVGM/VExporter.h"

class VGM::IFactory;
class VGM::IVolume;

namespace XmlVGM {

  class AGDDExporter : public VExporter
  {
    public:
      AGDDExporter(const VGM::IFactory* factory);
      // --> protected
      // AGDDExporter();
      // AGDDExporter(const AGDDExporter& right);
      virtual ~AGDDExporter();

    protected:
      AGDDExporter();
      AGDDExporter(const AGDDExporter& right);

      // operators
      AGDDExporter& operator=(const AGDDExporter& right);

      // methods
      // (specific to XML definition)
      //
      virtual void GenerateGeometry(VGM::IVolume* volume);
      virtual void GenerateSection(VGM::IVolume* volume);
      virtual void ProcessVolume(VGM::IVolume* volume); 

    private:
      ThreeVector Identity() const;
  };

}

#endif //XML_VGM_AGDD_EXPORTER_H

