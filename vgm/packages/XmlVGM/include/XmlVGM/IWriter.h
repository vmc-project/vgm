// $Id$
/// \ingroup XmlVGM
//
/// \class XmlVGM::IWriter
///
/// The interface for the XML writer that
/// writes VGM geometry objects to XML:
///
/// Author: I. Hrivnacova, 16.01.2004 

#ifndef XML_VGM_WRITER_H
#define XML_VGM_WRITER_H

#include <string>

#include "VGM/common/Axis.h"
#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"
#include "VGM/volumes/IPlacement.h"

class VGM::IElement;
class VGM::IMaterial;

namespace XmlVGM {

  class IWriter
  {
    public:
      virtual ~IWriter() {}

      // methods

      // XML elements 
      //
		    ///
                    /// Open output file
      virtual void OpenFile(std::string filePath) = 0;
		    ///
                    /// Write XML document opening
      virtual void OpenDocument() = 0;
		    ///
                    /// Write the section opening (if present)
      virtual void OpenSection(const std::string& topVolume) = 0;
		    ///
                    /// Write positions definitions opening
      virtual void OpenPositions() = 0; 
		    ///
                    /// Write rotations definitions opening
      virtual void OpenRotations() = 0;     
		    ///
                    /// Write materials definitions opening
      virtual void OpenMaterials() = 0; 
		    ///
                    /// Write solids definitions opening
      virtual void OpenSolids() = 0; 
		    ///
                    /// Write structure definition opening (if present)
      virtual void OpenStructure() = 0; 
		    ///
                    /// Write composition definition opening (if present)
      virtual void OpenComposition(const std::string& name,
                                 const std::string& materialName) = 0;

		    ///
                    /// Close output file
      virtual void CloseFile() = 0;
		    ///
                    /// Write XML document closing
      virtual void CloseDocument() = 0;
		    ///
                    /// Write the section closing (if present)
      virtual void CloseSection(const std::string& topVolume) = 0;
		    ///
                    /// Write positions definitions closing
      virtual void ClosePositions() = 0;
		    ///
                    /// Write rotations definitions closing
      virtual void CloseRotations() = 0;
		    ///
                    /// Write materials definitions closing
      virtual void CloseMaterials() = 0;
		    ///
                    /// Write materials definitions closing
      virtual void CloseSolids() = 0;
		    ///
                    /// Write structure definition closing (if present)
      virtual void CloseStructure() = 0;
		    ///
                    /// Write composition definition closing (if present)
      virtual void CloseComposition() = 0;

      // Geometry elements
      //
		    ///
                    /// Write VGM element
      virtual void WriteElement(const VGM::IElement* element) = 0; 
		    ///
                    /// Write VGM material
      virtual void WriteMaterial(const VGM::IMaterial* material) = 0; 
		    ///
                    /// Write VGM solid
      virtual void WriteSolid(std::string lvName, 
                            const VGM::ISolid* solid, 
                            std::string materialName) = 0; 
		    ///
                    /// Write position (from VGM transformation)
      virtual void WritePosition(const std::string& name, 
                            const VGM::Transform& position) = 0; 
		    ///
                    /// Write rotation (from VGM transformation)
      virtual void WriteRotation(const std::string& name, 
                            const VGM::Transform& rotation) = 0; 
		    ///
                    /// Write VGM placement
      virtual void WritePlacement(
                            const VGM::IPlacement& placement) = 0; 
		    ///
                    /// Write empty line
      virtual void WriteEmptyLine() = 0;
		    ///
                    /// Increase indention
      virtual void IncreaseIndention() = 0;
		    ///
                    /// Decrease indention
      virtual void DecreaseIndention() = 0;

      // Units
      //
		     ///
                     /// Return the default length unit
      virtual double LengthUnit() const = 0;
		     ///
                     /// Return the default angle unit
      virtual double AngleUnit() const = 0;
		     ///
                     /// Return the default atomic weight unit
      virtual double AtomicWeightUnit() const = 0;
		     ///
                     /// Return the default mass density unit
      virtual double MassDensityUnit() const = 0;

      // Set methods
      //
		    ///
                    /// Set fixed format number width 
      virtual void SetNumWidth(int width) = 0;
		    ///
                    /// Set fixed format number precision
      virtual void SetNumPrecision(int precision) = 0;

      // Get methods
      //
		      ///
                      /// Return fixed format number width 
      virtual double GetNumWidth() const = 0;
		      ///
                      /// Return fixed format number precision
      virtual double GetNumPrecision() const = 0;
   };

}

#endif //XML_VGM_WRITER_H

