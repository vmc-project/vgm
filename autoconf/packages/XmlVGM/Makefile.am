# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} ${GEANT4_INCLUDE} \
         -I../../../packages/VGM/include \
         -I../../../packages/ClhepVGM/include \
         -I../../../packages/XmlVGM/include

xmlvgmsrc=../../../packages/XmlVGM/source

lib_LTLIBRARIES = libXmlVGM.la

libXmlVGM_la_SOURCES =                        \
	$(xmlvgmsrc)/AGDDExporter.cxx \
	$(xmlvgmsrc)/AGDDWriter.cxx \
	$(xmlvgmsrc)/GDMLExporter.cxx \
	$(xmlvgmsrc)/GDMLWriter.cxx \
	$(xmlvgmsrc)/Maps.cxx \
	$(xmlvgmsrc)/VExporter.cxx \
	$(xmlvgmsrc)/utilities.cxx

xmlvgminc=../../../packages/XmlVGM/include/XmlVGM
xmlvgmincdir = $(includedir)/XmlVGM
xmlvgminc_HEADERS = \
	$(xmlvgminc)/AGDDExporter.h \
	$(xmlvgminc)/AGDDWriter.h \
	$(xmlvgminc)/GDMLExporter.h \
	$(xmlvgminc)/GDMLWriter.h \
	$(xmlvgminc)/IWriter.h \
	$(xmlvgminc)/Maps.h \
	$(xmlvgminc)/VExporter.h \
	$(xmlvgminc)/utilities.h


