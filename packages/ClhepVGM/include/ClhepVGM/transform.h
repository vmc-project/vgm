// $Id$

// -----------------------------------------------------------------------
// The ClhepVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup ClhepVGM
//
/// ClhepVGM utilities
///
/// Utility functions 
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef CLHEP_VGM_TRANSFORM_H
#define CLHEP_VGM_TRANSFORM_H

#include "VGM/common/Transform.h"

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

namespace ClhepVGM {

    // CLHEP -> VGM
    //
    VGM::Transform  Transform(const CLHEP::HepRotation& rotation,
                              const CLHEP::Hep3Vector& translation);
    VGM::Transform  Transform(const HepGeom::Transform3D& objectTransform);
    VGM::Transform  TransformScale(const HepGeom::Scale3D& scaleTransform);
    VGM::Transform  Identity();
    bool            HasReflection(const HepGeom::Transform3D& transform);
    
    // VGM -> CLHEP
    //
    CLHEP::Hep3Vector     Translation(const VGM::Transform& transform);
    CLHEP::HepRotation    Rotation(const VGM::Transform& transform);
    HepGeom::Scale3D      Scale(const VGM::Transform& transform);
    HepGeom::Transform3D  Transform(const VGM::Transform& transform);
    bool            HasReflection(const VGM::Transform& transform);

    // VGM
    //
    VGM::Transform  Inverse(const VGM::Transform& transform);

    // Utility function
    double Round(double x);
}

#endif //CLHEP_VGM_TRANSFORM_H
