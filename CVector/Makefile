#
#  Makefile
#  CVector
#
#  Created by Herbert J. Bernstein on 12/03/08.
#  Copyright 2008 Herbert J. Bernstein. All rights reserved.
#  rev 13 Jan 09 -- HJB
#
#


#**********************************************************************
#*                                                                    *
#* YOU MAY REDISTRIBUTE THE CVector API UNDER THE TERMS OF THE LGPL   *
#*                                                                    *
#**********************************************************************/

#************************* LGPL NOTICES *******************************
#*                                                                    *
#* This library is free software; you can redistribute it and/or      *
#* modify it under the terms of the GNU Lesser General Public         *
#* License as published by the Free Software Foundation; either       *
#* version 2.1 of the License, or (at your option) any later version. *
#*                                                                    *
#* This library is distributed in the hope that it will be useful,    *
#* but WITHOUT ANY WARRANTY; without even the implied warranty of     *
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
#* Lesser General Public License for more details.                    *
#*                                                                    *
#* You should have received a copy of the GNU Lesser General Public   *
#* License along with this library; if not, write to the Free         *
#* Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    *
#* MA  02110-1301  USA                                                *
#*                                                                    *
#**********************************************************************/

# Version string
VERSION = 1:0:1
RELEASE = 1.0.1


#
# Compiler and compilation flags
#
CC	= gcc
ifneq ($(MSYSTEM),MINGW32)
CFLAGS  = -g -O2  -Wall -ansi -pedantic
else
CFLAGS  = -g -O2 -Wall
endif


#
# libtool path if system default is not suitable
#
#LIBTOOL = $(HOME)/bin/libtool
ifndef LIBTOOL
  LIBTOOL = libtool
endif

#
# If local headers must be quoted uncomment the next line
#
#USE_LOCAL_HEADERS = 1


#
# Directories
#
ROOT     = .
LIB      = $(ROOT)/lib
BIN      = $(ROOT)/bin
SRC      = $(ROOT)
INC      = $(ROOT)
EXAMPLES = $(ROOT)
TESTDATA = $(ROOT)
ifndef INSTALL_PREFIX
INSTALL_PREFIX = /usr/local
#INSTALL_PREFIX  = $(HOME)
endif

#
# Include directories
#
ifdef USE_LOCAL_HEADERS
INCLUDES = -DUSE_LOCAL_HEADERS
else
INCLUDES = -I$(INC)
endif

COMPILE_COMMAND        =  $(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(INCLUDES) $(WARNINGS) -c
LIBRARY_LINK_COMMAND   =  $(LIBTOOL) --mode=link  $(CC) -version-info $(VERSION) -release $(RELEASE) -no-undefined -rpath $(INSTALL_PREFIX)/lib
BUILD_COMMAND_LOCAL    =  $(LIBTOOL) --mode=link $(CC) $(CFLAGS) $(INCLUDES)
BUILD_COMMAND_DYNAMIC  =  $(LIBTOOL) --mode=link $(CC) $(CFLAGS) -shared -I $(INSTALL_PREFIX)/include
BUILD_COMMAND_STATIC   =  $(LIBTOOL) --mode=link $(CC) $(CFLAGS) -static -I $(INSTALL_PREFIX)/include
INSTALL_COMMAND        =  $(LIBTOOL) --mode=install cp
INSTALL_FINISH_COMMAND =  $(LIBTOOL) --mode=finish

OBJ_EXT                =  lo
LIB_EXT                =  la

######################################################################
#  You should not need to make modifications below this line         #
######################################################################

#
# Suffixes of files to be used or built
#
.SUFFIXES:	.c .$(OBJ_EXT) .$(LIB_EXT)

#
# Common dependencies
#
COMMONDEP = Makefile

#
# Source files
#
SOURCE   =  $(SRC)/CVector.c

#
# Header files
#
HEADERS   =  $(INC)/CVector.h

# Default: instructions
#
default:
	@echo ' '
	@echo '***************************************************************'
	@echo ' '
	@echo ' PLEASE READ README_CVector.txt and lgpl.txt'
	@echo ' '
	@echo ' Before making the CVector library and example programs, check'
	@echo ' that the chosen settings are correct'
	@echo ' '
	@echo ' The current compile command is:'
	@echo ' '
	@echo '   $(COMPILE_COMMAND)'
	@echo ' '
	@echo ' The current library link command is:'
	@echo ' '
	@echo '   $(LIBRARY_LINK_COMMAND)'
	@echo ' '
	@echo ' The current library local, dynamic and static build commands are:'
	@echo ' '
	@echo '   $(BUILD_COMMAND_LOCAL)'
	@echo '   $(BUILD_COMMAND_DYNAMIC)'
	@echo '   $(BUILD_COMMAND_STATIC)'
	@echo ' '
	@echo ' Before installing the CVector library and example programs, check'
	@echo ' that the install directory and install commands are correct:'
	@echo ' '
	@echo ' The current values are :'
	@echo ' '
	@echo '   $(INSTALL_PREFIX) '	
	@echo '   $(INSTALL_COMMAND) '	
	@echo '   $(INSTALL_FINISH) '	
	@echo ' '
	@echo ' To compile the CVector library and example programs type:'
	@echo ' '
	@echo '   make clean'
	@echo '   make all'
	@echo ' '
	@echo ' To run a set of tests type:'
	@echo ' '
	@echo '   make tests'
	@echo ' '
	@echo ' To clean up the directories type:'
	@echo ' '
	@echo '   make clean'
	@echo ' '
	@echo ' To install the library and binaries type:'
	@echo ' '
	@echo '   make install'
	@echo ' '
	@echo '***************************************************************'
	@echo ' '

#
# Compile the library and examples
#
all:	$(LIB) $(BIN) $(SOURCE) $(HEADERS) \
		$(LIB)/libCVector.$(LIB_EXT) \
		$(BIN)/CVectorBasicTest
		
install:  all $(INSTALL_PREFIX) $(INSTALL_PREFIX)/lib $(INSTALL_PREFIX)/include \
          $(INC) $(LIB)/libCVector.$(LIB_EXT)  $(INC)/CVector.h
		  $(INSTALL_COMMAND) $(LIB)/libCVector.$(LIB_EXT) $(INSTALL_PREFIX)/lib/libCVector.$(LIB_EXT)
		  $(INSTALL_FINISH_COMMAND) $(INSTALL_PREFIX)/lib/libCVector.$(LIB_EXT)
		  -cp $(INSTALL_PREFIX)/include/CVector.h $(INSTALL_PREFIX)/include/CVector_old.h
		  cp $(INC)/CVector.h $(INSTALL_PREFIX)/include/CVector.h
		  chmod 644 $(INSTALL_PREFIX)/include/CVector.h
		  echo "Testing final install dynamic"
		  $(BUILD_COMMAND_DYNAMIC)  $(EXAMPLES)/CVectorBasicTest.c \
		  -L$INSTALLPREFIX)/lib -lCVector -o $(BIN)/CVectorBasicTest_dynamic
		  $(BIN)/CVectorBasicTest_dynamic > $(TESTDATA)/CVectorBasicTest_dynamic.lst
		  diff -b -c $(TESTDATA)/CVectorBasicTest_orig.lst \
		    $(TESTDATA)/CVectorBasicTest_dynamic.lst
		  echo "Testing final install static"
		  $(BUILD_COMMAND_STATIC) $(EXAMPLES)/CVectorBasicTest.c \
		  -L$INSTALLPREFIX)/lib -lCVector -o $(BIN)/CVectorBasicTest_static
		  $(BIN)/CVectorBasicTest_static > $(TESTDATA)/CVectorBasicTest_static.lst
		  diff -b -c $(TESTDATA)/CVectorBasicTest_orig.lst \
		    $(TESTDATA)/CVectorBasicTest_static.lst
			
		  
		  
#
# Directories
#
$(INSTALL_PREFIX):
	mkdir -p $(INSTALL_PREFIX)

$(INSTALL_PREFIX)/lib:  $(INSTALL_PREFIX)
	mkdir -p $(INSTALL_PREFIX)/lib

$(INSTALL_PREFIX)/bin:  $(INSTALL_PREFIX)
	mkdir -p $(INSTALL_PREFIX)/bin

$(INSTALL_PREFIX)/include:  $(INSTALL_PREFIX)
	mkdir -p $(INSTALL_PREFIX)/include
	

$(LIB):
	mkdir $(LIB)

$(BIN):
	mkdir $(BIN)

#
# CVector library
#
$(LIB)/libCVector.$(LIB_EXT): $(SOURCE) $(HEADERS) $(COMMONDEP)
	$(COMPILE_COMMAND) -c $(SOURCE)
	$(LIBRARY_LINK_COMMAND) -o $(LIB)/libCVector.$(LIB_EXT) *.$(OBJ_EXT) 

#
# CVectorBasicTest example program
#
$(BIN)/CVectorBasicTest: $(LIB)/libCVector.$(LIB_EXT) $(EXAMPLES)/CVectorBasicTest.c 
	$(BUILD_COMMAND_LOCAL) $(EXAMPLES)/CVectorBasicTest.c $(LIB)/libCVector.$(LIB_EXT) \
		      -o $@

#
# Tests
#
tests:		$(LIB) $(BIN) $(BIN)/CVectorBasicTest \
				$(TESTDATA)/CVectorBasicTest_orig.lst
			$(BIN)/CVectorBasicTest > $(TESTDATA)/CVectorBasicTest.lst
			diff -b -c $(TESTDATA)/CVectorBasicTest_orig.lst \
				$(TESTDATA)/CVectorBasicTest.lst

#
# Remove all non-source files
#
empty:
		  @-rm -rf $(LIB)
		  @-rm -rf $(BIN)
		  @-rm -f $(TESTDATA)/CVectorBasicTest.lst
		  
#
# Remove temporary files
#
clean:
	@-rm -f core 
	@-rm -f *.o
	@-rm -f *.$(OBJ_EXT)
	@-rm -f *.c.*
	@-rm -rf .libs


#
# Restore to distribution state
#
distclean:	clean empty





