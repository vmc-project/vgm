// $Id$
//
// Class VExporter
// --------------------
// Class for generation of geometry data files in XML,
// the XML format is independent from the geometry object model. 
// It has three abstract methods (for processing the volume tree)
// that have to be provided by derived classes.
//
// Author: I. Hrivnacova, 19.1.2004

#ifndef XML_VGM_V_EXPORTER_H
#define XML_VGM_V_EXPORTER_H

#include <fstream>
#include <string>
#include <set>
#include <map>

#include "VGM/common/ThreeVector.h"
#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"

namespace XmlVGM {

  class IWriter;
  
  class VExporter
  {
    public:
      typedef std::set <std::string, std::less<std::string> > StringSet; 
      typedef std::map <VGM::ThreeVector, std::string, 
                      std::less<VGM::ThreeVector> >  ThreeVectorMap; 
      typedef std::multimap <VGM::ThreeVector, const VGM::IElement*, 
                      std::less<VGM::ThreeVector> >  ElementMap; 
      typedef std::map <std::string, const VGM::IMaterial*, 
                      std::less<std::string> > MaterialMap; 

    public:
      VExporter(const VGM::IFactory* factory);
      // --> protected
      // VExporter();
      // VExporter(const VExporter& right);
      virtual ~VExporter();
 
      // methods
      void GenerateXMLGeometry();
      void GenerateXMLGeometry(const std::string& volumeName);

      // set methods
      void SetFileName(const std::string& fileName);
      void SetDebug(int debug);

      // get methods
      std::string GetFileName() const;
      int  Debug() const;

    protected:
      VExporter();
      VExporter(const VExporter& right);

      // operators
      VExporter& operator=(const VExporter& /*right*/);

      // abstract methods
      // specific to XML definition
      //
      virtual void GenerateGeometry(VGM::IVolume* volume) = 0;
      virtual void GenerateSection(VGM::IVolume* volume) = 0;
      virtual void ProcessVolume(VGM::IVolume* volume) = 0;  

      // methods
      //
      std::string  FindPositionName(VGM::ThreeVector position) const;
      std::string  FindRotationName(const VGM::Rotation& rotation) const;

      void GeneratePositions(VGM::IVolume* volume);
      void GenerateRotations(VGM::IVolume* volume);
      void GenerateMaterials(VGM::IVolume* volume);
      void GenerateSolids(VGM::IVolume* volume);

      void OpenFile(std::string filePath);
      void CloseFile();
      void ClearVolumeNames();
      
      VGM::ThreeVector Origin()   const;
      VGM::Rotation    Identity() const;

      // static data members
      static const std::string fgkUndefinedFileName; //default value of file name
                                     
      // data members
      //
      const VGM::IFactory*  fFactory; // VGM factory 
      IWriter*       fWriter;         //interface to XML writer 
      StringSet      fVolumeNames;    //set of volume names
      std::ofstream  fOutFile;        //output file
      std::string    fFileName;       //output file name
      int            fDebug;          //debug level

    private:
      // methods
      //
      void   CutName(std::string& name) const;
      double Round(double number) const;
 
      std::string  AddPositionToMap(const VGM::ThreeVector& position);
      std::string  AddRotationToMap(const VGM::Rotation& rotation);
      const VGM::IElement*  AddElementToMap(const VGM::IElement* element);
      const VGM::IMaterial* AddMaterialToMap(const VGM::IMaterial* material);
    
      void ProcessPositions(VGM::IVolume* volume); 
      void ProcessRotations(VGM::IVolume* volume); 
      void ProcessMaterials(VGM::IVolume* volume); 
      void ProcessSolids(VGM::IVolume* volume); 

      // data members
      //
      ThreeVectorMap     fPositions; //map between positions and their XML names
      ThreeVectorMap     fRotations; //map between rotations and their XML names
      ElementMap         fElements;  //map of elements
      MaterialMap        fMaterials; //map of materials
  };

}

// inline methods

inline void XmlVGM::VExporter::SetFileName(const std::string& fileName)
{ fFileName = fileName; }

inline void XmlVGM::VExporter::SetDebug(int debug)
{ fDebug = debug; }

inline std::string XmlVGM::VExporter::GetFileName() const
{ return fFileName; }

inline int XmlVGM::VExporter::Debug() const
{ return fDebug; }

#endif //XML_VGM_V_EXPORTER_H

