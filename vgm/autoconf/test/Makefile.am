# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
#
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} ${ROOT_INCLUDE} ${GEANT4_INCLUDE} \
         -I../../packages/VGM/include \
         -I../..//packages/BaseVGM/include \
         -I../../packages/ClhepVGM/include \
         -I../../packages/XmlVGM/include   \
         -I../../packages/RootGM/include   \
         -I../../packages/Geant4GM/include \
         -I../../test/include

vgm_libs = ../packages/BaseVGM/libBaseVGM.la ../packages/ClhepVGM/libClhepVGM.la \
           ../packages/RootGM/libRootGM.la ../packages/Geant4GM/libGeant4GM.la \
           ../packages/XmlVGM/libXmlVGM.la

ext_links = \
	$(CLHEP_LINK) $(ROOT_LINK) $(GEANT4_LINK) $(XERCES_LINK) $(EXPAT_LINK)


check_PROGRAMS = vgm_test


vgmtestsrc = ../../test/src
vgm_test_SOURCES = ../../test/vgm_test.cc \
	$(vgmtestsrc)/TstDetectorConstruction.cc \
	$(vgmtestsrc)/TstGeometryViaGeant4.cc \
	$(vgmtestsrc)/TstGeometryViaRoot.cc \
	$(vgmtestsrc)/TstGeometryViaVGM.cc \
	$(vgmtestsrc)/TstPhysicsList.cc \
	$(vgmtestsrc)/TstPrimaryGeneratorAction.cc \
	$(vgmtestsrc)/TstPrimaryGeneratorActionMessenger.cc \
	$(vgmtestsrc)/TstRunAction.cc \
	$(vgmtestsrc)/TstSteppingAction.cc \
	$(vgmtestsrc)/TstTrackingAction.cc \
	$(vgmtestsrc)/TstVGeometry.cc

vgm_test_LDADD = $(vgm_libs)
vgm_test_LDFLAGS = $(ext_links)
