// $Id$
//
// Taken from Geant4 (G3toG4RotationMatrix) 
// ------------------------------------------
// Class description:
//
// An "extended" rotation matrix class.
// The SetRotationMatrixByCol/Row() methods enables
// to define the rotation matrix by column/row vectors.
// The result matrix may be a matrix that does not
// represent a rotation transformation (!) as
// G3 "rotation" matrices can be a composition of
// rotation and reflection.  

// --------------------------------------------

#ifndef ROOT_GM_ROTATION_MATRIX_H
#define ROOT_GM_ROTATION_MATRIX_H

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace RootGM {

  class RotationMatrix : public HepRotation
  {

  public:  // with description

    RotationMatrix();

    void SetRotationMatrixByCol(const Hep3Vector& Col1,
                              const Hep3Vector& Col2,
                              const Hep3Vector& Col3);
    
    void SetRotationMatrixByRow(const Hep3Vector& Row1,
                              const Hep3Vector& Row2,
                              const Hep3Vector& Row3);
    
    ~RotationMatrix();

  };

}

#endif    
