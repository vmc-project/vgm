// $Id$

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
/// \class AgddGM::MaterialFactory
///
/// VGM implementation of VMaterialFactory for AgddGM
///
/// \author: bv@bnl.gov


#ifndef AGDD_GM_MATERIALFACTORY_H
#define AGDD_GM_MATERIALFACTORY_H

#include "BaseVGM/materials/VMaterialFactory.h"

#include <vector>
#include <map>
#include <string>

namespace agdd {
    class AGDD_Materials;
}

namespace AgddGM {

class MaterialFactory : public BaseVGM::VMaterialFactory {
public:

    MaterialFactory();
    virtual ~MaterialFactory();

    /// Add materials to the factory
    void AddMaterials(agdd::AGDD_Materials* mat) { fMatVec.push_back(mat); }

    /// Import previsouly added materials
    bool Import();

    virtual VGM::IIsotope* CreateIsotope(const std::string& name,      
                                         int z, int n, double a = 0.);

    virtual VGM::IElement* CreateElement(const std::string& name,
                                         const std::string& symbol,
                                         double z, double a);
    virtual VGM::IElement* CreateElement(const std::string& name,      
                                         const std::string& symbol,      
                                         const VGM::IsotopeVector& isotopes,
                                         const VGM::RelAbundanceVector& relAbundances);
    virtual VGM::IElement* CreateElement(int z, bool isotopes = true);


    virtual VGM::IMaterial* CreateMaterial(const std::string& name,
					   double density,
					   VGM::IElement* element,
					   double radlen, double intlen);

    virtual VGM::IMaterial* CreateMaterial(const std::string& name,
					   double density,
					   VGM::IElement* element,
					   double radlen, double intlen,
					   VGM::MaterialState state,
					   double temperature, double pressure);

    virtual VGM::IMaterial* CreateMaterial(const std::string& name,
					   double density,
					   const VGM::ElementVector& elements,
					   const VGM::MassFractionVector& fractions);

    virtual VGM::IMaterial*  CreateMaterial(const std::string& name, 
                                            double density,
                                            const VGM::ElementVector& elements,
                                            const VGM::AtomCountVector& atomCounts);

    virtual VGM::IMaterial* CreateMaterial(const std::string& name,
					   double density,
					   const VGM::ElementVector& elements,
					   const VGM::MassFractionVector& fractions,
					   VGM::MaterialState state,
					   double temperature, double pressure);
    virtual VGM::IMaterial*  CreateMaterial(const std::string& name, 
                                            double density,
                                            const VGM::ElementVector& elements,
                                            const VGM::AtomCountVector& atomCounts,
                                            VGM::MaterialState state,
                                            double temperature, double pressure);

    virtual VGM::IMedium*   CreateMedium(const std::string& name,
					 int mediumId,
					 VGM::IMaterial* material,
					 int nofParameters,
					 double* parameters);



private:

    std::vector<agdd::AGDD_Materials*> fMatVec;
    std::map<std::string,VGM::IIsotope*> fIsoMap;
};

}
#endif  // AGDD_GM_MATERIALFACTORY_H
