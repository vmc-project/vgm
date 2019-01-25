// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_common
//
/// \class VGM::TwoVector
///
/// VGM typedef for 2D vector
/// represented by std::pair<double, double>:
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_TWO_VECTOR_H
#define VGM_TWO_VECTOR_H

#include <utility>

namespace VGM {

  typedef std::pair<double, double>  TwoVector;

}

#endif //VGM_TWO_VECTOR_H
