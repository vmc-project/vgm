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
/// \class Geant4GM:: ExtrudedSolid
///
/// VGM implementation for Geant4 xtru solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_EXTRUDED_SOLID_H
#define GEANT4_GM_EXTRUDED_SOLID_H

#include "BaseVGM/solids/VExtrudedSolid.h"

#include "globals.hh"

#include <string>
#include <vector>

class G4ExtrudedSolid;
class G4ReflectedSolid;
class G4VSolid;

namespace Geant4GM {

  class ExtrudedSolid : public BaseVGM::VExtrudedSolid
  {
    public:
      ExtrudedSolid(const std::string& name, 
                    std::vector<VGM::TwoVector> polygon,
                    std::vector< std::vector<double> > zsections);
      ExtrudedSolid(G4ExtrudedSolid* xtru,
                    G4ReflectedSolid* reflXtru = 0);
      virtual ~ExtrudedSolid();

      // methods
      virtual std::string     Name() const;
      inline  int             NofVertices() const;
      inline  VGM::TwoVector  Vertex(int index) const;
      virtual int             NofZSections() const;
      virtual double          ZPosition(int iz) const;
      virtual VGM::TwoVector  Offset(int iz) const;
      virtual double          Scale(int iz) const;

    protected:
      ExtrudedSolid();
      ExtrudedSolid(const ExtrudedSolid& rhs);
      
    private:   
      // types
      typedef std::vector<double>  ZSectionType;
     
      // methods
      void CreateFinalSolid();
      
      // data members
      G4String   fName;       
      G4VSolid*  fExtrudedSolid;
      std::vector<ZSectionType>     fZSections;
      std::vector<G4ExtrudedSolid*> fConstituents;
  };

}  

#endif //GEANT4_GM_EXTRUDED_SOLID_H
