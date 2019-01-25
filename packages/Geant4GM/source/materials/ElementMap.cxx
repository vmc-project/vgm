// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class ElementMap
// ------------------
// The map between VGM and Geant4 elements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IElement.h"

#include "Geant4GM/materials/ElementMap.h"

#include "G4Element.hh"

Geant4GM::ElementMap*  Geant4GM::ElementMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::ElementMap*
Geant4GM::ElementMap::Instance()
{
/// Singleton access function.

  if (!fgInstance) new ElementMap();

  return fgInstance;
}

//_____________________________________________________________________________
Geant4GM::ElementMap::ElementMap()
  : fG4Elements(),
    fVgmElements()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::ElementMap::ElementMap(const ElementMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::ElementMap::~ElementMap()
{
//
  fgInstance = 0;
}


//
// public methods
//

//_____________________________________________________________________________
void  Geant4GM::ElementMap::AddElement(VGM::IElement* iElement,
                                       G4Element* g4Element)
{
/// Add the specified pair in the map

  fG4Elements[iElement] = g4Element;
  fVgmElements[g4Element] = iElement;
}

//_____________________________________________________________________________
void  Geant4GM::ElementMap::Print() const
{
/// Prints all elements in the map

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
/// Find the G4 element corresponding to a specified VGM element

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
/// Find the VGM element corresponding to a specified G4 element

  VgmElementMapCIterator i = fVgmElements.find(element);
  if (i != fVgmElements.end())
    return (*i).second;
  else
    return 0;
}
