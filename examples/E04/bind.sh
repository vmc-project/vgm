#!/bin/sh

g++ -I$ROOTSYS/include \
    -I$VGM_INSTALL/packages/VGM/include \
    -I$VGM_INSTALL/packages/BaseVGM/include \
    -I$VGM_INSTALL/packages/RootGM/include \
    -I$VGM_INSTALL/packages/XmlVGM/include \
    -I$CLHEP_BASE_DIR/include \
    -L$VGM_INSTALL/lib/$VGM_SYSTEM -lRootGM -lBaseVGM -lXmlVGM \
    -L$CLHEP_BASE_DIR/lib -lCLHEP \
    `root-config --glibs` -lGeomPainter -lGeom rootgeom.cxx \
    -o rootgeom
    
    
