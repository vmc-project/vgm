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
/// \class ClhepVGM::Units
///
/// Conversion from CLHEP physical units to VGM units.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef CLHEP_VGM_UNITS_H
#define CLHEP_VGM_UNITS_H

#include "VGM/common/Axis.h"

namespace ClhepVGM {

  class Units
  {
    public:
      // --> protected
      // Units();
      virtual ~Units();

                    /// Return CLHEP default length unit in VGM units
		    ///
      static double Length();

                    /// Convert CLHEP length unit in VGM units
		    ///
      static double Length(double clhepUnit);

                    /// Return CLHEP default angle unit in VGM units
		    ///
      static double Angle();

                    /// Convert CLHEP angle unit in VGM units
		    ///
      static double Angle(double clhepUnit);

                    /// Return CLHEP default mass density unit in VGM units
		    ///
      static double MassDensity();

                    /// Convert CLHEP mass density unit in VGM units
		    ///
      static double MassDensity(double clhepUnit);

                    /// Return CLHEP default atomic weight unit in VGM units
		    ///
      static double AtomicWeight();

                    /// Convert CLHEP  atomic weight  unit in VGM units
		    ///
      static double AtomicWeight(double clhepUnit);

                    /// Return CLHEP default temperature unit in VGM unit
		    ///
      static double Temperature();

                    /// Convert CLHEP temperature unit in VGM unit
		    ///
      static double Temperature(double clhepUnit);

                    /// Return CLHEP default pressure unit in VGM unit
		    ///
      static double Pressure();

                    /// Convert CLHEP temperature unit in VGM unit
		    ///
      static double Pressure(double clhepUnit);

                    /// Convert CLHEP  default unit for given axis type
		    /// in VGM units
		    ///
      static double AxisUnit(VGM::Axis axis);

    protected:
      Units();
          // only static data members and methods

    private:
      // static data members
      static const double fgkLength;
      static const double fgkAngle;
      static const double fgkMassDensity;
      static const double fgkAtomicWeight;
      static const double fgkTemperature;
      static const double fgkPressure;
  };

}

#endif //CLHEP_VGM_UNITS_H
