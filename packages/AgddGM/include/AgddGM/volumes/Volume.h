// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_volumes
//
/// \class AgddGM::Volume
///
/// VGM implementation of VVolume for AgddGM
///
/// \author: bv@bnl.gov

#ifndef AGDD_GM_VOLUME_H
#define AGDD_GM_VOLUME_H

#include <BaseVGM/volumes/VVolume.h>

#include <string>
#include <map>

namespace agdd {
    class AGDD_Solid;
}

namespace AgddGM {
class Volume : public BaseVGM::VVolume {
public:
    Volume(VGM::ISolid* solid, agdd::AGDD_Solid* agdd_sol);
    virtual ~Volume();
    std::string   Name() const;
    std::string   MaterialName() const;
    std::string   MediumName() const;

    void SetName(std::string name);

    // this is used by Placements to assure correct copy number
    typedef std::map<std::string,int> DaughterNameCount;
    DaughterNameCount& NameCount() { return fNameCount; }

private:
    agdd::AGDD_Solid* fSol;
    std::string fName;

    DaughterNameCount fNameCount;
};
}
#endif  // AGDD_GM_VOLUME_H
