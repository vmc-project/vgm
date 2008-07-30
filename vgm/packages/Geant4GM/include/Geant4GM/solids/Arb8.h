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
/// \class Geant4GM::Arb8
///
/// VGM implementation for Geant4 Arb8 solid,
/// the shape is implemented using G4TessellatedSolid.
/// The twisted shape is not supported. 
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ARB8_SOLID_H
#define GEANT4_GM_ARB8_SOLID_H

#include "BaseVGM/solids/VArb8.h"

#include "VGM/common/TwoVector.h"

#include "globals.hh"
#include "G4ThreeVector.hh"

#include <string>
#include <vector>

class G4TessellatedSolid;
class G4VFacet;

namespace Geant4GM {

  class Arb8 : public BaseVGM::VArb8
  {
    public:
      Arb8(const std::string& name, 
           double hz, 
           std::vector<VGM::TwoVector> vertices);
      virtual ~Arb8();
   
      // static methods
      static bool IsTwisted(std::vector<VGM::TwoVector> vertices);

      // methods
      virtual std::string     Name() const;
      virtual int             NofVertices() const;
      inline  VGM::TwoVector  Vertex(int index) const;
      virtual double          ZHalfLength() const;

    protected:
      Arb8();
      Arb8(const Arb8& rhs);
      
    private:   
      // methods
      G4VFacet* MakeDownFacet(std::vector<G4ThreeVector> fromVertices, 
                              int ind1, int ind2, int ind3) const;
      G4VFacet* MakeUpFacet(std::vector<G4ThreeVector> fromVertices, 
                              int ind1, int ind2, int ind3) const;      
      G4VFacet* MakeSideFacet(G4ThreeVector downVertex0, 
                              G4ThreeVector downVertex1,
                              G4ThreeVector upVertex1,
                              G4ThreeVector upVertex0) const;
                                    
      // static data members
      static const int    fgkNofVertices;
      static const double fgkTolerance;

      // data members
      double                      fHz;
      std::vector<VGM::TwoVector> fVertices;
      G4TessellatedSolid*         fTessellatedSolid;
  };

}  

#endif //GEANT4_GM_EXTRUDED_SOLID_H
