// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::TessellatedSolid
///
/// VGM implementation for Geant4 tessellated solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TESSELLATED_SOLID_H
#define GEANT4_GM_TESSELLATED_SOLID_H

#include "BaseVGM/solids/VTessellatedSolid.h"
#include "VGM/common/ThreeVector.h"

#include "globals.hh"

#include <string>
#include <vector>

class G4TessellatedSolid;
class G4ReflectedSolid;
class G4VSolid;

namespace Geant4GM {

  class TessellatedSolid : public BaseVGM::VTessellatedSolid
  {
    public:
      TessellatedSolid(const std::string& name, 
                       std::vector< std::vector<VGM::ThreeVector> > facets);
      TessellatedSolid(G4TessellatedSolid* tessellated,
                       G4ReflectedSolid* reflTessellated = 0);
      virtual ~TessellatedSolid();

      // methods  
      virtual std::string      Name() const;
      virtual int              NofFacets() const;
      virtual int              NofVertices(int ifacet) const;
      virtual VGM::ThreeVector Vertex(int ifacet, int index) const;

    protected:
      TessellatedSolid();
      TessellatedSolid(const TessellatedSolid& rhs);
      
    private:   
      // methods
      void CheckFacetIndex(int ifacet) const;
      void CheckVertexIndex(int ifacet, int index) const;
      
      // data members
      G4String  fName;       
      G4bool    fIsReflected;
      G4TessellatedSolid*  fTessellatedSolid;
  };

}  

#endif //GEANT4_GM_TESSELLATED_SOLID_H
