// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2010 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class ElementMap
// ------------------
// The map between VGM and Root elements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IElement.h"

#include "RootGM/materials/ElementMap.h"

#include "TGeoElement.h"

RootGM::ElementMap* RootGM::ElementMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::ElementMap* RootGM::ElementMap::Instance()
{
  /// Singleton access function.

  if (!fgInstance) new ElementMap();

  return fgInstance;
}

//_____________________________________________________________________________
RootGM::ElementMap::ElementMap() : fTGeoElements(), fVgmElements()
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

//
// public methods
//

//_____________________________________________________________________________
void RootGM::ElementMap::AddElement(
  VGM::IElement* iElement, TGeoElement* tgeoElement)
{
  /// Add the specified pair in the map

  fTGeoElements[iElement] = tgeoElement;
  fVgmElements[tgeoElement] = iElement;
}

//_____________________________________________________________________________
void RootGM::ElementMap::Print() const
{
  /// Print all elements in the map

  std::cout << "Geant4 Elements Map: " << std::endl;

  int counter = 0;
  TGeoElementMapCIterator i;
  for (i = fTGeoElements.begin(); i != fTGeoElements.end(); i++) {
    VGM::IElement* iElement = (*i).first;
    TGeoElement* element = (*i).second;

    std::cout << "   " << counter++ << "th entry:"
              << "  vgmElement " << iElement << " " << iElement->Name()
              << "  LV " << element << " " << element->GetName() << std::endl;
  }
}

//_____________________________________________________________________________
TGeoElement* RootGM::ElementMap::GetElement(VGM::IElement* iElement) const
{
  /// Find the Root element corresponding to a specified VGM element

  TGeoElementMapCIterator i = fTGeoElements.find(iElement);
  if (i != fTGeoElements.end())
    return (*i).second;
  else
    return 0;
}

//_____________________________________________________________________________
VGM::IElement* RootGM::ElementMap::GetElement(TGeoElement* element) const
{
  /// Find the VGM element corresponding to a specified Root element

  VgmElementMapCIterator i = fVgmElements.find(element);
  if (i != fVgmElements.end())
    return (*i).second;
  else
    return 0;
}
