// $Id$
//
// Class Maps
// --------------------
// Add 
//
// Author: I. Hrivnacova, 19.1.2004

#ifndef XML_VGM_MAPS_H
#define XML_VGM_MAPS_H

#include <string>
#include <map>

#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"

namespace XmlVGM {

  class IWriter;

  typedef std::vector<double> ThreeVector;

  class Maps
  {
    public:
      typedef std::map <ThreeVector, 
                        std::string, 
                        std::less<ThreeVector> >  ThreeVectorMap; 
      typedef std::multimap <ThreeVector, 
                        const VGM::IElement*, 
                        std::less<ThreeVector> >  ElementMap; 
      typedef std::map <std::string, 
                        const VGM::IMaterial*, 
                        std::less<std::string> >  MaterialMap; 

    public:
      Maps(double numPrecision,
           double angleUnit, double lengthUnit);
      // --> protected
      // Maps();
      // Maps(const Maps& right);
      virtual ~Maps();
 
      // methods
      std::string AddPosition(const VGM::Transform& transform);
      std::string AddRotation(const VGM::Transform& transform);
      const VGM::IElement*  AddElement(const VGM::IElement* element);
      const VGM::IMaterial* AddMaterial(const VGM::IMaterial* material);
    
      std::string  FindPositionName(const VGM::Transform& transform) const;
      std::string  FindRotationName(const VGM::Transform& transform) const;
      
      void WriteAllPositions(IWriter* writer);
      void WriteAllRotations(IWriter* writer);
      void WriteAllElements(IWriter* writer);
      void WriteAllMaterials(IWriter* writer);

      void ClearAllMaps();

    protected:
      Maps();
      Maps(const Maps& right);

      // operators
      Maps& operator=(const Maps& /*right*/);

    private:
      // methods
      //
      void         CutName(std::string& name) const;
      double       Round(double number) const;
      ThreeVector  PurifyAngles(const ThreeVector& rotation) const;
 
      // data members
      //
      double  fNumPrecision;  // numerical precision
      double  fAngleUnit;     // angle unit
      double  fLengthUnit;    // length unit
      
      ThreeVectorMap     fPositions; //map between positions and their XML names
      ThreeVectorMap     fRotations; //map between rotations and their XML names
      ElementMap         fElements;  //map of elements
      MaterialMap        fMaterials; //map of materials
  };

}

#endif //XML_VGM_MAPS_H

