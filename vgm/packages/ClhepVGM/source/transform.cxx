// $Id$
//
// ClhepVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <float.h>

#include "ClhepVGM/transform.h"

//_____________________________________________________________________________
VGM::Transform    
ClhepVGM::Transform(const HepRotation& rotation,
                    const Hep3Vector&  translation)
{

  // Translation
  //
  VGM::Transform transform(VGM::kSize);
  transform[VGM::kDx] = translation.x();
  transform[VGM::kDy] = translation.y();
  transform[VGM::kDz] = translation.z();

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

  transform[VGM::kAngleX] = angleX;
  transform[VGM::kAngleY] = angleY;
  transform[VGM::kAngleZ] = angleZ;

  // No reflection
  transform[VGM::kReflZ] = 0.;
  
  return transform;
}  		    
				
//_____________________________________________________________________________
VGM::Transform    
ClhepVGM::Transform(const HepTransform3D& objectTransform)
{
// 
  HepScale3D scale;
  HepRotate3D rotate;
  HepTranslate3D translate;
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
VGM::Transform  ClhepVGM::Identity()
{
//
  VGM::Transform transform(VGM::kSize);
  for (int i=0; i<7; i++) transform[i] = 0.;
 
  return transform;
}

//_____________________________________________________________________________
bool ClhepVGM::HasReflection(const HepTransform3D& transform)
{
//
  HepScale3D scale;
  HepRotate3D rotate;
  HepTranslate3D translate;
  transform.getDecomposition(scale, rotate, translate);

  if (scale(0,0)*scale(1,1)*scale(2,2) < 0.)
    return true;
  else 
    return false;  
}

//_____________________________________________________________________________
Hep3Vector ClhepVGM::Translation(const VGM::Transform& transform)
{
  if (transform.size() != VGM::kSize) {
    std::cerr << "ClhepVGM::Translation: " << std::endl;
    std::cerr << "Wrong vector size " << transform.size() << std::endl;
    exit(1);
  }  
    
  return Hep3Vector(transform[VGM::kDx], 
                    transform[VGM::kDy], 
		    transform[VGM::kDz]);
}  


//_____________________________________________________________________________
HepRotation  ClhepVGM::Rotation(const VGM::Transform& transform)
{
  if (transform.size() != VGM::kSize) {
    std::cerr << "ClhepVGM::Rotation: " << std::endl;
    std::cerr << "Wrong vector size. " << std::endl;
    exit(1);
  }  
    
  HepRotation hepRotation;
  hepRotation.rotateX(transform[VGM::kAngleX]);
  hepRotation.rotateY(transform[VGM::kAngleY]);
  hepRotation.rotateZ(transform[VGM::kAngleZ]);

  return hepRotation;
}  

//_____________________________________________________________________________
HepTransform3D  ClhepVGM::Transform(const VGM::Transform& transform)
{    
  HepTranslate3D translate(Translation(transform));
  HepRotate3D rotate(Rotation(transform));
  HepScaleZ3D scale;
  if (HasReflection(transform)) scale = HepScaleZ3D(-1.0);

  return translate * rotate * scale; 
}

//_____________________________________________________________________________
bool ClhepVGM::HasReflection(const VGM::Transform& transform)
{
  return round(transform[VGM::kReflZ]) == 1.;
}  

//_____________________________________________________________________________
VGM::Transform  ClhepVGM::Inverse(const VGM::Transform& transform)
{    
  HepTranslate3D translate(Translation(transform));
  HepRotate3D rotate(Rotation(transform));
  HepScaleZ3D scale;
  if (HasReflection(transform)) scale = HepScaleZ3D(-1.0);
  
  return Transform((translate * rotate * scale).inverse());
}

