// $Id$
//
// Class ElementMap
// ------------------
// The map between VGM and Geant4 elements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/materials/ElementMap.h"

Geant4GM::ElementMap*  Geant4GM::ElementMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::ElementMap* 
Geant4GM::ElementMap::Instance()
{ 
// Singleton access function.
// ---

  if (!fgInstance) new ElementMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::ElementMap::ElementMap()
  : fG4Elements(),
    fVgmElements()
{
//  
  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::ElementMap::~ElementMap() 
{
//
  fgInstance = 0;
}    

//_____________________________________________________________________________
void  Geant4GM::ElementMap::AddElement(VGM::IElement* iElement, 
                                       G4Element* g4Element)
{
// Adds the specified pair in the map.
// ---

  fG4Elements[iElement] = g4Element;
  fVgmElements[g4Element] = iElement;
}  

//_____________________________________________________________________________
void  Geant4GM::ElementMap::Print() const
{
// Prints all elements in  the map.
// ---

  std::cout << "Geant4 Elements Map: " << std::endl; 

  int counter = 0;
  G4ElementMapCIterator i;
  for (i = fG4Elements.begin(); i != fG4Elements.end(); i++) {
    VGM::IElement* iElement = (*i).first;
    G4Element* element = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmElement " << iElement << " " << iElement->Name()
              << "  LV " << element << " " << element->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
G4Element* 
Geant4GM::ElementMap::GetElement(VGM::IElement* iElement) const
{
// Finds the G4 element corresponding to a specified VGM element.
// ---

  G4ElementMapCIterator i = fG4Elements.find(iElement);
  if (i != fG4Elements.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IElement* 
Geant4GM::ElementMap::GetElement(G4Element* element) const
{
// Finds the G4 element corresponding to a specified VGM element.
// ---

  VgmElementMapCIterator i = fVgmElements.find(element);
  if (i != fVgmElements.end()) 
    return (*i).second;
  else                 
    return 0;
}
