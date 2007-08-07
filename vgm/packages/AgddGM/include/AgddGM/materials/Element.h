// $Id: Element.h,v 1.1 2007-01-25 21:57:12 bviren Exp $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_materials
//
/// \class AgddGM::Element
///
/// VGM implementation for AGDD_Element.
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_ELEMENT_H
#define AGDD_GM_ELEMENT_H

#include <VGM/materials/IElement.h>
#include <VGM/materials/IIsotope.h>
#include <string>
#include <map>

namespace agdd {
    class AGDD_Element;
}

namespace AgddGM {

class Element : public virtual VGM::IElement
{
public:
    typedef std::map<std::string,VGM::IIsotope*> IsotopeMap;

    Element(agdd::AGDD_Element* element, const IsotopeMap& isomap);
    virtual ~Element() {}
    
    // methods
    std::string Name() const;
    std::string Symbol() const;

    double  Z() const;     
    double  N() const;     
    double  A() const;     

    int NofIsotopes() const;
    VGM::IIsotope*  Isotope(int i) const;
    double RelAbundance(int i) const;
protected:  
    Element();
    Element(const Element& rhs) : VGM::IElement(rhs) {}
    
private:
  
    agdd::AGDD_Element* fElement;
    IsotopeMap fIsoMap;
};

}

#endif //AGDD_GM_ELEMENT_H
