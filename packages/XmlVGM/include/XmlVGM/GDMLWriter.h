// $Id$
//
// Author: I. Hrivnacova, 31.03.2004 
//
// Class GDMLWriter
// ----------------------
// The implementation of the interface for the XML writer that
// writes VGM geometry objects to XML defined by GDML scheme.

#ifndef XML_VGM_GDML_WRITER_H
#define XML_VGM_GDML_WRITER_H

#include <fstream>
#include <vector>
#include <set>

#include "CLHEP/Units/SystemOfUnits.h" 

#include "VGM/solids/ISolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"
#include "VGM/solids/ISphere.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITubs.h"

#include "XmlVGM/IWriter.h"

class VGM::IMaterial;
class VGM::IElement;

namespace XmlVGM {

  class GDMLWriter : public virtual IWriter
  {
    typedef std::vector<VGM::Rotation>  RotationMatrixVector;

    public:
      GDMLWriter(std::ofstream& outFile,
		 const std::string& unitName = "unit1", 
                 const std::string& version = "1.0"); 
      virtual ~GDMLWriter();

      // methods

      // XML elements 
      //
      virtual void OpenDocument();
      virtual void OpenSection(const std::string& topVolume);
      virtual void OpenPositions(); 
      virtual void OpenRotations();       
      virtual void OpenMaterials();
      virtual void OpenSolids(); 
      virtual void OpenStructure(); 
      virtual void OpenComposition(const std::string& name,
                                   const std::string& materialName);

      virtual void CloseDocument();
      virtual void CloseSection(const std::string& topVolume);
      virtual void ClosePositions();
      virtual void CloseRotations();
      virtual void CloseMaterials();
      virtual void CloseSolids();
      virtual void CloseStructure();
      virtual void CloseComposition();

      // Geometry elements
      //
      virtual void WriteElement(const VGM::IElement* element); 
      
      virtual void WriteMaterial(const VGM::IMaterial* material); 
      
      virtual void WriteSolid(
                            std::string lvName, 
                            const VGM::ISolid* solid, 
                            std::string materialName);
			     
      virtual void WritePosition(
                            const std::string& name, 
                            const VGM::ThreeVector& position); 
			    
      virtual void WriteRotation(
                            const std::string& name, 
                            const VGM::Rotation& rotation); 

      virtual void WritePlacement(
                            const std::string& /*lvName*/, 
                            const VGM::ThreeVector& /*position*/) {} 
			    
      virtual void WritePlacementWithRotation(
                            std::string /*name*/, 
			    const VGM::ThreeVector& /*position*/,
   			    const VGM::Rotation& /*rotation*/) {}
			    
      virtual void WritePlacementWithRotationAndReflection(
                            std::string /*name*/, 
			    const VGM::ThreeVector& /*position*/,
                            const VGM::Rotation& /*rotation*/) {} 
			    
      virtual void WritePlacementWithRotation(
                            const std::string& lvName, 
			    const std::string& positionRef,
			    const std::string& rotationRef);
			     
      virtual void WriteMultiplePlacement(
                            const std::string& lvName,
                            VGM::Axis axis, int nofReplicas, 
			    double width, double offset);			       

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

    private:
      // types
      typedef std::set <std::string, std::less<std::string> > StringSet; 

      //methods
      std::string UpdateName(const std::string& name,         
                             const std::string& extension = "") const;
      double UpdateAngle(double angle) const;
      void Append(std::string& name, int size, std::string string) const;
      void RegisterName(const std::string& name, bool warning = true);
      std::ostream& SmartPut(std::ostream& out,
		        int size, int precision,
		        const std::string& separator1, 
		        double number, const std::string& separator2) const;
    
           // writing solids
      void WriteBox (std::string lvName, 
                     double hx, double hy, double hz,  
                     std::string materialName); 
		    
      void WriteBox (std::string name, const VGM::IBox*  box,  
                     std::string materialName); 
		     
      void WriteTubs(std::string name, const VGM::ITubs* tubs, 
                     std::string materialName); 
		     
      void WriteCons(std::string name, const VGM::ICons* cons, 
                     std::string materialName); 
		     
      void WriteTrd (std::string name, const VGM::ITrd*  trd,  
                     std::string materialName); 
		     
      void WriteTrap(std::string name, const VGM::ITrap* trap, 
                     std::string materialName); 
		     
      void WritePara(std::string name, const VGM::IPara* para, 
                     std::string materialName); 
		     
      //void WritePolycone(std::string name, const VGM::IPolycone* polycone, 
      //               std::string materialName); 
      
      //void WritePolyhedra(std::string name, const VGM::IPolyhedra* polyhedra, 
      //               std::string materialName); 
      
      void WriteSphere(std::string name, const VGM::ISphere* sphere, 
                     std::string materialName); 
		     
      //void WriteTorus(std::string name, const VGM::ISphere* sphere, 
      //                std::string materialName); 
      
      void WriteNotSupportedSolid(std::string name, 
                        std::string materialName); 
  
      // static data members
      static const int          fgkDefaultNumWidth;     //default output numbers width
      static const int          fgkDefaultNumPrecision; //default output numbers precision 
      static const std::string  fgkSolidNameExtension;  //solid names extension 
      static const std::string  fgkElementNameExtension;//element names extension 
      static const char         fgkCharReplacement;     //replacement for ' ' in names 
      static const std::string  fgkNotAllowedChars;     //not allowed characters in XML
      static const std::string  fgkNotAllowedChars1;    //not allowed first characters
                                                        //in XML names

      // data members
      std::ofstream&     fOutFile;          //output file
      std::string        fUnitName;         //unit name
      std::string        fVersion;          //geometry version
      const std::string  fkBasicIndention;  //basic indention 
      std::string        fIndention;        //indention string
      int                fNW;               //output numbers width
      int                fNP;               //output numbers precision 
      StringSet          fGDMLNames;        //names in GDML 
  };

}

inline double XmlVGM::GDMLWriter::LengthUnit() const
{ return cm; }

inline double XmlVGM::GDMLWriter::AngleUnit() const
{ return deg; }

inline double XmlVGM::GDMLWriter::AtomicWeightUnit() const
{ return g/mole; }

inline double XmlVGM::GDMLWriter::MassDensityUnit() const
{ return g/cm3; }

inline void XmlVGM::GDMLWriter::SetNumWidth(int width)
{ fNW = width; }

inline void XmlVGM::GDMLWriter::SetNumPrecision(int precision)
{ fNP = precision; }

inline double XmlVGM::GDMLWriter::GetNumWidth() const
{ return fNW; }

inline double XmlVGM::GDMLWriter::GetNumPrecision() const
{ return fNP; }

#endif //XML_VGM_GDML_WRITER_H

