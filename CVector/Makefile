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
VERSION = 0.1.0

#
# Program to use to create archives
#
AR	= /usr/bin/ar

#
# Program to use to add an index to an archive
#
RANLIB  = /usr/bin/ranlib

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
SRC      = $(ROOT)
INCLUDE  = $(ROOT)
EXAMPLES = $(ROOT)
TESTDATA = $(ROOT)
#INSTALLDIR = /usr/local
INSTALLDIR  = $(HOME)

#
# Include directories
#
INCLUDES = -I$(INCLUDE)


######################################################################
#  You should not need to make modifications below this line         #
######################################################################

#
# Suffixes of files to be used or built
#
.SUFFIXES:	.c .o

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
HEADERS   =  $(INCLUDE)/CVector.h

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
		$(LIB)/libCVector.a \
		$(BIN)/CVectorBasicTest
		
install:  all $(INSTALLDIR) $(INSTALLDIR)/lib $(INSTALLDIR)/include \
          $(INCLUDE) $(HEADERS) $(LIB)/libCVector.a
		  -cp $(INSTALLDIR)/lib/libCVector.a $(INSTALLDIR)/lib/libCVector_old.a
		  cp $(LIB)/libCvector.a $(INSTALLDIR)/lib/libCVector.a
		  -cp $(INSTALLDIR)/include/CVector.h $(INSTALLDIR)/include/CVector_old.h
		  cp $(INCLUDE)/Cvector.h $(INSTALLDIR)/include/CVector.h
		  chmod 644 $(INSTALLDIR)/lib/libCVector.a
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


#
# CVector library
#
$(LIB)/libCVector.a: $(SOURCE) $(HEADERS) $(COMMONDEP)
	$(CC) $(CFLAGS) $(INCLUDES) $(WARNINGS) -c $(SOURCE)
	$(AR) cr $@ *.o
	rm *.o
ifneq ($(RANLIB),)
	$(RANLIB) $@
endif

#
# CVectorBasicTest example program
#
$(BIN)/CVectorBasicTest: $(LIB)/libCVector.a $(EXAMPLES)/CVectorBasicTest.c 
		  $(CC) $(CFLAGS) $(INCLUDES) \
		      $(EXAMPLES)/CVectorBasicTest.c -L$(LIB) \
		  -lCVector -o $@

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
		  @-rm -f $(LIB)/libCVector.a
		  @-rm -f $(BIN)/CVectorBasicTest
		  @-rm -f $(TESTDATA)/CVectorBasicTest.lst
		  
#
# Remove temporary files
#
clean:
	@-rm -f core 
	@-rm -f *.o

#
# Restore to distribution state
#
distclean:	clean empty





