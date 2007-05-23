// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_materials
//
/// \class VGM::IMaterial
///
/// The VGM interface to materials.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MATERIAL_H
#define VGM_I_MATERIAL_H

#include <string>
#include <iostream>
#include <vector>

namespace VGM {

  class IElement;

  typedef std::vector<IElement*>  ElementVector;
  typedef std::vector<double>     MassFractionVector;
  typedef std::vector<int>        AtomCountVector;

  enum MaterialState {
    kUndefined, ///< Undefined material state
    kSolid,	///< Solid material 
    kLiquid,	///< Liquid material
    kGas 	///< Gas materila
  };	   

  class IMaterial
  {
    public:
      virtual ~IMaterial() {}
      
      // methods
			  ///
                          /// Return the name of this element
      virtual std::string Name() const = 0;
			  ///
                          /// Return the density in g/cm3
      virtual double  Density() const = 0;
			  ///
                          /// Return the radiation length in mm
      virtual double  RadiationLength() const = 0;
			  ///
                          /// Return the nuclear interaction length in mm 
      virtual double  NuclearInterLength() const = 0;
                          ///
			  /// Return the material state
      virtual MaterialState  State() const = 0;
                          /// 
			  /// Return the temperature in kelvins
      virtual double  Temperature() const = 0;
                          ///
			  /// Return the density in atmosphere
      virtual double  Pressure() const = 0;			  
			  ///
                          /// Return the number of elements constituing 
			  /// this material 
      virtual int     NofElements() const = 0;
			  ///
                          /// Return the i-th element constituing this material
      virtual IElement*  Element(int iel) const = 0;
			  ///
                          /// Return the mass fraction of the i-th element 
			  /// constituing this material
      virtual double     MassFraction(int iel) const = 0 ;
			  ///
                          /// Return the atom count of the i-th element 
			  /// constituing this material
      virtual int        AtomCount(int iel) const = 0 ;
  };
}  

std::ostream& operator << (std::ostream& out, const VGM::IMaterial& material);

#endif //VGM_I_MATERIAL_H
