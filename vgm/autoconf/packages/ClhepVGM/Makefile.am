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
         -I$(VGM_SOURCE)/packages/ClhepVGM/include 

clhepvgmsrc=$(VGM_SOURCE)/packages/ClhepVGM/source

lib_LTLIBRARIES = libClhepVGM.la

nodist_libClhepVGM_la_SOURCES =                        \
	$(clhepvgmsrc)/Units.cxx \
	$(clhepvgmsrc)/transform.cxx

clhepvgminc=$(VGM_SOURCE)/packages/ClhepVGM/include/ClhepVGM
clhepvgmincdir = $(includedir)/ClhepVGM
nodist_clhepvgminc_HEADERS = \
	$(clhepvgminc)/Units.h \
	$(clhepvgminc)/transform.h

