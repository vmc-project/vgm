// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_UTILITIES_H
#define BASE_VGM_UTILITIES_H


#include "VGM/common/Rotation.h"
#include "VGM/common/ThreeVector.h"


namespace BaseVGM {

    VGM::ThreeVector  Origin();
    VGM::Rotation     Identity();

    // Debug printing 
    void  DebugInfo();
};

#endif //BASE_VGM_UTILITIES_H
