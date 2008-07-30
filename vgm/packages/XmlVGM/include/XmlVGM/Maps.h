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
/// \class XmlVGM::Maps
/// --------------------
/// Utility class for mapping XML element values to their names
/// within the XML exporter precision
///
/// \author I. Hrivnacova, 19.1.2004

#ifndef XML_VGM_MAPS_H
#define XML_VGM_MAPS_H

#include <string>
#include <map>

#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IMedium.h"
#include "VGM/common/Transform.h"
#include "VGM/common/ThreeVector.h"

namespace XmlVGM {

  class IWriter;

  class Maps
  {
    public:
      typedef std::map <VGM::ThreeVector, 
                        std::string, 
                        std::less<VGM::ThreeVector> >  ThreeVectorMap; 
      typedef std::multimap <VGM::ThreeVector, 
                        const VGM::IIsotope*, 
                        std::less<VGM::ThreeVector> >  IsotopeMap; 
      typedef std::multimap <VGM::ThreeVector, 
                        const VGM::IElement*, 
                        std::less<VGM::ThreeVector> >  ElementMap; 
      typedef std::map <std::string, 
                        const VGM::IMaterial*, 
                        std::less<std::string> >  MaterialMap; 
      typedef std::map <std::string, 
                        const VGM::IMedium*, 
                        std::less<std::string> >  MediumMap; 

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
      std::string AddBooleanPosition();
      std::string AddBooleanRotation();
      const VGM::IIsotope*  AddIsotope(const VGM::IIsotope* isotope);
      const VGM::IElement*  AddElement(const VGM::IElement* element);
      const VGM::IMaterial* AddMaterial(const VGM::IMaterial* material);
      const VGM::IMedium*   AddMedium(const VGM::IMedium* medium);
    
      std::string  FindPositionName(const VGM::Transform& transform) const;
      std::string  FindRotationName(const VGM::Transform& transform) const;
      
      void WriteAllPositions(IWriter* writer);
      void WriteAllRotations(IWriter* writer);
      void WriteAllIsotopes(IWriter* writer);
      void WriteAllElements(IWriter* writer);
      void WriteAllMaterials(IWriter* writer);
      void WriteAllMedia(IWriter* writer);
      void WriteAllMediaFromMaterials(IWriter* writer);

      void SetNumPrecision(double precision);

      void ClearAllMaps();

    protected:
      Maps();
      Maps(const Maps& right);

      // operators
      Maps& operator=(const Maps& /*right*/);

    private:
      // methods
      //
      void    CutName(std::string& name) const;
      double  Round2(double number) const;
      VGM::ThreeVector  PurifyAngles(const VGM::ThreeVector& rotation) const;
 
      // data members
      //
      double  fNumPrecision;  // numerical precision
      double  fAngleUnit;     // angle unit
      double  fLengthUnit;    // length unit
      
      ThreeVectorMap     fPositions; //map between positions and their XML names
      ThreeVectorMap     fRotations; //map between rotations and their XML names
      IsotopeMap         fIsotopes;  //map of isotopes
      ElementMap         fElements;  //map of elements
      MaterialMap        fMaterials; //map of materials
      MediumMap          fMedia;     //map of media
      int                fNofBoolPositions; // number of positions in Boolean solids
      int                fNofBoolRotations; // number of rotations in Boolean solids
  };

}

inline void XmlVGM::Maps::SetNumPrecision(double precision)
{ /// Set numerical precision
  fNumPrecision = precision; }


#endif //XML_VGM_MAPS_H

