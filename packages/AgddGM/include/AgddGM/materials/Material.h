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
/// \class AgddGM::Material
///
/// VGM implementation of IMaterial for AgddGM.
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_MATERIAL_H
#define AGDD_GM_MATERIAL_H

#include "VGM/materials/IMaterial.h"

#include <string>

namespace agdd {
    class AGDD_Material;
}

namespace AgddGM {

class MaterialFactory;

class Material : public VGM::IMaterial {

public:

    Material(agdd::AGDD_Material* mat,
	     const VGM::ElementVector& eles);

    virtual ~Material() {}

    std::string Name() const;

    double  Density() const;
    double  RadiationLength() const;
    double  NuclearInterLength() const;
    VGM::MaterialState  State() const;
    double  Temperature() const;
    double  Pressure() const;

    int     NofElements() const;
    VGM::IElement*  Element(int iel) const;
    double  MassFraction(int iel) const;
    double  AtomCount(int iel) const;

private:

    agdd::AGDD_Material* fMat;
    VGM::ElementVector fElements;
    VGM::MassFractionVector fMassFrac;
};

}


#endif  // AGDD_GM_MATERIAL_H
