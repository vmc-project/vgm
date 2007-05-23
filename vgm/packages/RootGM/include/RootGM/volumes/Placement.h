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

#include <string>
#include <vector>

#include <TGeoMatrix.h>
#include <TGeoNode.h>

#include "VGM/common/Transform.h"

#include "BaseVGM/volumes/VPlacement.h"

class TGeoPatternFinder;

class VGM::IVolume;

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
      // data members
      std::string  fName;
      TGeoNode*    fGeoNode;
      std::vector<const TGeoNode*>  fAssemblyNodes;
  };

}

#endif //ROOT_GM_PLACEMENT_H
