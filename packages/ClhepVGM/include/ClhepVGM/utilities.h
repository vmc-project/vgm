// $Id$
//
// ClhepVGM utilities
// -------------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef CLHEP_VGM_UTILITIES_H
#define CLHEP_VGM_UTILITIES_H

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "VGM/common/ThreeVector.h"
#include "VGM/common/Rotation.h"

namespace ClhepVGM {

    // CLHEP -> VGM
    //
    VGM::ThreeVector  Translation(const Hep3Vector& translation);
    VGM::ThreeVector  Translation(const HepTransform3D& transform);
    VGM::ThreeVector  Origin();
    VGM::Rotation     Rotation(const HepRotation& rotation);
    VGM::Rotation     Rotation(const HepTransform3D& transform);
    VGM::Rotation     Identity();
    bool              HasReflection(const HepTransform3D& transform);
    
    // VGM -> CLHEP
    //

    Hep3Vector      Translation(VGM::ThreeVector translation);
    HepRotation     Rotation(VGM::Rotation rotation);

    HepTransform3D  Transform(VGM::Rotation rotation,
			      VGM::ThreeVector translation,
                              bool hasReflection);
};

#endif //CLHEP_VGM_UTILITIES_H
