// $Id: $

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include <AgddGM/solids/Polycone.h>
#include <AGDD/AGDD_Model.hh>
#include <CLHEP/Units/SystemOfUnits.h>

AgddGM::Polycone::Polycone(agdd::AGDD_Pcon* pcon)
    : fPcon(pcon)
{
    size_t siz = fPcon->NPolyplanes();

    fZ = new double[siz];
    fIr = new double[siz];
    fOr = new double[siz];

    for (size_t ind = 0; ind<siz; ++ind) {
	const agdd::AGDD_Polyplane* pp = fPcon->Polyplane(ind);
	const double* RioZ = pp->m_Rio_Z;
	fIr[ind] = RioZ[0] / CLHEP::mm;
	fOr[ind] = RioZ[1] / CLHEP::mm;
	fZ[ind] = RioZ[2] / CLHEP::mm;
    }
}

AgddGM::Polycone::~Polycone()
{
    delete [] fZ; fZ=0;
    delete [] fIr; fIr = 0;
    delete [] fOr; fOr = 0;
}

std::string AgddGM::Polycone::Name() const
{
    return fPcon->getName();
}

double  AgddGM::Polycone::StartPhi() const
{
    return fPcon->StartingAngle() / CLHEP::degree;
}
double  AgddGM::Polycone::DeltaPhi() const
{
    return fPcon->Angle() / CLHEP::degree;
}

int     AgddGM::Polycone::NofZPlanes() const
{
    return fPcon->NPolyplanes();
}
double* AgddGM::Polycone::ZValues() const
{
    return fZ;
}
double* AgddGM::Polycone::InnerRadiusValues() const
{
    return fIr;
}
double* AgddGM::Polycone::OuterRadiusValues() const
{
    return fOr;
}
