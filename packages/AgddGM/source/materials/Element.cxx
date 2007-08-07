// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/materials/Element.h>
#include <AGDD/AGDD_Material_Model.hh>

AgddGM::Element::Element() : fElement(0)
{
}

AgddGM::Element::Element(agdd::AGDD_Element* element, const IsotopeMap& isomap)
    : fElement(element), fIsoMap(isomap)
{
}
    
    // methods
std::string AgddGM::Element::Name() const
{
    return fElement->m_symbol;
}
std::string AgddGM::Element::Symbol() const
{
    return fElement->m_symbol;
}

double  AgddGM::Element::Z() const
{
    if (fElement->m_atom) return fElement->m_atom->m_zeff;
    size_t siz = fElement->m_addisotopes.size();
    int totatoms = 0;
    double totz = 0;
    for (size_t ind=0; ind<siz; ++ind) {
	int natoms = fElement->m_addisotopes[ind]->m_natoms;
	agdd::AGDD_Isotope* iso = fElement->m_addisotopes[ind]->m_isotope;
	totatoms += natoms;
	totz += natoms*iso->m_z;
    }
    if (totatoms) return totz/totatoms;
    return 0.0;
}

double  AgddGM::Element::N() const
{
    if (fElement->m_addisotopes.size()) {
	return fElement->m_addisotopes[0]->m_isotope->m_n;
    }
    return 0;
}
double  AgddGM::Element::A() const
{
    if (fElement->m_atom) return fElement->m_atom->m_aweight;
    size_t siz = fElement->m_addisotopes.size();
    int totatoms = 0;
    double tota = 0;
    for (size_t ind=0; ind<siz; ++ind) {
	int natoms = fElement->m_addisotopes[ind]->m_natoms;
	agdd::AGDD_Isotope* iso = fElement->m_addisotopes[ind]->m_isotope;
	totatoms += natoms;
	tota += natoms*iso->m_a;
    }
    if (totatoms) return tota/totatoms;
    return 0.0;
}

int AgddGM::Element::NofIsotopes() const
{
    return fIsoMap.size();
}

VGM::IIsotope*  AgddGM::Element::Isotope(int index) const
{
    std::string name = fElement->m_addisotopes[index]->m_isotope_name;
    IsotopeMap::const_iterator it = fIsoMap.find(name);
    if (it == fIsoMap.end()) return 0;
    VGM::IIsotope* iso = it->second;
    return iso;
}

double AgddGM::Element::RelAbundance(int index) const
{
    if (fElement->m_atom) return 1;

    size_t siz = fElement->m_addisotopes.size();
    if (index >= int(siz)) return 0;

    int totatoms = 0;
    for (size_t ind=0; ind<siz; ++ind) {
	int natoms = fElement->m_addisotopes[ind]->m_natoms;
	totatoms += natoms;
    }

    return fElement->m_addisotopes[index]->m_natoms / ((double)totatoms);
}




