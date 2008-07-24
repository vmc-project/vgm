// $Id$

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup XmlVGM
//
/// XmlVGM utilities
/// 
/// Utility functions 
///
/// \author I. Hrivnacova, IPN Orsay

#ifndef XML_VGM_UTILITIES_H
#define XML_VGM_UTILITIES_H

#include <VGM/materials/IIsotope.h>

#include "XmlVGM/Maps.h"

namespace XmlVGM {

  std::string UpdateName(const std::string& name,         
                         const std::string& extension = "");
  
  std::string StripName(const std::string& name,         
                         const std::string& extension = "");

  std::string AppendName(const std::string& name, int size);

  std::string IsotopeName(const VGM::IIsotope* isotope);                       

  void CutName(std::string& name);
  void CutName(std::string& name, int size);

  std::ostream& SmartPut(std::ostream& out, 
                     int size, int precision,
                     double number, const std::string& separator);
  
  std::ostream& SmartPut(std::ostream& out,
		     int size, int precision,
		     const std::string& separator1, 
		     double number, const std::string& separator2);

  std::string  Date();

  // date
  const char         fgkCharReplacement  = '_';   //replacement for ' ' in names 
  const std::string  fgkNotAllowedChars  = " +-*/&<>%^$()"; //not allowed characters in XML
  const std::string  fgkNotAllowedChars1 = "0123456789";  //not allowed first characters
}

#endif //XML_VGM_UTILITIES_H

