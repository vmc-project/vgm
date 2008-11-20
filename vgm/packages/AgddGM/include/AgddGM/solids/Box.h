// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_solids
//
/// \class AgddGM::Box
///
/// VGM implementation of VBox for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_BOX_H
#define AGDD_GM_BOX_H

#include "BaseVGM/solids/VBox.h"

#include <string>

namespace agdd { 
  class AGDD_Box; 
}

namespace AgddGM {

class Box : public BaseVGM::VBox
{
public:
    Box(agdd::AGDD_Box* box);
    virtual ~Box() {}

    std::string Name() const;
    double XHalfLength() const;
    double YHalfLength() const;
    double ZHalfLength() const;


private:
    agdd::AGDD_Box* fBox;
};

}

#endif  // AGDD_GM_BOX_H
