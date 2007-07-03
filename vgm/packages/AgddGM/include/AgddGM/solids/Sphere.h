// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#ifndef AGDD_GM_SPHERE_H
#define AGDD_GM_SPHERE_H

#include <BaseVGM/solids/VSphere.h>

#include <string>

namespace agdd { class AGDD_Sphere; }

namespace AgddGM {
class Sphere : public BaseVGM::VSphere
{
public:
    Sphere(agdd::AGDD_Sphere* sphere);
    virtual ~Sphere() {}

    std::string Name() const;
    double InnerRadius() const;
    double OuterRadius() const;
    double StartPhi() const;
    double DeltaPhi() const;
    double StartTheta() const;
    double DeltaTheta() const;


private:
    agdd::AGDD_Sphere* fSphere;
};

}

#endif  // AGDD_GM_SPHERE_H
