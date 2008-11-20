// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"

#include <iostream>
#include <math.h>

//_____________________________________________________________________________
void  BaseVGM::DebugInfo()
{
// 
  std::cout << "VGM info:   ";
}  

//_____________________________________________________________________________
double BaseVGM::Round(double x)
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
