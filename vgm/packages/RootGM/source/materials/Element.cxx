// $Id$
//
// Class Element
// ---------------
// VGM implementations for Root element.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <math.h>

#include "TGeoElement.h"
#include "TGeoManager.h"

#include "RootGM/materials/Element.h"
#include "RootGM/materials/Isotope.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Element::Element(const std::string& name, 
                         const std::string& symbol,      
                         double z, double a) 
  : VGM::IElement(),
    fName(name),
    fSymbol(symbol),
    fZ(z),
    fN(a),
    fA(a),    			       			  
    fIsotopes(),
    fRelAbundances()    			       			  
{
/// Standard constructor to define element from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol its symbol
/// \param z the effective atomic number
/// \param a the effective mass of a mole in g/mole 

}
			   
//_____________________________________________________________________________
RootGM::Element::Element(const std::string& name, 
                         const std::string& symbol,      
                         const VGM::IsotopeVector& isotopes,
                         const VGM::RelAbundanceVector& relAbundances) 
  : VGM::IElement(),
    fName(name),
    fSymbol(symbol),
    fZ(0),
    fN(0),
    fA(0),
    fIsotopes(),
    fRelAbundances()    			       			  
{
/// Standard constructor to define element from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol  its symbol
/// \param isotopes  the vector if isotopes
/// \param relAbundances  the vector of relative abundances of isotopes

  if ( ! isotopes.size() ) {
    std::cerr << "    RootGM::Element::Element: " << std::endl; 
    std::cerr << "    No isotopes defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (isotopes.size() != relAbundances.size()) {
    std::cerr << "    RootGM::Element::Element: " << std::endl; 
    std::cerr << "    Isotopes size and relAbundances size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  // Compute Neff, Aeff
  double wtSum = 0.;
  fN = 0;
  fA = 0;
  for ( unsigned int i=0; i<isotopes.size(); i++ ) {
    fIsotopes.push_back(isotopes[i]);
    fRelAbundances.push_back(relAbundances[i]);
    
    if (fZ == 0 ) fZ = isotopes[i]->Z();
    if (fZ != 0 && fZ != isotopes[i]->Z() ) {
      std::cerr << "    RootGM::Element::Element: " << std::endl; 
      std::cerr << "    Isotopes with different Z not allowed.";
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }  
    
    fN += relAbundances[i] * isotopes[i]->N();
    fA += relAbundances[i] * isotopes[i]->A();
    wtSum +=  relAbundances[i];
  }
  fN /=  wtSum;
  fA /=  wtSum;
}
			   
//_____________________________________________________________________________
RootGM::Element::Element(const Element& rhs) 
  : VGM::IElement(rhs), 
    fName(rhs.fName),
    fSymbol(rhs.fSymbol),
    fZ(rhs.fZ),
    fN(rhs.fN),
    fA(rhs.fA),    			       			  
    fIsotopes(rhs.fIsotopes),
    fRelAbundances(rhs.fRelAbundances)    			       			  
{
/// Copy constructor
}

//_____________________________________________________________________________
RootGM::Element::Element() 
  : VGM::IElement(), 
    fName("Undefined"),
    fSymbol("Undefined"),
    fZ(0),
    fN(0),
    fA(0),    			       			  
    fIsotopes(),
    fRelAbundances()    			       			  
{
/// Default constructor
}  

//_____________________________________________________________________________
RootGM::Element::~Element() {
//
}

//
// operators
//

//_____________________________________________________________________________
RootGM::Element& 
RootGM::Element::operator = (const Element& rhs) 
{
/// Assignment operator
 
  // check assignment to self
  if ( this == &rhs ) return *this;

  // assignment operator
  fName= rhs.fName;
  fSymbol = rhs.fSymbol;
  fZ = rhs.fZ;
  fA = rhs.fA;
  
  return *this; 
}  

//
// private functions
//

//_____________________________________________________________________________
void RootGM::Element::CheckIndex(int i) const
{
  if ( i < 0 || i >= NofIsotopes()) {  
    std::cerr << "    RootGM::Element::CheckIndex: " << std::endl;
    std::cerr << "    Index of isotope outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Element::Name() const
{
  return fName;
}  

//_____________________________________________________________________________
std::string RootGM::Element::Symbol() const
{
  return fSymbol;
}  

//_____________________________________________________________________________
double  RootGM::Element::Z() const    
{
  return fZ;
}

//_____________________________________________________________________________
double  RootGM::Element::N() const    
{
  return fN;
}

//_____________________________________________________________________________
double  RootGM::Element::A() const    
{
  return fA * RootGM::Units::AtomicWeight();
}

//_____________________________________________________________________________
int RootGM::Element::NofIsotopes() const 
{
  return fIsotopes.size();
}

//_____________________________________________________________________________
VGM::IIsotope*  RootGM::Element::Isotope(int i) const
{
  CheckIndex(i);

  return fIsotopes[i];
}  

//_____________________________________________________________________________
double  RootGM::Element::RelAbundance(int i) const 
{
  CheckIndex(i);

  return fRelAbundances[i];
}  

