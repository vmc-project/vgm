# $Id$
# Based on G4 makefiles

MAKEFLAGS= --no-print-directory

SUBDIR = BaseVGM/source XmlVGM/source

ifeq ($(VGM_NO_CLHEP),)
ifneq ($(CLHEP_BASE_DIR),)
SUBDIR += ClhepVGM/source
endif
endif

ifeq ($(VGM_NO_GEANT4),)
ifneq ($(G4INSTALL),)
SUBDIR += Geant4GM/source
endif
endif

ifeq ($(VGM_NO_ROOT),)
ifneq ($(ROOTSYS),)
SUBDIR += RootGM/source 
endif
endif

ifndef VGM_INSTALL
  VGM_INSTALL = ..
endif

.PHONY: global granular clean_libs clean_dicts clean clean_all

global:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) global); done;:

granular:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE)); done;:
	
clean_libs:
	@echo Removing all libraries ...
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) clean_libs); done

clean:
	@echo Removing current $(VGM_SYSTEM) installation ...
	@rm -rf $(VGM_TMPDIR)
	@rm -rf $(VGM_LIBDIR)
	@rm -rf $(VGM_BINDIR)
	@rm -rf $(VGM_INCLUDE)
	@rm -rf $(VGM_INSTALL)/source/*/*/*Cint*
ifdef CFRONT
	@rm -rf $(VGM_TREP)
endif

# Pay _extremely_ attention before executing the following target !!
#
clean_all:
	@echo Removing all installations ...
	@echo Removing $(VGM_TMP) ...
	@rm -rf $(VGM_TMP)
	@echo Removing $(VGM_LIB) ...
	@rm -rf $(VGM_LIB)
	@echo Removing $(VGM_BIN) ...
	@rm -rf $(VGM_BIN)
	@echo Removing $(VGM_INCLUDE) ...
	@rm -rf $(VGM_INCLUDE)
