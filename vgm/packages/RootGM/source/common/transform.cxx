// $Id$
//
// RootGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>
#include <float.h>
#include <math.h>

#include <TGeoMatrix.h>
#include <TGeoPatternFinder.h>
#include <TMath.h>

#include "RootGM/common/transform.h"
#include "RootGM/common/Units.h"

//
// Root -> VGM
//

//_____________________________________________________________________________
VGM::Transform  RootGM::Transform(const TGeoMatrix& matrix)
{
//
  // Translation
  //
  const Double_t* translation = matrix.GetTranslation();

  VGM::Transform transform(VGM::kSize);
  transform[0] = translation[VGM::kDx] * Units::Length();
  transform[1] = translation[VGM::kDy] * Units::Length();
  transform[2] = translation[VGM::kDz] * Units::Length();

  // Rotation 
  //
  const Double_t* rm = matrix.GetRotationMatrix();

  double xx, xy, xz,     // 3x3  Rotation Matrix
         yx, yy, yz,
         zx, zy, zz;

  xx = rm[0]; xy = rm[1]; xz = rm[2];
  yx = rm[3]; yy = rm[4]; yz = rm[5];
  zx = rm[6]; zy = rm[7]; zz = rm[8];

  // Decompose reflectionZ from rotation matrix 

  if ( HasReflection(matrix) ) {
    xz = -xz; yz = -yz; zz = -zz;
  }  

  // Get axis angles
  // (Using E.Tchernaiev formula)

  double angleX;
  double angleY;
  double angleZ;
  double cosb = sqrt(xx*xx + yx*yx); 
  if (cosb > 16*FLT_EPSILON) {
    angleX = atan2( zy, zz);
    angleY = atan2(-zx, cosb);
    angleZ = atan2( yx, xx);
  }
  else{
    angleX = atan2(-yz, yy);
    angleY = atan2(-zx, cosb);
    angleZ = 0.;
  }

  transform[VGM::kAngleX] = angleX * TMath::RadToDeg() * Units::Angle();
  transform[VGM::kAngleY] = angleY * TMath::RadToDeg() * Units::Angle();
  transform[VGM::kAngleZ] = angleZ * TMath::RadToDeg() * Units::Angle();

  // Reflection 
  //
  transform[VGM::kReflZ] = 0.;
  if (matrix.IsReflection()) transform[VGM::kReflZ] = 1.;
    
  
  return transform;
}

//_____________________________________________________________________________
bool RootGM::HasReflection(const TGeoMatrix& matrix)
{
//
/*
  // Decompose general matrix 
  const Double_t* rm = matrix.GetRotation()

  // Matrix
  // rm[0] * sm[0], rm[1] * sm[1], rm[2] * sm[2], tm[0]
  // rm[3] * sm[0], rm[4] * sm[1], rm[5] * sm[2], tm[1]
  // rm[6] * sm[0], rm[7] * sm[1], rm[8] * sm[2], tm[2]

  double xx, xy, xz, dx,     // 4x3  Transformation Matrix
         yx, yy, yz, dy,
         zx, zy, zz, dz;

  xx = rm[0]; xy = rm[1]; xz = rm[2];
  yx = rm[3]; yy = rm[4]; yz = rm[5];
  zx = rm[6]; zy = rm[7]; zz = rm[8];
  dx = tm[0]; dy = tm[1]; dz = tm[2];
  sx = sm[0]; sy = sm[1]; sz = sm[2];

  // If reflection, apply it to scaleZ
  if (xx*(yy*zz-yz*zy) - xy*(yx*zz-yz*zx) + xz*(yx*zy-yy*zx) < 0) 
    return true;
  else
    return false  
*/

  return matrix.IsReflection();
}

//
// VGM -> Root
//

//_____________________________________________________________________________
TGeoMatrix* RootGM::CreateTransform(const VGM::Transform& transform)
{

  if (transform.size() != VGM::kSize) {
    std::cerr << "RootGM::CreateTransform: " << std::endl;
    std::cerr << "Wrong transform vector size. " << std::endl;
    exit(1);
  }  
    
  TGeoRotation* rootRotation = new TGeoRotation();
  rootRotation->RotateX( transform[VGM::kAngleX] / Units::Angle() );
  rootRotation->RotateY( transform[VGM::kAngleY] / Units::Angle() );
  rootRotation->RotateZ( transform[VGM::kAngleZ] / Units::Angle() );

  if (HasReflection(transform)) {
    // copy matrix in a new one
    const Double_t* matrix = rootRotation->GetRotationMatrix();
    Double_t matrix2[9];
    for (Int_t i=0; i<9; i++) matrix2[i] = matrix[i];
    
    // apply reflectionZ to rotation matrix
    matrix2[2] = - matrix2[2];  //xz
    matrix2[5] = - matrix2[5];  //yz
    matrix2[8] = - matrix2[8];  //zz

    // reset matrix
    rootRotation->SetMatrix(matrix2);
 }
 
 return new TGeoCombiTrans(transform[VGM::kDx] / Units::Length(),
                           transform[VGM::kDy] / Units::Length(),
                           transform[VGM::kDz] / Units::Length(),
			   rootRotation);
}

//_____________________________________________________________________________
bool RootGM::HasReflection(const VGM::Transform& transform)
{
  return round(transform[VGM::kReflZ]) == 1.;
}  

