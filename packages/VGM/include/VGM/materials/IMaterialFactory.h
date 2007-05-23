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
/// \class VGM::IMaterialFactory
///
/// The VGM interface to material factory providing
/// functions for material conversions.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MATERIAL_FACTORY_H
#define VGM_I_MATERIAL_FACTORY_H

#include <vector>

#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"

namespace VGM {

  class IIsotope;
  class IElement;
  class IMedium;

  typedef std::vector<IIsotope*>  IsotopeStore;
  typedef std::vector<IElement*>  ElementStore;
  typedef std::vector<IMaterial*> MaterialStore;
  typedef std::vector<IMedium*>   MediumStore;

  class IMaterialFactory
  {
    public:
      virtual ~IMaterialFactory() {}
    
      //
      // methods
      //
                          /// Create a chemical isotope
		          /// \param name its name
			  ///        (must be unique in the factory)
		          /// \param z the atomic number
		          /// \param n the number of nucleons
		          /// \param a the mass of a mole in g/mole (optional)
			  /// 
      virtual IIsotope*   CreateIsotope(
                                 const std::string& name,      
                                 int z, int n, double a = 0.) = 0;

                          /// Create a chemical element
		          /// \param name its name
			  ///        (must be unique in the factory)
		          /// \param symbol its symbol
		          /// \param z the effective atomic number
		          /// \param a the effective mass of a mole in g/mole 
			  /// 
      virtual IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
                                 double z, double a) = 0;

                          /// Create a chemical element
		          /// \param name its name
			  ///        (must be unique in the factory)
		          /// \param symbol its symbol
		          /// \param isotopes vector of isotopes constituting this
                          ///        element
		          /// \param relAbundances vector of relative abundances
                          ///        of isotopes 
			  /// 
      virtual IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
	                         const VGM::IsotopeVector& isotopes,
                                 const VGM::RelAbundanceVector& relAbundances) = 0;
                                 
                          /// Create a chemical element
		          /// \param z the effective atomic number
		          /// \param isotopes if true, build element from isotopes
                          ///
      virtual IElement*   CreateElement(
                                 int z, bool isotopes = true) = 0;

                          /// Create a material
		          /// \param name its name 
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param element element constituing this material
			  /// \param radlen radiation length in mm
			  /// \param intlen nuclear interaction length in mm
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
	  		         double density, 
			         VGM::IElement* element,     
			         double radlen, double intlen) = 0;

                          /// Create a compound material
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param element element constituing this material
			  /// \param radlen radiation length in mm			  
			  /// \param intlen nuclear interaction length in mm
			  /// \param state material state
			  /// \param temperature temperature in kelvin
			  /// \param pressure pressure in atmosphere 
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
	  		         double density, 
			         VGM::IElement* element,     
			         double radlen, double intlen,
				 VGM::MaterialState state,
				 double temperature, double pressure) = 0;

                          /// Create a compound material
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param elements vector of elements constituing 
			  ///        this material
			  /// \param fractions vector of mass fractions of
			  ///        elements constituing this material
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions) = 0;

                          /// Create a compound material
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param elements vector of elements constituing 
			  ///        this material
			  /// \param fractions vector of mass fractions of
			  ///        elements constituing this material
			  /// \param state material state
			  /// \param temperature temperature in kelvin
			  /// \param pressure pressure in atmosphere 
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions,
				 VGM::MaterialState state,
				 double temperature, double pressure) = 0;

                          /// Create a compound material
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param elements vector of elements constituing 
			  ///        this material
			  /// \param atomCounts vector of atom counts of
			  ///        elements constituing this material
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts) = 0;

                          /// Create a compound material
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param density in g/cm3
			  /// \param elements vector of elements constituing 
			  ///        this material
			  /// \param atomCounts vector of atom counts of
			  ///        elements constituing this material
			  /// \param state material state
			  /// \param temperature temperature in kelvin
			  /// \param pressure pressure in atmosphere 
			  ///
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts,
				 VGM::MaterialState state,
				 double temperature, double pressure) = 0;

                          /// Create a tracking medium
		          /// \param name its name
			  ///        (must be unique in the factory)
			  /// \param mediumId its unique identifier
			  /// \param material associated material
			  /// \param nofParameters number of defined parameters
			  /// \param parameters array of parameters
			  ///
      virtual IMedium*    CreateMedium(
                                 const std::string& name,
                                 int mediumId,
			         VGM::IMaterial* material,
			         int nofParameters,
			         double* parameters) = 0;      
    
      //
      // access 
      // 
	                              ///
                                      /// Return the name of this factory
      virtual std::string Name() const = 0;
	                             ///
                                     /// Return the store of isotopes
      virtual const IsotopeStore&   Isotopes() const = 0;	
	                             ///
                                     /// Return the store of elements
      virtual const ElementStore&   Elements() const = 0;	
	                             ///
                                     /// Return the store of materials
      virtual const MaterialStore&  Materials() const = 0;	
	                             ///
                                     /// Return the store of media
      virtual const MediumStore&    Media() const = 0;	

	                            ///
                                    /// Return isotope specified by name
      virtual const IIsotope*  Isotope(const std::string& name) const = 0;	
	                            ///
                                    /// Return element specified by name
      virtual const IElement*  Element(const std::string& name) const = 0;	
	                            ///
                                    /// Return material specified by name
      virtual const IMaterial* Material(const std::string& name) const = 0;	
	                            ///
                                    /// Return medium specified by name
      virtual const IMedium*   Medium(const std::string& name) const = 0;	

      //
      // import/export
      //
                     ///
                     /// Import native materials
      virtual bool Import() = 0;			       
                     ///
                     /// Export materials to the specified material factory
     virtual bool  Export(IMaterialFactory* factory) const = 0;			       

      //
      // listings
      //
	             ///
                     /// Print all isotopes
      virtual void PrintIsotopes() const = 0;			       
	             ///
                     /// Print all elements
      virtual void PrintElements() const = 0;			       
	             ///
                     /// Print all materials
      virtual void PrintMaterials() const = 0;			       
	             ///
                     /// Print all media
      virtual void PrintMedia() const = 0;			       

      //
      // debug
      //
	             ///
                     /// Set the debug level
      virtual void SetDebug (int debug) = 0;			       
	             ///
                     /// Return the debug level
      virtual int  Debug() const = 0;
  };
}  

#endif //VGM_I_MATERIAL_FACTORY_H
