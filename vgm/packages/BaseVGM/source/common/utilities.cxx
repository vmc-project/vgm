// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"

//_____________________________________________________________________________
Hep3Vector  BaseVGM::GetTranslation(const HepTransform3D& transform)
{
//
  HepScale3D scale;
  HepRotate3D rotation;
  HepTranslate3D translation;
  transform.getDecomposition(scale, rotation, translation);

  return translation.getTranslation();
}
    
//_____________________________________________________________________________
HepRotation  BaseVGM::GetRotation(const HepTransform3D& transform)
{
// 
  HepScale3D scale;
  HepRotate3D rotation;
  HepTranslate3D translation;
  transform.getDecomposition(scale, rotation, translation);

  return rotation.getRotation();
}

//_____________________________________________________________________________
HepScale3D BaseVGM::GetScale(const HepTransform3D& transform)
{    
// 
  HepScale3D scale;
  HepRotate3D rotation;
  HepTranslate3D translation;
  transform.getDecomposition(scale, rotation, translation);

  return scale;
}

//_____________________________________________________________________________
bool BaseVGM::HasReflection(const HepTransform3D& transform)
{
//
  return HasReflection(GetScale(transform));
}

//_____________________________________________________________________________
bool BaseVGM::HasReflection(const HepScale3D& scale)
{
//
  if (scale(0,0)*scale(1,1)*scale(2,2) < 0.)
    return true;
  else 
    return false;  
}

//_____________________________________________________________________________
void  BaseVGM::DebugInfo()
{
// 
  std::cout << "VGM info:   ";
}  
