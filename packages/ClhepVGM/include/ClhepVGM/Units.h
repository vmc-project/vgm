// $Id$
//
// Class Units
// --------------
// Conversion from CLHEP physical units to VGM units..
//
// Author: Ivana Hrivnacova; IPN Orsay

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
  
      // static get methods
      static double Length(); 
      static double Length(double clhepUnit); 

      static double Angle(); 
      static double Angle(double clhepUnit); 

      static double MassDensity(); 
      static double MassDensity(double clhepUnit); 

      static double AtomicWeight();     
      static double AtomicWeight(double clhepUnit);     
      
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
  }; 
  
}      

// inline methods

inline double ClhepVGM::Units::Length()       
{ return fgkLength; }

inline double ClhepVGM::Units::Length(double clhepUnit)       
{ return fgkLength * clhepUnit; }

inline double ClhepVGM::Units::Angle()        
{ return fgkAngle; }

inline double ClhepVGM::Units::Angle(double clhepUnit)        
{ return fgkAngle * clhepUnit; }

inline double ClhepVGM::Units::MassDensity()  
{ return fgkMassDensity; }

inline double ClhepVGM::Units::MassDensity(double clhepUnit)  
{ return fgkMassDensity * clhepUnit; }

inline double ClhepVGM::Units::AtomicWeight() 
{ return fgkAtomicWeight; }

inline double ClhepVGM::Units::AtomicWeight(double clhepUnit) 
{ return fgkAtomicWeight * clhepUnit; }

#endif //CLHEP_VGM_UNITS_H
