// $Id$
//
// BaseVGM utilities
// --------------
// Utility functions 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>
#include <math.h>

#include "BaseVGM/common/utilities.h"

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
