// $Id$
//
// RootGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>
#include <float.h>

#include <TGeoMatrix.h>
#include <TGeoPatternFinder.h>

#include "RootGM/common/utilities.h"
#include "RootGM/common/Units.h"

//
// Root -> VGM
//

//_____________________________________________________________________________
VGM::ThreeVector  RootGM::Translation(const TGeoMatrix& matrix)
{
//
  const Double_t* translation = matrix.GetTranslation();

  VGM::ThreeVector threeVector(3);
  threeVector[0] = translation[0] * Units::Length();
  threeVector[1] = translation[1] * Units::Length();
  threeVector[2] = translation[2] * Units::Length();

  return threeVector;
}
    
//_____________________________________________________________________________
VGM::ThreeVector  RootGM::Rotation(const TGeoMatrix& matrix)
{
//
/*
  // Decompose general matrix 
  const Double_t* tm = matrix.GetTranslation();
  const Double_t* rm = matrix.GetRotationMatrix();
  const Double_t* sm = matrix.GetScale();

  // Matrix
  // rm[0] * sm[0], rm[1] * sm[1], rm[2] * sm[2], tm[0]
  // rm[3] * sm[0], rm[4] * sm[1], rm[5] * sm[2], tm[1]
  // rm[6] * sm[0], rm[7] * sm[1], rm[8] * sm[2], tm[2]

  double xx, xy, xz, dx,     // 4x3  Transformation Matrix
         yx, yy, yz, dy,
         zx, zy, zz, dz;
  double sx, sy, sz;

  xx = rm[0]; xy = rm[1]; xz = rm[2];
  yx = rm[3]; yy = rm[4]; yz = rm[5];
  zx = rm[6]; zy = rm[7]; zz = rm[8];
  dx = tm[0]; dy = tm[1]; dz = tm[2];
  sx = sm[0]; sy = sm[1]; sz = sm[2];

  // If reflection, apply it to scaleZ
  if (xx*(yy*zz-yz*zy) - xy*(yx*zz-yz*zx) + xz*(yx*zy-yy*zx) < 0) {
    sz = -sz;
    xz = -xz; yz = -yz; zz = -zz;
  }  
*/
  // Get rotation matrix parameters 

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

  VGM::ThreeVector threeVector(3);
  threeVector[0] = angleX;
  threeVector[1] = angleY;
  threeVector[2] = angleZ;

  return threeVector;
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

//_____________________________________________________________________________
VGM::Axis RootGM::Axis(const TGeoPatternFinder* finder)
{
// Checks the finder concrete type and returns the division axis.
// ---

  const TGeoPatternX*  finderX 
    = dynamic_cast<const TGeoPatternX*>(finder);
  if (finderX) return VGM::kXAxis;

  const TGeoPatternY*  finderY 
    = dynamic_cast<const TGeoPatternY*>(finder);
  if (finderY) return VGM::kYAxis;

  const TGeoPatternZ*  finderZ 
    = dynamic_cast<const TGeoPatternZ*>(finder);
  if (finderZ) return VGM::kZAxis;

  const TGeoPatternParaX*  finderParaX 
    = dynamic_cast<const TGeoPatternParaX*>(finder);
  if (finderParaX) return VGM::kXAxis;

  const TGeoPatternParaY*  finderParaY 
    = dynamic_cast<const TGeoPatternParaY*>(finder);
  if (finderParaY) return VGM::kYAxis;

  const TGeoPatternParaZ*  finderParaZ 
    = dynamic_cast<const TGeoPatternParaZ*>(finder);
  if (finderParaZ) return VGM::kZAxis;

  const TGeoPatternTrapZ*  finderTrapZ 
    = dynamic_cast<const TGeoPatternTrapZ*>(finder);
  if (finderTrapZ) return VGM::kZAxis;

  const TGeoPatternCylR* finderR 
    = dynamic_cast<const TGeoPatternCylR*>(finder);
  if (finderR) return VGM::kRho;

  const TGeoPatternCylPhi* finderPhi 
    = dynamic_cast<const TGeoPatternCylPhi*>(finder);
  if (finderPhi) return VGM::kPhi;

  const TGeoPatternSphR* finderSphR 
    = dynamic_cast<const TGeoPatternSphR*>(finder);
  if (finderSphR) return VGM::kRadial3D;

  const TGeoPatternSphPhi* finderSphPhi 
    = dynamic_cast<const TGeoPatternSphPhi*>(finder);
  if (finderSphPhi) return VGM::kPhi;
  
  const TGeoPatternSphTheta* finderSphTheta 
    = dynamic_cast<const TGeoPatternSphTheta*>(finder);
  if (finderSphTheta) return VGM::kSphTheta;
  
  // Not supported shapes:
  // Honeycomb
  
  return  VGM::kUnknownAxis;
 }

//
// VGM -> Root
//

//_____________________________________________________________________________
TGeoMatrix*  RootGM::CreateTranslation(VGM::ThreeVector translation)
{
  if (translation.size() != 3) {
    std::cerr << "RootGM::CreateTranslation: " << std::endl;
    std::cerr << "Wrong vector size. " << std::endl;
    exit(1);
  }  
    
  return new TGeoTranslation(translation[0] / Units::Length(), 
                             translation[1] / Units::Length(), 
			     translation[2] / Units::Length());
}  
  

//_____________________________________________________________________________
TGeoMatrix*  RootGM::CreateRotation(VGM::Rotation rotation)
{
  if (rotation.size() != 3) {
    std::cerr << "RootGM::CreateRotation: " << std::endl;
    std::cerr << "Wrong vector size. " << std::endl;
    exit(1);
  }  
    
  TGeoRotation* rootRotation = new TGeoRotation();
  rootRotation->RotateX( - rotation[0] / Units::Angle() );
  rootRotation->RotateY( - rotation[1] / Units::Angle() );
  rootRotation->RotateZ( - rotation[2] / Units::Angle() );

  return rootRotation;
}  

//_____________________________________________________________________________
TGeoMatrix*  RootGM::CreateTransform(VGM::Rotation rotation,
				     VGM::ThreeVector translation,
                                     bool hasReflection)
{

  if (translation.size() != 3) {
    std::cerr << "RootGM::CreateTransform: " << std::endl;
    std::cerr << "Wrong translation vector size. " << std::endl;
    exit(1);
  }  
    
  if (rotation.size() != 3) {
    std::cerr << "RootGM::CreateTransform: " << std::endl;
    std::cerr << "Wrong rotation vector size. " << std::endl;
    exit(1);
  }  
    
  TGeoRotation* rootRotation = new TGeoRotation();
  rootRotation->RotateX( - rotation[0] / Units::Angle() );
  rootRotation->RotateY( - rotation[1] / Units::Angle() );
  rootRotation->RotateZ( - rotation[2] / Units::Angle() );

  if (hasReflection) {
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
 
 return new TGeoCombiTrans(translation[0] / Units::Length(),
                           translation[1] / Units::Length(),
                           translation[2] / Units::Length(),
			   rootRotation);
}
//_____________________________________________________________________________
int RootGM::Axis(VGM::Axis axis)
{
// Converts VGM axis enum to Root axis number.
// ---

  switch (axis) {
    case VGM::kXAxis:    return 1;
    case VGM::kYAxis:    return 2;
    case VGM::kZAxis:    return 3;
    case VGM::kRho:      return 1;
    case VGM::kPhi:      return 2;
    case VGM::kSphTheta: return 3;
    case VGM::kRadial3D: return 1;
    case VGM::kUnknownAxis: return 0;
  }
  
  return 0;
}    

//_____________________________________________________________________________
double RootGM::AxisUnit(VGM::Axis axis)
{
  switch (axis) {
    case VGM::kXAxis:    return RootGM::Units::Length(); break;
    case VGM::kYAxis:    return RootGM::Units::Length(); break;
    case VGM::kZAxis:    return RootGM::Units::Length(); break;
    case VGM::kRho:      return RootGM::Units::Length(); break;
    case VGM::kRadial3D: return RootGM::Units::Length(); break;
    case VGM::kPhi:      return RootGM::Units::Angle();  break;
    case VGM::kUnknownAxis: return 0; break;
    default:  return 0; break;
  }  
}    

//
// Other functions
//

//_____________________________________________________________________________
bool RootGM::IsDivided(const TGeoVolume* volume)
{
// Returns true if the volume is divided
// and division is known to VGM.
// ---

  // Check if division is present
  const TGeoPatternFinder* finder = volume->GetFinder();    
  if (!finder) return false;
    
  // Get division axis
  VGM::Axis axis = Axis(finder);
  if (axis == VGM::kUnknownAxis) return false;
  
  // Volume can be processed as VGM division
  return true;
}  


