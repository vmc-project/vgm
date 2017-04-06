// $Id$

// -----------------------------------------------------------------------
// The ClhepVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// ClhepVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/transform.h"
#include "ClhepVGM/Units.h"

#include <float.h>
#include <cstdlib>

//_____________________________________________________________________________
VGM::Transform    
ClhepVGM::Transform(const CLHEP::HepRotation& rotation,
                    const CLHEP::Hep3Vector&  translation)
{

  // Translation
  //
  VGM::Transform transform(VGM::kSize);
  transform[VGM::kDx] = translation.x() * Units::Length();
  transform[VGM::kDy] = translation.y() * Units::Length();
  transform[VGM::kDz] = translation.z() * Units::Length();

  // Get axis angles
  // (Using E.Tchernaiev formula)
  double angleX;
  double angleY;
  double angleZ;
  double cosb = sqrt(rotation.xx()*rotation.xx() + rotation.yx()*rotation.yx()); 
  if (cosb > 16*FLT_EPSILON) {
    angleX = atan2( rotation.zy(), rotation.zz());
    angleY = atan2(-rotation.zx(), cosb);
    angleZ = atan2( rotation.yx(), rotation.xx());
  }
  else{
    angleX = atan2(-rotation.yz(), rotation.yy());
    angleY = atan2(-rotation.zx(), cosb);
    angleZ = 0.;
  }

  transform[VGM::kAngleX] = angleX * Units::Angle();
  transform[VGM::kAngleY] = angleY * Units::Angle();
  transform[VGM::kAngleZ] = angleZ * Units::Angle();

  // No reflection
  transform[VGM::kReflZ] = 0.;
  
  return transform;
}  		    
				
//_____________________________________________________________________________
VGM::Transform    
ClhepVGM::Transform(const HepGeom::Transform3D& objectTransform)
{
// 
  HepGeom::Scale3D scale;
  HepGeom::Rotate3D rotate;
  HepGeom::Translate3D translate;
  objectTransform.getDecomposition(scale, rotate, translate);
  
  VGM::Transform transform 
    = Transform(rotate.getRotation(), translate.getTranslation()); 

  if (scale(0,0)*scale(1,1)*scale(2,2) < 0.)
    transform[VGM::kReflZ] = 1.;
  else 
    transform[VGM::kReflZ] = 0;;  

  return transform;
}

//_____________________________________________________________________________
VGM::Transform    
ClhepVGM::TransformScale(const HepGeom::Scale3D& scale3D)
{
  VGM::Transform transform(VGM::kSize);
  transform[VGM::kDx] = scale3D(0,0);
  transform[VGM::kDy] = scale3D(1,1);
  transform[VGM::kDz] = scale3D(2,2);

  return transform;
}

//_____________________________________________________________________________
VGM::Transform  ClhepVGM::Identity()
{
//
  VGM::Transform transform(VGM::kSize);
  for (int i=0; i<7; i++) transform[i] = 0.;
 
  return transform;
}

//_____________________________________________________________________________
bool ClhepVGM::HasReflection(const HepGeom::Transform3D& transform)
{
//
  HepGeom::Scale3D scale;
  HepGeom::Rotate3D rotate;
  HepGeom::Translate3D translate;
  transform.getDecomposition(scale, rotate, translate);

  if (scale(0,0)*scale(1,1)*scale(2,2) < 0.)
    return true;
  else 
    return false;  
}

//_____________________________________________________________________________
CLHEP::Hep3Vector ClhepVGM::Translation(const VGM::Transform& transform)
{
  if (transform.size() != VGM::kSize) {
    std::cerr << "ClhepVGM::Translation: " << std::endl;
    std::cerr << "Wrong vector size " << transform.size() << std::endl;
    exit(1);
  }  
    
  return CLHEP::Hep3Vector(transform[VGM::kDx] / Units::Length(), 
                           transform[VGM::kDy] / Units::Length(), 
                           transform[VGM::kDz] / Units::Length());
} 


//_____________________________________________________________________________
CLHEP::HepRotation  ClhepVGM::Rotation(const VGM::Transform& transform)
{
  if (transform.size() != VGM::kSize) {
    std::cerr << "ClhepVGM::Rotation: " << std::endl;
    std::cerr << "Wrong vector size. " << std::endl;
    exit(1);
  }  
    
  CLHEP::HepRotation hepRotation;
  hepRotation.rotateX(transform[VGM::kAngleX] / Units::Angle() );
  hepRotation.rotateY(transform[VGM::kAngleY] / Units::Angle() );
  hepRotation.rotateZ(transform[VGM::kAngleZ] / Units::Angle() );

  return hepRotation;
}  

//_____________________________________________________________________________
 HepGeom::Scale3D  ClhepVGM::Scale(const VGM::Transform& transform)
{
  return HepGeom::Scale3D(transform[VGM::kDx], 
                          transform[VGM::kDy], 
                          transform[VGM::kDz]);
}

//_____________________________________________________________________________
HepGeom::Transform3D  ClhepVGM::Transform(const VGM::Transform& transform)
{    
  HepGeom::Translate3D translate(Translation(transform));
  HepGeom::Rotate3D rotate(Rotation(transform));
  HepGeom::ScaleZ3D scale;
  if (HasReflection(transform)) scale = HepGeom::ScaleZ3D(-1.0);

  return translate * rotate * scale; 
}

//_____________________________________________________________________________
bool ClhepVGM::HasReflection(const VGM::Transform& transform)
{
  return Round(transform[VGM::kReflZ]) == 1.;
}  

//_____________________________________________________________________________
VGM::Transform  ClhepVGM::Inverse(const VGM::Transform& transform)
{    
  HepGeom::Translate3D translate(Translation(transform));
  HepGeom::Rotate3D rotate(Rotation(transform));
  HepGeom::ScaleZ3D scale;
  if (HasReflection(transform)) scale = HepGeom::ScaleZ3D(-1.0);
  
  return Transform((translate * rotate * scale).inverse());
}

//_____________________________________________________________________________
double ClhepVGM::Round(double x)
{
/// Replacement for round(double) function from math.h
/// which is not available on all platforms (gcc 2.95.x, Windows)

  double t;
  if (x >= 0.0) {
    t = ceil(x);
    if (t - x > 0.5) t -= 1.0;
    return t;
  } 
  else {
    t = ceil(-x);
    if (t + x > 0.5) t -= 1.0;
    return -t;
  }
}

