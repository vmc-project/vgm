// $Id$
//
// ClhepVGM utilities
// -------------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef CLHEP_VGM_TRANSFORM_H
#define CLHEP_VGM_TRANSFORM_H

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "VGM/common/Transform.h"

namespace ClhepVGM {

    // CLHEP -> VGM
    //
    VGM::Transform    Transform(const HepRotation& rotation,
                                const Hep3Vector& translation);
    VGM::Transform    Transform(const HepTransform3D& objectTransform);
    VGM::Transform    Identity();
    bool              HasReflection(const HepTransform3D& transform);
    
    // VGM -> CLHEP
    //
    Hep3Vector      Translation(const VGM::Transform& transform);
    HepRotation     Rotation(const VGM::Transform& transform);
    HepTransform3D  Transform(const VGM::Transform& transform);
    bool            HasReflection(const VGM::Transform& transform);

    // VGM
    //
    VGM::Transform  Inverse(const VGM::Transform& transform);
};

#endif //CLHEP_VGM_TRANSFORM_H
