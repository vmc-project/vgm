// $Id$
//
// Utilities
// --------------
// Functions for conversion between Root and VGM basic elements
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoVolume.h"

#include "BaseVGM/common/utilities.h"

#include "RootGM/common/utilities.h"
#include "RootGM/common/RotationMatrix.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
TGeoMatrix* RootGM::Convert(HepRotation* rot, const Hep3Vector& tr)
{
  if (!rot)
    return new TGeoTranslation(tr.x()/RootGM::Units::Length(),
                               tr.y()/RootGM::Units::Length(), 
			       tr.z()/RootGM::Units::Length());			  
  else {
    // 
    HepRotation rot2 = rot->inverse();
    
    TGeoRotation* rootRotation 
      = new TGeoRotation("rot", 
                rot2.thetaX()/RootGM::Units::Angle(), 
		rot2.phiX()/RootGM::Units::Angle(), 
	        rot2.thetaY()/RootGM::Units::Angle(), 
		rot2.phiY()/RootGM::Units::Angle(),
                rot2.thetaZ()/RootGM::Units::Angle(), 
		rot2.phiZ()/RootGM::Units::Angle());
    
    return new TGeoCombiTrans(tr.x()/RootGM::Units::Length(), 
                              tr.y()/RootGM::Units::Length(), 
			      tr.z()/RootGM::Units::Length(), 
			      rootRotation);
  }  			  
}

//_____________________________________________________________________________
TGeoMatrix* RootGM::Convert(const HepTransform3D& transform3D)
{
  // Decompose transformation
  HepScale3D     scale3D;
  HepRotate3D    rotate3D;
  HepTranslate3D translate3D;
  transform3D.getDecomposition(scale3D, rotate3D, translate3D);

  Hep3Vector translation = translate3D.getTranslation();

  HepTransform3D rotateAndScale3D = rotate3D * scale3D;
  Double_t* matrix = new Double_t[9];
  matrix[0] = rotateAndScale3D(0,0);
  matrix[1] = rotateAndScale3D(0,1);
  matrix[2] = rotateAndScale3D(0,2);
  matrix[3] = rotateAndScale3D(1,0);
  matrix[4] = rotateAndScale3D(1,1);
  matrix[5] = rotateAndScale3D(1,2);
  matrix[6] = rotateAndScale3D(2,0);
  matrix[7] = rotateAndScale3D(2,1);
  matrix[8] = rotateAndScale3D(2,2);
  TGeoRotation* rootRotation = new TGeoRotation("rot");
  rootRotation->SetMatrix(matrix);

  return new TGeoCombiTrans(translation.x()/RootGM::Units::Length(), 
                            translation.y()/RootGM::Units::Length(), 
			    translation.z()/RootGM::Units::Length(), 
			    rootRotation);
}			    

/*
//_____________________________________________________________________________
TGeoMatrix* RootGM::Convert(const HepTransform3D& transform3D)
{
 // Though more elegant, does not work,
 // as Root does not allow scale <0. 

 // Decompose transformation
  HepScale3D     scale3D;
  HepRotate3D    rotate3D;
  HepTranslate3D translate3D;
  transform3D.getDecomposition(scale3D, rotate3D, translate3D);

  Hep3Vector translation = translate3D.getTranslation();
  TGeoTranslation rootTranslation
    = TGeoTranslation(translation.x()/RootGM::Units::Length(),
                      translation.y()/RootGM::Units::Length(), 
		      translation.z()/RootGM::Units::Length());			  

  HepRotation rotation = rotate3D.getRotation();
  TGeoRotation rootRotation 
    = TGeoRotation("rot", 
                    rotation.thetaX()/RootGM::Units::Angle(), 
		    rotation.phiX()/RootGM::Units::Angle(), 
	            rotation.thetaY()/RootGM::Units::Angle(), 
		    rotation.phiY()/RootGM::Units::Angle(),
                    rotation.thetaZ()/RootGM::Units::Angle(), 
		    rotation.phiZ()/RootGM::Units::Angle());
		       
  TGeoScale rootScale
    = TGeoScale(scale3D(0,0), scale3D(1,1), scale3D(2,2));
  		       
  // Recompose TGeoHMatrix
  TGeoHMatrix matrix =  (rootTranslation) * (rootRotation) * (rootScale);
  
  // Return new TGeoCombiTrans as this type should be used
  // in building geometry
  return new TGeoCombiTrans(matrix.GetTranslation()[0],
                            matrix.GetTranslation()[1],
                            matrix.GetTranslation()[2],
			    rootRotation2);
}
*/  

//_____________________________________________________________________________
HepTransform3D RootGM::Convert(const TGeoMatrix* matrix)
{
// Convert Root transformation into CLHEP one
// --- 

  const double* rtTranslation = matrix->GetTranslation();
  const double* rtRotation = matrix->GetRotationMatrix();
  const double* rtScale = matrix->GetScale();

/*
  std::cout << "Root: " << std::endl;
  std::cout << rtTranslation[0] * RootGM::Units::Length() << ", "
            << rtTranslation[1] * RootGM::Units::Length() << ", "
	    << rtTranslation[2] * RootGM::Units::Length() << std::endl
	    << "---" << std::endl;
	    
  std::cout << rtRotation[0] << ", " << rtRotation[1] << ", " << rtRotation[2] << std::endl	    
            << rtRotation[3] << ", " << rtRotation[4] << ", " << rtRotation[5] << std::endl	    
            << rtRotation[6] << ", " << rtRotation[7] << ", " << rtRotation[8] << std::endl
	    << "---" << std::endl;

  std::cout << rtScale[0] << ", " << rtScale[1] << ", " << rtScale[2] << std::endl	    	    
	    << "===" << std::endl;
*/   
  HepTranslate3D translate3D(rtTranslation[0] * RootGM::Units::Length(),
                             rtTranslation[1] * RootGM::Units::Length(), 
	 		     rtTranslation[2] * RootGM::Units::Length());
  RootGM::RotationMatrix grtRotation;
  grtRotation.SetRotationMatrixByRow(
                    Hep3Vector(rtRotation[0], rtRotation[1], rtRotation[2]),
                    Hep3Vector(rtRotation[3], rtRotation[4], rtRotation[5]),
                    Hep3Vector(rtRotation[6], rtRotation[7], rtRotation[8]));
  HepRotate3D rotate3D(grtRotation);
  HepScale3D scale3D(rtScale[0], rtScale[1], rtScale[2]);
 
  HepTransform3D transform3D = translate3D * rotate3D * scale3D;

/*  
  HepScale3D scale2;
  HepRotate3D rotation2;
  HepTranslate3D translation2;
  transform3D.getDecomposition(scale2, rotation2, translation2);

  std::cout << "CLHEP: " << std::endl;
  std::cout << translation2.getTranslation()[0] << ", "
            << translation2.getTranslation()[1] << ", "
	    << translation2.getTranslation()[2] << std::endl
	    << "---" << std::endl;
	    
  std::cout << rotation2.getRotation()(0,0) << ", " << rotation2.getRotation()(0,1) << ", " << rotation2.getRotation()(0,2) << std::endl	    
            << rotation2.getRotation()(1,0) << ", " << rotation2.getRotation()(1,1) << ", " << rotation2.getRotation()(1,2) << std::endl	    
            << rotation2.getRotation()(2,0) << ", " << rotation2.getRotation()(2,1) << ", " << rotation2.getRotation()(2,2) << std::endl
	    << "---" << std::endl;

  std::cout << scale2(0,0) << ", " << scale2(1,1) << ", " << scale2(2,2) << std::endl	    	    
	    << "===" << std::endl;
*/
  return transform3D;
}  

//_____________________________________________________________________________
Hep3Vector RootGM::GetTranslation(const TGeoMatrix* matrix)
{
  HepTransform3D transform3D = Convert(matrix);
  return BaseVGM::GetTranslation(transform3D);
}  

//_____________________________________________________________________________
HepRotation RootGM::GetRotation(const TGeoMatrix* matrix)
{
  HepTransform3D transform3D = Convert(matrix);
  return BaseVGM::GetRotation(transform3D);
}  

//_____________________________________________________________________________
HepScale3D RootGM::GetScale(const TGeoMatrix* matrix)
{
  HepTransform3D transform3D = Convert(matrix);
  return BaseVGM::GetScale(transform3D);
}  

//_____________________________________________________________________________
bool RootGM::HasReflection(const TGeoMatrix* matrix)
{
  HepScale3D scale = GetScale(matrix);
  return BaseVGM::HasReflection(scale);
}  

//_____________________________________________________________________________
VGM::Axis RootGM::GetAxis(const TGeoPatternFinder* finder)
{
// Checks the finder concrete type and returns the division axis.
// ---

  const TGeoPatternX*  finderX 
    = dynamic_cast<const TGeoPatternX*>(finder);
  if (finderX) return VGM::kXAxis;

  const TGeoPatternY*  finderY 
    = dynamic_cast<const TGeoPatternY*>(finder);
  if (finderY) return VGM::kYAxis;

  const TGeoPatternZ*  finderZ 
    = dynamic_cast<const TGeoPatternZ*>(finder);
  if (finderZ) return VGM::kZAxis;

  const TGeoPatternParaX*  finderParaX 
    = dynamic_cast<const TGeoPatternParaX*>(finder);
  if (finderParaX) return VGM::kXAxis;

  const TGeoPatternParaY*  finderParaY 
    = dynamic_cast<const TGeoPatternParaY*>(finder);
  if (finderParaY) return VGM::kYAxis;

  const TGeoPatternParaZ*  finderParaZ 
    = dynamic_cast<const TGeoPatternParaZ*>(finder);
  if (finderParaZ) return VGM::kZAxis;

  const TGeoPatternTrapZ*  finderTrapZ 
    = dynamic_cast<const TGeoPatternTrapZ*>(finder);
  if (finderTrapZ) return VGM::kZAxis;

  const TGeoPatternCylR* finderR 
    = dynamic_cast<const TGeoPatternCylR*>(finder);
  if (finderR) return VGM::kRho;

  const TGeoPatternCylPhi* finderPhi 
    = dynamic_cast<const TGeoPatternCylPhi*>(finder);
  if (finderPhi) return VGM::kPhi;

  const TGeoPatternSphR* finderSphR 
    = dynamic_cast<const TGeoPatternSphR*>(finder);
  if (finderSphR) return VGM::kRadial3D;

  const TGeoPatternSphPhi* finderSphPhi 
    = dynamic_cast<const TGeoPatternSphPhi*>(finder);
  if (finderSphPhi) return VGM::kPhi;
  
  const TGeoPatternSphTheta* finderSphTheta 
    = dynamic_cast<const TGeoPatternSphTheta*>(finder);
  if (finderSphTheta) return VGM::kSphTheta;
  
  // Not supported shapes:
  // Honeycomb
  
  return  VGM::kUnknownAxis;
 }

//_____________________________________________________________________________
int RootGM::GetAxis(VGM::Axis axis)
{
// Converts VGM axis enum to Root axis number.
// ---

  switch (axis) {
    case VGM::kXAxis:    return 1;
    case VGM::kYAxis:    return 2;
    case VGM::kZAxis:    return 3;
    case VGM::kRho:      return 1;
    case VGM::kPhi:      return 2;
    case VGM::kSphTheta: return 3;
    case VGM::kRadial3D: return 1;
    case VGM::kUnknownAxis: return 0;
  }
  
  return 0;
}    

//_____________________________________________________________________________
double RootGM::GetAxisUnit(VGM::Axis axis)
{
  switch (axis) {
    case VGM::kXAxis:    return RootGM::Units::Length(); break;
    case VGM::kYAxis:    return RootGM::Units::Length(); break;
    case VGM::kZAxis:    return RootGM::Units::Length(); break;
    case VGM::kRho:      return RootGM::Units::Length(); break;
    case VGM::kRadial3D: return RootGM::Units::Length(); break;
    case VGM::kPhi:      return RootGM::Units::Angle();  break;
    case VGM::kUnknownAxis: return 0; break;
    default:  return 0; break;
  }  
}    

//_____________________________________________________________________________
bool RootGM::IsDivided(const TGeoVolume* volume)
{
// Returns true if the volume is divided
// and division is known to VGM.
// ---

  // Check if division is present
  const TGeoPatternFinder* finder = volume->GetFinder();    
  if (!finder) return false;
    
  // Get division axis
  VGM::Axis axis = GetAxis(finder);
  if (axis == VGM::kUnknownAxis) return false;
  
  // Volume can be processed as VGM division
  return true;
}  


