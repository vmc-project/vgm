// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_common
//
/// RootGM transformations
///
/// Utility functions for conversions between Root and VGM
/// transformtaions.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_TRANSFORM_H
#define ROOT_GM_TRANSFORM_H

#include "VGM/common/Transform.h"

class TGeoMatrix;
class TGeoPatternFinder;

namespace RootGM {

    // Root -> VGM
    //
    VGM::Transform  Transform(const TGeoMatrix& matrix);
    VGM::Transform  Identity();
    bool            HasReflection(const TGeoMatrix& matrix);
    
    // VGM -> Root
    TGeoMatrix*     CreateTransform(const VGM::Transform& transform);
    bool            HasReflection(const VGM::Transform& transform);
}

#endif //ROOT_GM_TRANSFORM_H
