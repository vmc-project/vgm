// $Id$
//
// Class Units
// --------------
// Conversion of Root geometry units (fixed) into CLHEP system of units.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_UNITS_H
#define ROOT_GM_UNITS_H

#include "VGM/common/Axis.h"

namespace RootGM {

  class Units
  {
    public:
      // --> protected
      // Units();  
      virtual ~Units();
  
      // static get methods
      static double Length(); 
      static double Angle(); 
      static double AxisUnit(VGM::Axis axis); 
      static double MassDensity(); 
      static double AtomicWeight();     
      
    protected:
      Units();      
          // only static data members and methods

    private:
      // static data members  
      static const double fgkLength; 
      static const double fgkAngle;  
      static const double fgkMassDensity;
      static const double fgkAtomicWeight;
  }; 
  
}      

// inline methods

inline double RootGM::Units::Length()       { return fgkLength; }
inline double RootGM::Units::Angle()        { return fgkAngle; }
inline double RootGM::Units::MassDensity()  { return fgkMassDensity; }
inline double RootGM::Units::AtomicWeight() { return fgkAtomicWeight; }

#endif //ROOT_GM_UNITS_H
