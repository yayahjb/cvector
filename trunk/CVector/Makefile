#
#  Makefile
#  CVector
#
#  Created by Herbert J. Bernstein on 12/03/08.
#  Copyright 2008 Herbert J. Bernstein. All rights reserved.
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
RELEASE = 1.0


#
# Compiler and compilation flags
#
CC	= gcc
CFLAGS  = -g -O2  -Wall -ansi -pedantic

#
# Directories
#
ROOT     = .
LIB      = $(ROOT)/lib
BIN      = $(ROOT)/bin
LIBTOOL  = $(ROOT)/libtool
SRC      = $(ROOT)
INC      = $(ROOT)
EXAMPLES = $(ROOT)
TESTDATA = $(ROOT)
#INSTALLDIR = /usr/local
INSTALLDIR  = $(HOME)

#
# Include directories
#
INCLUDES = -I$(INC)


######################################################################
#  You should not need to make modifications below this line         #
######################################################################

#
# Suffixes of files to be used or built
#
.SUFFIXES:	.c .o .lo .la

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
	@echo ' that the C compiler name and flags are correct:'
	@echo ' '
	@echo ' The current values are:'
	@echo ' '
	@echo '   $(CC) $(CFLAGS)'
	@echo ' '
	@echo ' Before installing the CBF library and example programs, check'
	@echo ' that the install directory is correct:'
	@echo ' '
	@echo ' The current value :'
	@echo ' '
	@echo '   $(INSTALLDIR) '	
	@echo ' '
	@echo ' To compile the CBF library and example programs type:'
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
		$(BIN)/libtool \
		$(LIB)/libCVector.la \
		$(BIN)/CVectorBasicTest
		
install:  all $(INSTALLDIR) $(INSTALLDIR)/lib $(INSTALLDIR)/include \
          $(INC) $(LIB)/libCVector.la  $(INC)/CVector.h
		  -$(BIN)/libtool cp $(INSTALLDIR)/lib/libCVector.la $(INSTALLDIR)/lib/libCVector_old.la
		  $(BIN)/libtool --mode=finish $(LIB)/libCVector.la
		  $(BIN)/libtool cp $(LIB)/libCVector.la $(INSTALLDIR)/lib/libCVector.la
		  $(BIN)/libtool --mode=finish $(INSTALLDIR)/lib/libCVector.la
		  -cp $(INSTALLDIR)/include/CVector.h $(INSTALLDIR)/include/CVector_old.h
		  cp $(INC)/CVector.h $(INSTALLDIR)/include/CVector.h
		  chmod 644 $(INSTALLDIR)/include/CVector.h
		  
#
# Directories
#
$(INSTALLDIR):
	mkdir -p $(INSTALLDIR)

$(INSTALLDIR)/lib:  $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/lib

$(INSTALLDIR)/bin:  $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/bin

$(INSTALLDIR)/include:  $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/include
	

$(LIB):
	mkdir $(LIB)

$(BIN):
	mkdir $(BIN)

$(BIN)/libtool:
		(CC=$(CC); cd $(LIBTOOL); ./build_libtool.sh; mv ./libtool ../$(BIN)/libtool)

#
# CVector library
#
$(LIB)/libCVector.la: $(SOURCE) $(HEADERS) $(COMMONDEP) $(BIN)/libtool
	$(BIN)/libtool --mode=compile $(CC) $(CFLAGS) $(INCLUDES) $(WARNINGS) -c $(SOURCE)
	$(BIN)/libtool --mode=link  $(CC) -version-info $(VERSION) -release $(RELEASE) -rpath $(INSTALLDIR)/lib -o $(LIB)/libCVector.la *.lo 


#
# CVectorBasicTest example program
#
$(BIN)/CVectorBasicTest: $(LIB)/libCVector.la $(EXAMPLES)/CVectorBasicTest.c 
		  $(BIN)/libtool $(CC) $(CFLAGS) $(INCLUDES) \
		      $(EXAMPLES)/CVectorBasicTest.c $(LIB)/libCVector.la \
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
	@-rm -f *.lo

#
# Restore to distribution state
#
distclean:	clean empty





