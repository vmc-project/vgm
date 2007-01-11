// $Id$
/// \ingroup VGM_materials
//
/// \class VGM::IElement
///
/// The VGM interface to elements.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ELEMENT_H
#define VGM_I_ELEMENT_H

#include <string>
#include <vector>
#include <iostream>

namespace VGM {
  class IIsotope;

  typedef std::vector<IIsotope*>  IsotopeVector;
  typedef std::vector<double>     RelAbundanceVector;

  class IElement
  {
    public:
      virtual ~IElement() {}
      
      // methods
			   ///
                           /// Return the name of this element
      virtual std::string Name() const = 0;
			   ///
                           /// Return the symbol of this element
      virtual std::string Symbol() const = 0;
		           ///
                           /// Return the effective atomic number
      virtual double  Z() const = 0;     
		           ///
                           /// Return the effective number of nucleons
      virtual double  N() const = 0;     
		           ///
                           /// Return the effective effective mass of a mole 
			   /// in g/mole
      virtual double  A() const = 0; 
			  ///
                          /// Return the number of isotopes constituing 
			  /// this element 
      virtual int     NofIsotopes() const = 0;
			  ///
                          /// Return the i-th isotope constituing this element
      virtual IIsotope*  Isotope(int i) const = 0;
			  ///
                          /// Return the relative abundance 
                          /// (the fraction of nb of atomes per volume)
                          /// of the i-th isotope constituing this material
      virtual double     RelAbundance(int i) const = 0 ;
  };       
} 

std::ostream& operator << (std::ostream& out, const VGM::IElement& element);

#endif //VGM_I_ELEMENT_H
