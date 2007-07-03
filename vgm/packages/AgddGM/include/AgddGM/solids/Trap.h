// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#ifndef AGDD_GM_TRAP_H
#define AGDD_GM_TRAP_H

#include <BaseVGM/solids/VTrap.h>

namespace agdd { class AGDD_GeneralTrapezoid; }


namespace AgddGM {

class Trap : public BaseVGM::VTrap {
public:
    Trap(agdd::AGDD_GeneralTrapezoid* trap);
    virtual ~Trap() {}

    std::string Name() const;
    double ZHalfLength() const;
    double Theta() const;
    double Phi() const;
    double YHalfLengthMinusZ() const;
    double XHalfLengthMinusZMinusY() const;
    double XHalfLengthMinusZPlusY() const;
    double AlphaMinusZ() const;
    double YHalfLengthPlusZ() const;
    double XHalfLengthPlusZMinusY() const;
    double XHalfLengthPlusZPlusY() const;
    double AlphaPlusZ() const;
    
private:
    agdd::AGDD_GeneralTrapezoid* fTrap;

};
}


#endif  // AGDD_GM_TRD_H
