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
/// \class XmlVGM::AGDDWriter
///
/// The implementation of the interface for the XML writer that
/// writes VGM geometry objects to XML defined by AGDD.dtd
/// (ATLAS Generic Detector Description)
///
/// \author I. Hrivnacova, 16.01.2004 

#ifndef XML_VGM_AGDD_WRITER_H
#define XML_VGM_AGDD_WRITER_H

#include <fstream>
#include <vector>
#include <string>
#include <set>

#include "VGM/solids/ISolid.h"
#include "VGM/solids/IBooleanSolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ITubs.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"

#include "XmlVGM/IWriter.h"
#include "XmlVGM/Maps.h"

class VGM::IMaterial;
class VGM::IElement;
class VGM::IVolume;
class VGM::IPlacement;

namespace XmlVGM {

  class AGDDWriter : public virtual IWriter
  {
    public:
      AGDDWriter(const std::string& version = "Undefined", 
                 const std::string& author = "VGM AGGD Writer", 
	         const std::string dtdVersion = "v7");
      virtual ~AGDDWriter();

      // methods

      // XML elements 
      //
      virtual void OpenFile(std::string filePath);
      virtual void OpenDocument();
      virtual void OpenSection(const std::string& topVolume);
      virtual void OpenPositions() {} 
      virtual void OpenRotations() {}     
      virtual void OpenMaterials();
      virtual void OpenMedia();
      virtual void OpenSolids() {} 
      virtual void OpenStructure() {} 
      virtual void OpenComposition(const std::string& name,
                                   const std::string& /*materialName*/);

      virtual void CloseFile();
      virtual void CloseDocument();
      virtual void CloseSection(const std::string& /*topVolume*/);
      virtual void ClosePositions() {}
      virtual void CloseRotations() {}
      virtual void CloseMaterials();
      virtual void CloseMedia();
      virtual void CloseSolids() {}
      virtual void CloseStructure() {}
      virtual void CloseComposition();

      // Geometry elements
      //
      virtual void WriteIsotope(const VGM::IIsotope* isotope);
       
      virtual void WriteElement(const VGM::IElement* element);
    
      virtual void WriteMaterial(const VGM::IMaterial* material); 
    
      virtual void WriteMedium(const VGM::IMedium* medium);
      virtual void WriteMedium(const VGM::IMaterial* material); 

      virtual void WriteSolid(std::string lvName, 
                            const VGM::ISolid* solid, 
                            std::string mediumName); 
			    
      virtual void WritePosition(const std::string& /*name*/, 
                            const VGM::Transform& /*position*/) {} 
      virtual void WriteRotation(const std::string& /*name*/, 
                            const VGM::Transform& /*rotation*/) {} 
      virtual void WriteScale(const std::string& /*name*/)      {} 

              void WritePlacement(const std::string& lvName, 
                            const ThreeVector& position); 
      virtual void WritePlacement(
                            const VGM::IPlacement& placement); 

      // Formatting utilities
      //
      virtual void WriteEmptyLine();
      virtual void IncreaseIndention();
      virtual void DecreaseIndention();
    
      // Units
      //
      virtual double LengthUnit() const;
      virtual double AngleUnit() const;
      virtual double AtomicWeightUnit() const;
      virtual double MassDensityUnit() const;

      // Set methods
      //
      virtual void SetNumWidth(int width);
      virtual void SetNumPrecision(int precision);

      // Get methods
      //
      virtual double GetNumWidth() const;
      virtual double GetNumPrecision() const;

    protected:
       AGDDWriter(const AGDDWriter& rhs); 

    private:
      // types
      //
      typedef std::set <std::string, std::less<std::string> > StringSet; 

      // Utility methods
      //
      std::string ElementSymbol(const VGM::IElement* element) const;                       
      void RegisterName(const std::string& name, bool warning = true);
      double  Round2(double number) const;
      bool    IsIdentity(const ThreeVector& rotation) const;
   
      // Writing solids
      //
      void WriteBooleanSolid (std::string lvName, 
                   const VGM::IBooleanSolid* booleanSolid,  
                   std::string mediumName); 
		   
      void WriteBox (std::string lvName, 
                   double hx, double hy, double hz,  
                   std::string mediumName); 
		   
      void WriteBox (std::string lvName, const VGM::IBox*  box,  
                     std::string mediumName); 
		     
      void WriteCons(std::string lvName, const VGM::ICons* cons, 
                   std::string mediumName); 
		   
      void WritePara(std::string lvName, const VGM::IPara* para, 
                   std::string mediumName); 
		   
      void WritePolycone(std::string lvName, const VGM::IPolycone* polycone, 
                   std::string mediumName);
		    
      void WritePolyhedra(std::string lvName, const VGM::IPolyhedra* polyhedra, 
                   std::string mediumName); 
		   
      void WriteTrap(std::string lvName, const VGM::ITrap* trap, 
                    std::string mediumName); 
		    
      void WriteTrd (std::string lvName, const VGM::ITrd*  trd,  
                   std::string mediumName); 
		   
      void WriteTubs(std::string lvName, const VGM::ITubs* tubs, 
                   std::string mediumName); 
		   
      void WriteNotSupportedSolid(std::string name, std::string mediumName); 
  
      // Writing placements
      //
      virtual void WritePlacementWithRotation(
                            std::string lvName, 
			    const ThreeVector& position,
   			    const ThreeVector& rotation);
			    
      virtual void WritePlacementWithRotationAndReflection(
                            std::string lvName, 
			    const ThreeVector& position,
                            const ThreeVector& rotation); 
			    
      virtual void WriteMultiplePlacement(
                            const std::string& lvName,
                            VGM::Axis axis, int nofReplicas, 
			    double width, double offset);			       

      // static data members
      //
      static const int fgkDefaultNumWidth;      //default output numbers width
      static const int fgkDefaultNumPrecision;  //default output numbers precision 
      static const std::string  fgkCompNameExtension; //name extension for composition
      static const std::string  fgkElementNameExtension; //element name extension 
      static const std::string  fgkMaterialNameExtension;//material name extension 

      // data members
      //
      std::ofstream      fOutFile;          //output file
      std::string        fVersion;          //geometry version
      std::string        fAuthor;           //geometry author
      std::string        fDtdVersion;       //DTD version
      const std::string  fkBasicIndention;  //basic indention 
      std::string        fIndention;        //indention string
      int                fNW;               //output numbers width
      int                fNP;               //output numbers precision 
      StringSet          fAGDDNames;        //names in GDML 
      Maps*              fMaps;             //name maps
  };

}

// inline functions

inline double XmlVGM::AGDDWriter::LengthUnit() const
{ return 10.; }    // cm

inline double XmlVGM::AGDDWriter::AngleUnit() const
{ return  1.; }    // deg

inline double XmlVGM::AGDDWriter::AtomicWeightUnit() const
{ return  1.; }   // g/mole

inline double XmlVGM::AGDDWriter::MassDensityUnit() const
{ return  1.; }   // g/cm3
 
inline void XmlVGM::AGDDWriter::SetNumWidth(int width)
{ fNW = width; }

inline void XmlVGM::AGDDWriter::SetNumPrecision(int precision)
{ fNP = precision; }

inline double XmlVGM::AGDDWriter::GetNumWidth() const
{ return fNW; }

inline double XmlVGM::AGDDWriter::GetNumPrecision() const
{ return fNP; }

#endif //XML_VGM_AGDD_WRITER_H

