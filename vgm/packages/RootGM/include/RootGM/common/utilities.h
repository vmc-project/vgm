// $Id$
//
// Utilities
// --------------
// Functions for conversion between Root and VGM basic elements
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_UTILITIES_H
#define ROOT_GM_UTILITIES_H

#include <string>

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "VGM/common/Axis.h"

class TGeoMatrix;
class TGeoVolume;
class TGeoPatternFinder;

namespace RootGM {

    // CLHEP -> Root conversion
    //
    TGeoMatrix*    Convert(HepRotation* rotation, 
                           const Hep3Vector& translation);
    TGeoMatrix*    Convert(const HepTransform3D& transformation);  

    // Root -> CLHEP conversion
    //
    HepTransform3D Convert(const TGeoMatrix* matrix);  
    Hep3Vector     GetTranslation(const TGeoMatrix* matrix);
    HepRotation    GetRotation(const TGeoMatrix* matrix);
    HepScale3D     GetScale(const TGeoMatrix* matrix);
    bool           HasReflection(const TGeoMatrix* matrix);

    int        GetAxis(VGM::Axis axis);
    double     GetAxisUnit(VGM::Axis axis);
    VGM::Axis  GetAxis(const TGeoPatternFinder* finder);

    bool IsDivided(const TGeoVolume* mother);
};

#endif //ROOT_GM_UTILITIES_H
