// $Id$
//
// Class Polycone
// ---------------
// VGM implementation for Root polycone solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_POLYCONE_H
#define ROOT_GM_POLYCONE_H

#include <string>

#include "TGeoPcon.h"

#include "BaseVGM/solids/VPolycone.h"

namespace RootGM {

  class Polycone : public BaseVGM::VPolycone
  {
    public:
      Polycone(const std::string& name, 
               double sphi, double dphi, int nofZPlanes,
               double* z, double* rin, double* rout);
      Polycone(TGeoPcon* polycone);
      virtual ~Polycone();

      // methods
      virtual std::string Name() const;
      virtual double  StartPhi() const;
      virtual double  DeltaPhi() const;
      virtual int     NofZPlanes() const;
      virtual double* ZValues() const;
      virtual double* InnerRadiusValues() const;
      virtual double* OuterRadiusValues() const;

    protected:
      Polycone() : BaseVGM::VPolycone() {}
      Polycone(const Polycone& rhs) : BaseVGM::VPolycone(rhs) {}

    private:
      void CreateBuffers();
  
      static const int fgkMaxNofZPlanes;
      static double*   fgZBuffer;
      static double*   fgRinBuffer;
      static double*   fgRoutBuffer;

      TGeoPcon* fPolycone;
  };

}

#endif //ROOT_GM_POLYCONE_H