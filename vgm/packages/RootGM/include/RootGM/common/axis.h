// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_AXIS_H
#define ROOT_GM_AXIS_H

#include "VGM/common/Axis.h"

class TGeoMatrix;
class TGeoPatternFinder;

namespace RootGM {

    // Root -> VGM
    //
    VGM::Axis  Axis(const TGeoPatternFinder* finder);

    // VGM -> Root
    //
    int      Axis(VGM::Axis axis);
    double   AxisUnit(VGM::Axis axis);
}

#endif //ROOT_GM_AXIS_H
