// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_UTILITIES_H
#define ROOT_GM_UTILITIES_H

#include "VGM/common/Axis.h"
#include "VGM/common/ThreeVector.h"
#include "VGM/common/Rotation.h"

class TGeoMatrix;
class TGeoPatternFinder;

namespace RootGM {

    // Root -> VGM
    //
    VGM::ThreeVector  Translation(const TGeoMatrix& matrix);
    VGM::Rotation     Rotation(const TGeoMatrix& matrix);
    bool              HasReflection(const TGeoMatrix& matrix);
    VGM::Axis         Axis(const TGeoPatternFinder* finder);
    
    // VGM -> Root
    //

    TGeoMatrix*   CreateTranslation(VGM::ThreeVector translation);
    TGeoMatrix*   CreateRotation(VGM::Rotation rotation);
    TGeoMatrix*   CreateTransform(VGM::Rotation rotation,
			          VGM::ThreeVector translation,
                                  bool hasReflection);
    int           Axis(VGM::Axis axis);
    double        AxisUnit(VGM::Axis axis);

    // Other functions

    bool IsDivided(const TGeoVolume* mother);
};

#endif //ROOT_GM_UTILITIES_H
