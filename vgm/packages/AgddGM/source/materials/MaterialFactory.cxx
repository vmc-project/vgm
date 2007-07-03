// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/materials/MaterialFactory.h>
#include <AgddGM/materials/Element.h>
#include <AgddGM/materials/Material.h>
#include <AGDD/AGDD_Material_Model.hh>
#include <cassert>
#include <string>
using namespace std;

AgddGM::MaterialFactory::MaterialFactory()
    : BaseVGM::VMaterialFactory("agdd")
{
}

AgddGM::MaterialFactory::~MaterialFactory()
{
}

bool AgddGM::MaterialFactory::Import()
{
    size_t nmats = fMatVec.size();
    
    for (size_t imat=0; imat<nmats; ++imat) {
        agdd::AGDD_Materials* mats = fMatVec[imat];


        {
            agdd::AGDD_Materials::ElementMap::iterator it,
                done= mats->m_elements.end();
            for (it=mats->m_elements.begin(); it!=done; ++it) {
                VGM::IElement* vgm_ele = new AgddGM::Element(it->second);
                ElementStore().push_back(vgm_ele);
            }
        }
        
        {
            agdd::AGDD_Materials::MaterialMap::iterator it,
                done = mats->m_materials.end();
            for (it=mats->m_materials.begin(); it != done; ++it) {

                VGM::ElementVector eles;
                agdd::AGDD_Material* mat = it->second;
                int siz = mat->m_addelements.size();

                for (int ind=0; ind<siz; ++ind) {

                    string name = mat->m_addelements[ind]->m_element->m_symbol;
                    // VGM::ElementVector doesn't take const pointers,
                    VGM::IElement* vgm_ele = // so we bust out ....
                        const_cast<VGM::IElement*>(Element(name));
                    eles.push_back(vgm_ele);

                    VGM::IMaterial* vgm_mat = new AgddGM::Material(mat,eles);
                    MaterialStore().push_back(vgm_mat);
                }
            }
        }
    } // loop over materials
    return true;
}

VGM::IIsotope* 
AgddGM::MaterialFactory::CreateIsotope(const std::string& name,
                                       int z, int n, double a )
{
    // FIXME
    assert(0); 
    return 0;
}



VGM::IElement*  
AgddGM::MaterialFactory::CreateElement(const std::string& name,
				       const std::string& symbol,
				       double z, double a)
{
    // FIXME
    assert(0); 
    return 0;
}

VGM::IElement* 
AgddGM::MaterialFactory::CreateElement(const std::string& name,      
                                       const std::string& symbol,      
                                       const VGM::IsotopeVector& isotopes,
                                       const VGM::RelAbundanceVector& relAbundances)
{
    // FIXME
    assert(0); 
    return 0;
}                                       

VGM::IElement* 
AgddGM::MaterialFactory::CreateElement(int z, bool isotopes)
{
    // FIXME
    assert(0); 
    return 0;
}                                       


VGM::IMaterial* 
AgddGM::MaterialFactory::CreateMaterial(const std::string& name,
					double density,
					VGM::IElement* element,
					double radlen, double intlen)
{
    // FIXME
    assert(0); 
    return 0;
}


VGM::IMaterial* 
AgddGM::MaterialFactory::CreateMaterial(const std::string& name,
					double density,
					VGM::IElement* element,
					double radlen, double intlen,
					VGM::MaterialState state,
					double temperature, double pressure)
{
    // FIXME
    assert(0); 
    return 0;
}

VGM::IMaterial* 
AgddGM::MaterialFactory::CreateMaterial(const std::string& name,
					double density,
					const VGM::ElementVector& elements,
					const VGM::MassFractionVector& fractions)
{
    // FIXME
    assert(0); 
    return 0;
}

VGM::IMaterial*  
AgddGM::MaterialFactory::CreateMaterial(const std::string& name, 
                                        double density,
                                        const VGM::ElementVector& elements,
                                        const VGM::AtomCountVector& atomCounts)
{
    // FIXME
    assert(0); 
    return 0;
}

VGM::IMaterial* 
AgddGM::MaterialFactory::CreateMaterial(const std::string& name,
					double density,
					const VGM::ElementVector& elements,
					const VGM::MassFractionVector& fractions,
					VGM::MaterialState state,
					double temperature, double pressure)
{
    // FIXME
    assert(0); 
    return 0;
}


VGM::IMaterial*  
AgddGM::MaterialFactory::CreateMaterial(const std::string& name, 
                                        double density,
                                        const VGM::ElementVector& elements,
                                        const VGM::AtomCountVector& atomCounts,
                                        VGM::MaterialState state,
                                        double temperature, double pressure)
{
    // FIXME
    assert(0); 
    return 0;
}

VGM::IMedium*   
AgddGM::MaterialFactory::CreateMedium(const std::string& name,
				      int mediumId,
				      VGM::IMaterial* material,
				      int nofParameters,
				      double* parameters)
{
    // FIXME
    assert(0); 
    return 0;
}


