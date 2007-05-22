# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} \
         -I$(VGM_SOURCE)/packages/VGM/include \
         -I$(VGM_SOURCE)/packages/ClhepVGM/include \
         -I$(VGM_SOURCE)/packages/XmlVGM/include

xmlvgmsrc=$(VGM_SOURCE)/packages/XmlVGM/source

lib_LTLIBRARIES = libXmlVGM.la

nodist_libXmlVGM_la_SOURCES =                        \
	$(xmlvgmsrc)/AGDDExporter.cxx \
	$(xmlvgmsrc)/AGDDWriter.cxx \
	$(xmlvgmsrc)/GDMLExporter.cxx \
	$(xmlvgmsrc)/GDMLWriter.cxx \
	$(xmlvgmsrc)/Maps.cxx \
	$(xmlvgmsrc)/VExporter.cxx \
	$(xmlvgmsrc)/utilities.cxx

xmlvgminc=$(VGM_SOURCE)/packages/XmlVGM/include/XmlVGM
xmlvgmincdir = $(includedir)/XmlVGM
nodist_xmlvgminc_HEADERS = \
	$(xmlvgminc)/AGDDExporter.h \
	$(xmlvgminc)/AGDDWriter.h \
	$(xmlvgminc)/GDMLExporter.h \
	$(xmlvgminc)/GDMLWriter.h \
	$(xmlvgminc)/IWriter.h \
	$(xmlvgminc)/Maps.h \
	$(xmlvgminc)/VExporter.h \
	$(xmlvgminc)/utilities.h


