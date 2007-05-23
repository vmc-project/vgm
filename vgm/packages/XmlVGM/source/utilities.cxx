// $Id$

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// XmlVGM utilities
// --------------
// Utility functions 
//
// Author: I. Hrivnacova, 27.07.2000 

#include "XmlVGM/utilities.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>

#include <VGM/materials/IIsotope.h>

#include <ClhepVGM/transform.h>


//_____________________________________________________________________________
std::string 
XmlVGM::UpdateName(const std::string& name,
                   const std::string& extension)
{
/// Remove spaces after the name if present,
/// replace not allowed characters with fgkCharReplacement inside names
/// and apped the specified extension.

  std::string newName(name);

  // Remove spaces after the name
  int i = newName.length();
  while (newName[--i] == ' ') newName = std::string(newName, 0, i);
  
  // Replace not allowed characters
  //
  for (i=0; i<int(newName.length()); i++) {
  
    if (( i==0 && 
          fgkNotAllowedChars1.find(newName[i]) < fgkNotAllowedChars1.size()) ||
          fgkNotAllowedChars.find(newName[i]) < fgkNotAllowedChars.size() )
	    
      newName[i] = fgkCharReplacement;
  }      
      
  // Append extension
  newName.append(extension);
  
  return newName;     
}  

//_____________________________________________________________________________
std::string 
XmlVGM::StripName(const std::string& name,
                  const std::string& extension)
{
/// Remove specified extension from the name if present

  return name.substr(0, name.find(extension));
}  

//_____________________________________________________________________________
std::string 
XmlVGM::AppendName(const std::string& name, int size)
{
///  Append name with spaces to get the desired size

  std::string newName(name);

  for (int i=0; i < size - int(name.size()); i++) {
    //std::cout << string << "appending " << i << std::endl;
    newName.append(" ");
  }  
  
  return newName;
}  

//_____________________________________________________________________________
std::string 
XmlVGM::IsotopeName(const VGM::IIsotope* isotope)
{
/// Generate isotope name in the form Symbol_N

  std::string name = UpdateName(isotope->Name());
  std::ostringstream nStream;
  nStream << isotope->N();  
  std::string n(nStream.str());
  
  // Cut N from name if present
  if ( name.find(n) < name.size() ) 
    name.insert(name.find(n), 1, fgkCharReplacement);
  else  {   
    name += fgkCharReplacement;
    name += n;
  }  
  
  return name;
}  
                       
//_____________________________________________________________________________
void XmlVGM::CutName(std::string& name)
{
/// Removes spaces after the name if present

  int i = name.length();
  while (name[--i] == ' ') name = std::string(name,0,i);
}  

//_____________________________________________________________________________
void XmlVGM::CutName(std::string& name, int size)
{
// Cut name to given size

  if (int(name.length()) > size) name = std::string(name, 0, size);
}  

//_____________________________________________________________________________
std::ostream& 
XmlVGM::SmartPut(std::ostream& out, 
                 int size, int precision,
                 double number, 
		 const std::string& separator)
{
/// Help function to supress - sign in case the number == 0
/// within the given precision

  if ( ClhepVGM::Round(number*pow(10.,precision))/pow(10.,precision) == 0.0) {
    number = 0.;
  }  
  
  out << std::setw(size) << std::setprecision(precision) 
      << number << separator;
  
  return out;
}

//_____________________________________________________________________________
std::ostream& 
XmlVGM::SmartPut(std::ostream& out, 
                 int size, int precision,
		 const std::string& separator1,
                 double number, 
		 const std::string& separator2)
{
/// Help function to supress - sign in case the number == 0
/// within the given precision

  if ( ClhepVGM::Round(number*pow(10.,precision))/pow(10.,precision) == 0.0) {
    number = 0.;
  }  
  
  out << separator1;
  out << std::setw(size) << std::setprecision(precision) << number;
  out << separator2;
  
  return out;
}


//_____________________________________________________________________________
std::string XmlVGM::Date()
{
/// Convert date to string

  time_t t = time(0);
  tm time = *localtime(&t);

  std::ostringstream tmpStream;
  tmpStream 
    << time.tm_year + 1900 << "-" 
    << std::setw(2) << std::setfill('0') << time.tm_mon + 1 << "-" 
    << std::setw(2) << std::setfill('0') << time.tm_mday; 
  
  return tmpStream.str();
}

