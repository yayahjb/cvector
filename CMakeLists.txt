######################################################################
#  CMakeLists.txt - cmake build file to create CVector               #
#                                                                    #
# Version 1.0.4 26 November 2014                                     #
# Rev 23 November 2014                                               #
#                                                                    #
#                Herbert J. Bernstein (yayahjb@gmail.com)            #
#                                                                    #
# (C) Copyright 2008 - 2014 Herbert J. Bernstein                     #
#                                                                    #
######################################################################

######################################################################
#                                                                    #
# YOU MAY REDISTRIBUTE THE CVector API UNDER THE TERMS OF THE LGPL  #
#                                                                    #
######################################################################

######################################################################
#                                                                    #
# This library is free software; you can redistribute it and/or      #
# modify it under the terms of the GNU Lesser General Public         #
# License as published by the Free Software Foundation; either       #
# version 2.1 of the License, or (at your option) any later version. #
#                                                                    #
# This library is distributed in the hope that it will be useful,    #
# but WITHOUT ANY WARRANTY; without even the implied warranty of     #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  #
# Lesser General Public License for more details.                    #
#                                                                    #
# You should have received a copy of the GNU Lesser General Public   #
# License along with this library; if not, write to the Free         #
# Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    #
# MA  02110-1301  USA                                                #
#                                                                    #
######################################################################

cmake_minimum_required (VERSION 2.8.7)

project (CVector C)
set(CV_APIVERS,"2.0.1")

#
# Environment Variables
#
set(CV_USE_LOCAL_HEADERS_ENV $ENV{CV_USE_LOCAL_HEADERS})

if (CV_USE_LOCAL_HEADERS_ENV STREQUAL "YES")
  set(COMPILE_DEFINITIONS "USE_LOCAL_HEADERS=1")
endif (CV_USE_LOCAL_HEADERS_ENV STREQUAL "YES")

#
# Directories
#

#
# Directories on the kit side
#
set(CV__SRC       "${CVector_SOURCE_DIR}" )
set(CV__INCLUDE   "${CVector_SOURCE_DIR}" )
set(CV__EXAMPLES  "${CVector_SOURCE_DIR}" )
set(CV__TESTDATA  "${CVector_SOURCE_DIR}" )

#
# Directories on the build side
#
set(CV__BIN       "${CVector_BINARY_DIR}/bin" )
set(CV__LIB       "${CVector_BINARY_DIR}/lib" )

#
# CV_REQUIRE_DIRECTORY -- require directory dir
#
macro(CV_REQUIRE_DIRECTORY dir)
  if (NOT EXISTS "${dir}")
    file(MAKE_DIRECTORY "${dir}")
    MESSAGE("Created directory ${dir}")
  endif (NOT EXISTS "${dir}")
endmacro(CV_REQUIRE_DIRECTORY)

CV_REQUIRE_DIRECTORY(${CV__BIN})
CV_REQUIRE_DIRECTORY(${CV__LIB})

#
# Source files
#
set(
    CV_C_SOURCES
    ${CV__SRC}/CVector.c 
)


set(
    CV_HEADERS
    ${CV__INCLUDE}/CVector.h
)

# Set up the necessary includes

include_directories(
	BEFORE SYSTEM
        ${CV__INCLUDE}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CV__BIN}")

#
#  Build the static and shared CVector libraries
#

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CV__LIB}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CV__LIB}")
add_library(CV_static STATIC ${CV__SRC}/CVector.c)
set_target_properties(CV_static PROPERTIES OUTPUT_NAME "CVector")
set_target_properties(CV_static PROPERTIES LINKER_LANGUAGE C)
set_target_properties(CV_static PROPERTIES SOVERSION "${CV_APIVERSION}")
set(CV_STATIC_LIBRARY_PATH ${CV__LIB}/libCVector${CMAKE_STATIC_LIBRARY_SUFFIX})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CV__LIB}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CV__LIB}")
add_library(CV_shared SHARED  ${CV__SRC}/CVector.c)
set_target_properties(CV_shared PROPERTIES OUTPUT_NAME "CVector")
set_target_properties(CV_shared PROPERTIES LINKER_LANGUAGE C)
set_target_properties(CV_shared PROPERTIES SOVERSION "${CV_APIVERSION}")
set(CV_SHARED_LIBRARY_PATH ${CV__LIB}/libCVector.${CMAKE_SHARED_LIBRARY_SUFFIX})


#
#  C examples
#

# Note: to add a target with multiple sources/dependencies/libraries you must pass a list
# separated by semicolons for the appropriate parameter.
# Note: the math library should be linked in by appending ';m' to the library list here
macro(add_target target source dependencies libraries)
	add_executable(${target} ${source})
	add_dependencies(${target} ${dependencies})
	target_link_libraries(${target} ${libraries})
endmacro()


add_executable(CVectorBasicTest "${CV__EXAMPLES}/CVectorBasicTest.c")
set_target_properties(CVectorBasicTest PROPERTIES LINK_LIBRARIES CV_static)

#
# install
#

install (TARGETS CVectorBasicTest DESTINATION bin)
install (TARGETS CV_static DESTINATION lib)
install (TARGETS CV_shared DESTINATION lib)

#
# test
#
enable_testing()
add_test(CVectorBasicTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CVectorBasicTest CVectorBasicTest.lst)
add_test(cmp-CVectorBasicTest_orig.lst-CVectorBasicTest.lst ${CMAKE_COMMAND} -E compare_files ${CV__TESTDATA}/CVectorBasicTest_orig.lst CVectorBasicTest.lst)



