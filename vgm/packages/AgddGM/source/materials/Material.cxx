// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <VGM/materials/IElement.h>
#include <AgddGM/materials/Material.h>

#include <AGDD/AGDD_Material_Model.hh>

#include <string>
using namespace std;

AgddGM::Material::Material(agdd::AGDD_Material* mat,
			   const VGM::ElementVector& eles)
    : fMat(mat), fElements(eles)
{
    double totmass = 0;

    size_t siz = eles.size();
    for (size_t ind = 0; ind<siz; ++ind) {
	const VGM::IElement* vgm_ele = eles[ind];
	double amass = vgm_ele->A();
	double natom = fMat->m_addelements[ind]->m_natoms;
	amass *= natom;
	fMassFrac.push_back(amass);
	totmass += amass;
    }
    for (size_t ifoo=0; ifoo<siz; ++ifoo) fMassFrac[ifoo] /= totmass;
}

std::string AgddGM::Material::Name() const
{
    return fMat->m_name;
}

double  AgddGM::Material::Density() const
{
    return fMat->m_density;
}
double  AgddGM::Material::RadiationLength() const
{
    return fMat->m_x0;
}
double  AgddGM::Material::NuclearInterLength() const
{
    return fMat->m_lambda;
}

VGM::MaterialState AgddGM::Material::State() const
{
    if (fMat->m_state == agdd::AGDD_Material::gas)
	return VGM::kGas;

    return VGM::kUndefined;
}

// No temp/pressure in AGDD.  What to do???
double  AgddGM::Material::Temperature() const{return 0;}
double  AgddGM::Material::Pressure() const{return 0;}

int AgddGM::Material::NofElements() const
{
    return fElements.size();
}

VGM::IElement* AgddGM::Material::Element(int iel) const
{
    return fElements[iel];
}
double  AgddGM::Material::MassFraction(int iel) const
{
    return fMassFrac[iel];
}

int AgddGM::Material::AtomCount(int iel) const
{
    // FIXME: implement
    return 0;
} 
