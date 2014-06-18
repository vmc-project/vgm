// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// RootGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"

#include "RootGM/common/transform.h"
#include "RootGM/common/Units.h"

#include "TGeoPatternFinder.h"
#include "TGeoBBox.h"
#include "TMath.h"

#include <iostream>
#include <float.h>
#include <math.h>

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

  double xx, xz,        // 3x3  Rotation Matrix (xy not used)
         yx, yy, yz,
         zx, zy, zz;

  xx = rm[0]; xz = rm[2];
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
  return BaseVGM::Round(transform[VGM::kReflZ]) == 1.;
}  

//
// Root special
//

//_____________________________________________________________________________
TGeoHMatrix  RootGM::Displacement(TGeoShape* shape)
{
  TGeoBBox* box = dynamic_cast<TGeoBBox*>(shape);
  if ( ! box ) return TGeoHMatrix();
  
  const Double_t* origin = box->GetOrigin();
  if ( ! origin ) return TGeoHMatrix();
  
  return  TGeoHMatrix(TGeoTranslation(origin[0], origin[1], origin[2]));;
}  
  



//_____________________________________________________________________________

// The following code was taken from the paper:
// http://jgt.akpeters.com/papers/MollerHughes99/
// Changed float to double.
// See below the authors.

#include <math.h>

#define EPSILON 0.000001

#define CROSS(dest, v1, v2){                 \
          dest[0] = v1[1] * v2[2] - v1[2] * v2[1]; \
          dest[1] = v1[2] * v2[0] - v1[0] * v2[2]; \
          dest[2] = v1[0] * v2[1] - v1[1] * v2[0];}

#define DOT(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])

#define SUB(dest, v1, v2){       \
          dest[0] = v1[0] - v2[0]; \
          dest[1] = v1[1] - v2[1]; \
          dest[2] = v1[2] - v2[2];}

/*
 * A function for creating a rotation matrix that rotates a vector called
 * "from" into another vector called "to".
 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
 * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
 * Authors: Tomas Möller, John Hughes
 *          "Efficiently Building a Matrix to Rotate One Vector to Another"
 *          Journal of Graphics Tools, 4(4):1-4, 1999
 */
void RootGM::fromToRotation(double from[3], double to[3], double mtx[3][3]) {
  double v[3];
  double e, h, f;

  CROSS(v, from, to);
  e = DOT(from, to);
  f = (e < 0)? -e:e;
  if (f > 1.0 - EPSILON)     /* "from" and "to"-vector almost parallel */
  {
    double utmp[3], vtmp[3]; /* temporary storage vectors */
    double x[3];       /* vector most nearly orthogonal to "from" */
    double c1, c2, c3; /* coefficients for later use */
    int i, j;

    x[0] = (from[0] > 0.0)? from[0] : -from[0];
    x[1] = (from[1] > 0.0)? from[1] : -from[1];
    x[2] = (from[2] > 0.0)? from[2] : -from[2];

    if (x[0] < x[1])
    {
      if (x[0] < x[2])
      {
        x[0] = 1.0; x[1] = x[2] = 0.0;
      }
      else
      {
        x[2] = 1.0; x[0] = x[1] = 0.0;
      }
    }
    else
    {
      if (x[1] < x[2])
      {
        x[1] = 1.0; x[0] = x[2] = 0.0;
      }
      else
      {
        x[2] = 1.0; x[0] = x[1] = 0.0;
      }
    }

    utmp[0] = x[0] - from[0]; utmp[1] = x[1] - from[1]; utmp[2] = x[2] - from[2];
    vtmp[0] = x[0] - to[0];   vtmp[1] = x[1] - to[1];   vtmp[2] = x[2] - to[2];

    c1 = 2.0 / DOT(utmp, utmp);
    c2 = 2.0 / DOT(vtmp, vtmp);
    c3 = c1 * c2  * DOT(utmp, vtmp);

    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        mtx[i][j] =  - c1 * utmp[i] * utmp[j]
                     - c2 * vtmp[i] * vtmp[j]
                     + c3 * vtmp[i] * utmp[j];
      }
      mtx[i][i] += 1.0;
    }
  }
  else  /* the most common case, unless "from"="to", or "from"=-"to" */
  {
#if 0
    /* unoptimized version - a good compiler will optimize this. */
    /* h = (1.0 - e)/DOT(v, v); old code */
    h = 1.0/(1.0 + e);      /* optimization by Gottfried Chen */
    mtx[0][0] = e + h * v[0] * v[0];
    mtx[0][1] = h * v[0] * v[1] - v[2];
    mtx[0][2] = h * v[0] * v[2] + v[1];

    mtx[1][0] = h * v[0] * v[1] + v[2];
    mtx[1][1] = e + h * v[1] * v[1];
    mtx[1][2] = h * v[1] * v[2] - v[0];

    mtx[2][0] = h * v[0] * v[2] - v[1];
    mtx[2][1] = h * v[1] * v[2] + v[0];
    mtx[2][2] = e + h * v[2] * v[2];
#else
    /* ...otherwise use this hand optimized version (9 mults less) */
    double hvx, hvz, hvxy, hvxz, hvyz;
    /* h = (1.0 - e)/DOT(v, v); old code */
    h = 1.0/(1.0 + e);      /* optimization by Gottfried Chen */
    hvx = h * v[0];
    hvz = h * v[2];
    hvxy = hvx * v[1];
    hvxz = hvx * v[2];
    hvyz = hvz * v[1];
    mtx[0][0] = e + hvx * v[0];
    mtx[0][1] = hvxy - v[2];
    mtx[0][2] = hvxz + v[1];

    mtx[1][0] = hvxy + v[2];
    mtx[1][1] = e + h * v[1] * v[1];
    mtx[1][2] = hvyz - v[0];

    mtx[2][0] = hvxz - v[1];
    mtx[2][1] = hvyz + v[0];
    mtx[2][2] = e + hvz * v[2];
#endif
  }
}
