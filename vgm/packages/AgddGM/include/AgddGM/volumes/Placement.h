// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#ifndef AGDD_GM_PLACEMENT_H
#define AGDD_GM_PLACEMENT_H

#include <BaseVGM/volumes/VPlacement.h>

#include <string>

namespace HepGeom { class Transform3D; }
namespace AgddGM {

class Volume;

class Placement : public BaseVGM::VPlacement {
public:
    Placement(const std::string& name, 
	      AgddGM::Volume* volume, AgddGM::Volume* parent,
	      const HepGeom::Transform3D& transform);

    virtual ~Placement() {}

    VGM::PlacementType Type() const;
    std::string        Name() const;
    int                CopyNo() const;
    VGM::Transform     Transformation() const;
    bool  MultiplePlacementData(VGM::Axis&  axis,
				int&     nofDivisions,
				double&  width,
				double&  offset) const;
private:
    std::string fName;
    int fCopyNo;
    VGM::Transform fTrans;
};

}

#endif  // AGDD_GM_PLACEMENT_H
