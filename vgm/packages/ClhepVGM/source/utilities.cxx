// $Id$
//
// ClhepVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <float.h>

#include "ClhepVGM/utilities.h"

//_____________________________________________________________________________
VGM::ThreeVector  ClhepVGM::Translation(const Hep3Vector& translation)
{
//
  VGM::ThreeVector threeVector(3);
  threeVector[0] = translation.x();
  threeVector[1] = translation.y();
  threeVector[2] = translation.z();

  return threeVector;
}
    
//_____________________________________________________________________________
VGM::ThreeVector  ClhepVGM::Translation(const HepTransform3D& transform)
{
//
  HepScale3D scale;
  HepRotate3D rotate;
  HepTranslate3D translate;
  transform.getDecomposition(scale, rotate, translate);

  return Translation(translate.getTranslation());
}

//_____________________________________________________________________________
VGM::ThreeVector  ClhepVGM::Origin()
{
//
  VGM::ThreeVector threeVector(3);
  threeVector[0] = 0.;
  threeVector[1] = 0.;
  threeVector[2] = 0.;

  return threeVector;
}

//_____________________________________________________________________________
VGM::Rotation  ClhepVGM::Rotation(const HepRotation& rotation)
{
// 
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

  VGM::Rotation vgmRotation(3);
  vgmRotation[0] = angleX;
  vgmRotation[1] = angleY;
  vgmRotation[2] = angleZ;

  return vgmRotation;
}


//_____________________________________________________________________________
VGM::Rotation  ClhepVGM::Rotation(const HepTransform3D& transform)
{
// 
  HepScale3D scale;
  HepRotate3D rotate;
  HepTranslate3D translate;
  transform.getDecomposition(scale, rotate, translate);

  return Rotation(rotate.getRotation().inverse());
}

//_____________________________________________________________________________
VGM::Rotation  ClhepVGM::Identity()
{
//
  VGM::Rotation rotation(3);
  rotation[0] = 0.;
  rotation[1] = 0.;
  rotation[2] = 0.;

  return rotation;
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
Hep3Vector ClhepVGM::Translation(VGM::ThreeVector translation)
{
  if (translation.size() != 3) {
    std::cerr << "ClhepVGM::Translation: " << std::endl;
    std::cerr << "Wrong vector size " << translation.size() << std::endl;
    exit(1);
  }  
    
  return Hep3Vector(translation[0], translation[1], translation[2]);
}  
  

//_____________________________________________________________________________
HepRotation  ClhepVGM::Rotation(VGM::Rotation rotation)
{
  if (rotation.size() != 3) {
    std::cerr << "ClhepVGM::Rotation: " << std::endl;
    std::cerr << "Wrong vector size. " << std::endl;
    exit(1);
  }  
    
  HepRotation hepRotation;
  hepRotation.rotateX(rotation[0]);
  hepRotation.rotateY(rotation[1]);
  hepRotation.rotateZ(rotation[2]);

  return hepRotation;
}  

//_____________________________________________________________________________
HepTransform3D  ClhepVGM::Transform(VGM::Rotation rotation,
				    VGM::ThreeVector translation,
                                    bool hasReflection)
{
// !! input rotation = frame rotation
// has to be inverted to get object rotation 

  HepTranslate3D translate(Translation(translation));
  HepRotate3D rotate(Rotation(rotation).inverse());
  HepScaleZ3D scale;
  if (hasReflection) scale = HepScaleZ3D(-1.0);

  return translate * rotate * scale; 
}
