// $Id$
//
// Class ElementMap
// ------------------
// The map between VGM and Root elements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/ElementMap.h"

RootGM::ElementMap*  RootGM::ElementMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::ElementMap* 
RootGM::ElementMap::Instance()
{ 
/// Singleton access function.

  if (!fgInstance) new RootGM::ElementMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
RootGM::ElementMap::ElementMap()
  : fRootElements(),
    fVgmElements()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::ElementMap::ElementMap(const ElementMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::ElementMap::~ElementMap() 
{
//
  fgInstance = 0;
}    

//_____________________________________________________________________________
void  RootGM::ElementMap::AddElement(VGM::IElement* iElement, 
                                     TGeoElement* rtElement)
{
/// Add the specified pair in the map

  fRootElements[iElement] = rtElement;
  fVgmElements[rtElement] = iElement;
}  

//_____________________________________________________________________________
void  RootGM::ElementMap::Print() const
{
/// Print all elements in  the map

  std::cout << "Root Elements Map: " << std::endl; 

  int counter = 0;
  RootElementMapCIterator i;
  for (i = fRootElements.begin(); i != fRootElements.end(); i++) {
    VGM::IElement* iElement = (*i).first;
    TGeoElement* element = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmElement " << iElement << " " << iElement->Name()
              << "  LV " << element << " " << element->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
TGeoElement* 
RootGM::ElementMap::GetElement(VGM::IElement* iElement) const
{
/// Find the Root element corresponding to a specified VGM element

  RootElementMapCIterator i = fRootElements.find(iElement);
  if (i != fRootElements.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IElement* 
RootGM::ElementMap::GetElement(TGeoElement* element) const
{
/// Finds the VGM element corresponding to a specified Root element

  VgmElementMapCIterator i = fVgmElements.find(element);
  if (i != fVgmElements.end()) 
    return (*i).second;
  else                 
    return 0;
}
