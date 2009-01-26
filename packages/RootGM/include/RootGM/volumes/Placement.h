// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_volumes
//
/// \class RootGM:: Placement
///
/// VGM implementation for Root positions of volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PLACEMENT_H
#define ROOT_GM_PLACEMENT_H

#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

#include <string>
#include <vector>

class TGeoPatternFinder;
class TGeoMatrix;
class TGeoNode;


namespace VGM {
  class IVolume;
}

namespace RootGM {

  class Placement : public BaseVGM::VPlacement
  {
    public:
      Placement(
         const std::string& name, 
	 int copyNo,
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
	 TGeoMatrix* transformation);
      Placement(
         const std::string& name, 
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
         VGM::Axis axis, int nofItems, double  width, double offset);
      Placement(
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
         TGeoNode* node);
      Placement(
         VGM::IVolume* volume, VGM::IVolume* motherVolume,
         TGeoNode* node, std::vector<const TGeoNode*> assemblyNodes);
      virtual ~Placement();
    
      // static methods
      static void SetIncludeAssembliesInNames(bool includeAssembliesInNames);
      static bool GetIncludeAssembliesInNames();

      static void SetNameSeparator(char nameSeparator);
      static char GetNameSeparator();

      // methods
      virtual VGM::PlacementType Type() const;
      virtual std::string        Name() const;
      virtual int                CopyNo() const;
      virtual VGM::Transform     Transformation() const;      

      virtual bool  MultiplePlacementData(
                                VGM::Axis&  axis,
                                int&     nofItems,
                                double&  width,
                                double&  offset) const;

    protected:
      Placement();
      Placement(const Placement& rhs);

    private:
      // static data members
      static bool fgIncludeAssembliesInNames; 
      static char fgNameSeparator; 
    
      // data members
      std::string  fName;
      TGeoNode*    fGeoNode;
      std::vector<const TGeoNode*>  fAssemblyNodes;
  };

}

#endif //ROOT_GM_PLACEMENT_H
