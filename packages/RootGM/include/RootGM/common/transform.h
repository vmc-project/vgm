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

#include "TGeoMatrix.h"

class TGeoShape;

namespace RootGM {

    // Root -> VGM
    //
    VGM::Transform  Transform(const TGeoMatrix& matrix);
    VGM::Transform  TransformScale(const TGeoScale& scale);
    VGM::Transform  Identity();
    bool            HasReflection(const TGeoMatrix& matrix);

    // VGM -> Root
    TGeoMatrix*     CreateTransform(const VGM::Transform& transform);
    TGeoScale*      CreateScale(const VGM::Transform& transform);
    bool            HasReflection(const VGM::Transform& transform);

    // Root special
    TGeoHMatrix     Displacement(TGeoShape* shape);

    void  fromToRotation(double from[3], double to[3], double mtx[3][3]);
}

#endif //ROOT_GM_TRANSFORM_H
