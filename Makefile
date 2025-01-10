################################################################################
######################### User configurable parameters #########################
# filename extensions
CEXTS:=c
ASMEXTS:=s S
CXXEXTS:=cpp c++ cc

# probably shouldn't modify these, but you may need them below
ROOT=.
FWDIR:=$(ROOT)/firmware
BINDIR=$(ROOT)/bin
SRCDIR=$(ROOT)/src
INCDIR=$(ROOT)/include

WARNFLAGS+=
EXTRA_CFLAGS=
EXTRA_CXXFLAGS=

# Set to 1 to enable hot/cold linking
USE_PACKAGE:=1

# Add libraries you do not wish to include in the cold image here
# EXCLUDE_COLD_LIBRARIES:= $(FWDIR)/your_library.a
EXCLUDE_COLD_LIBRARIES:= 

# Set this to 1 to add additional rules to compile your project as a PROS library template
IS_LIBRARY:=0
# TODO: CHANGE THIS!
LIBNAME:=1516X
VERSION:=1.0.0
# EXCLUDE_SRC_FROM_LIB= $(SRCDIR)/unpublishedfile.c
# this line excludes opcontrol.c and similar files
EXCLUDE_SRC_FROM_LIB+=$(foreach file, $(SRCDIR)/main,$(foreach cext,$(CEXTS),$(file).$(cext)) $(foreach cxxext,$(CXXEXTS),$(file).$(cxxext)))

# files that get distributed to every user (beyond your source archive) - add
# whatever files you want here. This line is configured to add all header files
# that are in the the include directory get exported
TEMPLATE_FILES=$(INCDIR)/**/*.h $(INCDIR)/**/*.hpp

USER_HEADERS=$(INCDIR)/screen/*.h $(INCDIR)/*.h $(INCDIR)/robot/*.h

USER_SRC=$(SRCDIR)/**/*.cpp $(SRCDIR)/*.cpp

.DEFAULT_GOAL=quick

################################################################################
################################################################################
########## Nothing below this line should be edited by typical users ###########
-include ./common.mk

# @...||: is a hack to prevent make from failing if the command outputs a non-fail result -> This is because we recieve is a directory error
format-all: format-src format-includes

format-src:
	@clang-format -i $(USER_SRC) --style file ||:

format-includes:
	@clang-format -i $(USER_HEADERS) --style file ||:


lint-all: lint-src lint-includes

lint-src:
	@clang-tidy $(USER_SRC) -checks=-cppcoreguidelines-* --format-style=file ||:
	@echo -e "\033[0;32mNon user-code errors can be ignored.\033[0m They are \033[1;33mnot relevant\033[0m to the user code."

lint-includes:
	@clang-tidy $(USER_HEADERS) -checks=-cppcoreguidelines-* --format-style file ||:
	@echo -e "\033[0;32mNon user-code errors can be ignored.\033[0m They are \033[1;33mnot relevant\033[0m to the user code."



docs:
	@doxygen Doxyfile

# Cleans up the bin/ directory, useful when testing compiler flags
# Watch out for when other files than globals.cpp or main.cpp are changed, as that is unchecked behavior
clean-bin:
	@rm bin/*.cpp.* && rm bin/cold* && rm bin/hot*
	@echo -e "\033[0;32mNow rebuild the program.\033[0m"

	
