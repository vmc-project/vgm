// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_UTILITIES_H
#define BASE_VGM_UTILITIES_H

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

namespace BaseVGM {

    // CLHEP utilities
    Hep3Vector     GetTranslation(const HepTransform3D& transform);
    HepRotation    GetRotation(const HepTransform3D& transform);
    HepScale3D     GetScale(const HepTransform3D& transform);
    bool           HasReflection(const HepTransform3D& transform);
    bool           HasReflection(const HepScale3D& scale);
    
    // Debug printing 
    void  DebugInfo();
};

#endif //BASE_VGM_UTILITIES_H
