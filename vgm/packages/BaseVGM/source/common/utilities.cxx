// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>

#include "BaseVGM/common/utilities.h"

//_____________________________________________________________________________
VGM::ThreeVector  BaseVGM::Origin()
{
//
  VGM::ThreeVector threeVector(3);
  threeVector[0] = 0.;
  threeVector[1] = 0.;
  threeVector[2] = 0.;

  return threeVector;
}

//_____________________________________________________________________________
VGM::Rotation  BaseVGM::Identity()
{
//
  VGM::Rotation rotation(3);
  rotation[0] = 0.;
  rotation[1] = 0.;
  rotation[2] = 0.;

  return rotation;
}

//_____________________________________________________________________________
void  BaseVGM::DebugInfo()
{
// 
  std::cout << "VGM info:   ";
}  
