// $Id$
//
// Class SolidMap
// ---------------
// The map between VGM and Root solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/SolidMap.h"

RootGM::SolidMap*  RootGM::SolidMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::SolidMap* 
RootGM::SolidMap::Instance()
{ 
// Singleton access function.
// ---

  if (!fgInstance) new RootGM::SolidMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
RootGM::SolidMap::SolidMap()
  : fRootSolids(),
    fVgmSolids()
{
//  
  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::SolidMap::SolidMap(const SolidMap&)
{
//
  fgInstance = 0;
}

//_____________________________________________________________________________
RootGM::SolidMap::~SolidMap() {
//
}    

//_____________________________________________________________________________
void  RootGM::SolidMap::AddSolid(VGM::ISolid* iSolid, 
                                 TGeoShape* rootSolid)
{
// Adds the specified pair in the map.
// ---

  fRootSolids[iSolid] = rootSolid;
  fVgmSolids[rootSolid] = iSolid;
}  

//_____________________________________________________________________________
TGeoShape* 
RootGM::SolidMap::GetSolid(VGM::ISolid* iSolid) const
{
// Finds the Root solid corresponding to a specified VGM solid.
// ---

  RootSolidMapCIterator i = fRootSolids.find(iSolid);
  if (i != fRootSolids.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::SolidMap::GetSolid(TGeoShape* rootSolid) const
{
// Finds the Root solid corresponding to a specified VGM solid.
// ---

  VgmSolidMapCIterator i = fVgmSolids.find(rootSolid);
  if (i != fVgmSolids.end()) 
    return (*i).second;
  else                 
    return 0;
}
