// $Id$
//
// Class IWriter
// --------------
// The interface for the XML writer that
// writes VGM geometry objects to XML:
//
// Author: I. Hrivnacova, 16.01.2004 

#ifndef XML_VGM_WRITER_H
#define XML_VGM_WRITER_H

#include <string>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "VGM/common/Axis.h"

class VGM::IElement;
class VGM::IMaterial;
class VGM::ISolid;

namespace XmlVGM {

  class IWriter
  {
    public:
      virtual ~IWriter() {}

      // methods

      // XML elements 
      //
      virtual void OpenDocument() = 0;
      virtual void OpenSection(const std::string& topVolume) = 0;
      virtual void OpenPositions() = 0; 
      virtual void OpenRotations() = 0;     
      virtual void OpenMaterials() = 0; 
      virtual void OpenSolids() = 0; 
      virtual void OpenStructure() = 0; 
      virtual void OpenComposition(const std::string& name,
                                 const std::string& materialName) = 0;

      virtual void CloseDocument() = 0;
      virtual void CloseSection(const std::string& topVolume) = 0;
      virtual void ClosePositions() = 0;
      virtual void CloseRotations() = 0;
      virtual void CloseMaterials() = 0;
      virtual void CloseSolids() = 0;
      virtual void CloseStructure() = 0;
      virtual void CloseComposition() = 0;

      // Geometry elements
      //
      virtual void WriteElement(const VGM::IElement* element) = 0; 
      virtual void WriteMaterial(const VGM::IMaterial* material) = 0; 
      virtual void WriteSolid(std::string lvName, const VGM::ISolid* solid, 
                            std::string materialName) = 0; 
      virtual void WritePosition(const std::string& name, 
                            Hep3Vector position) = 0; 
      virtual void WriteRotation(const std::string& name, 
                            const HepRotation& rotation) = 0; 

      virtual void WritePlacement(const std::string& lvName, 
                            Hep3Vector position) = 0; 
      virtual void WritePlacementWithRotation(
                            std::string lvName, Hep3Vector position,
                            const HepRotation& rotation) = 0; 
      virtual void WritePlacementWithRotationAndReflection(
                            std::string lvName, Hep3Vector position,
                            const HepRotation& rotation) = 0; 
      virtual void WritePlacementWithRotation(
                             const std::string& lvName, 
			    const std::string& positionRef,
			    const std::string& rotationRef) = 0; 
      virtual void WriteMultiplePlacement(
                            const std::string& lvName,
                            VGM::Axis axis, int nofReplicas, 
			    double width, double offset) = 0;			       
      virtual void WriteEmptyLine() = 0;
      virtual void IncreaseIndention() = 0;
      virtual void DecreaseIndention() = 0;

      // Units
      //
      virtual double LengthUnit() const = 0;
      virtual double AngleUnit() const = 0;
      virtual double AtomicWeightUnit() const = 0;

      // Set/get precision
      //
      virtual void SetNumWidth(int width) = 0;
      virtual void SetNumPrecision(int precision) = 0;
      virtual double GetNumWidth() const = 0;
      virtual double GetNumPrecision() const = 0;
  };

}

#endif //XML_VGM_WRITER_H

