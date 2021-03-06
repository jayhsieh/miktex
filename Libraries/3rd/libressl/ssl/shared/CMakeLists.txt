## CMakeLists.txt                                       -*- CMake -*-
##
## Copyright (C) 2015-2017 Christian Schenk
## 
## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2, or (at your
## option) any later version.
## 
## This file is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this file; if not, write to the Free Software
## Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
## USA.

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(${libressl_ssl_dll_name}_sources ${ssl_sources})

if(MIKTEX_NATIVE_WINDOWS)
  configure_file(
    ssl.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ssl.rc
  )
  list(APPEND ${libressl_ssl_dll_name}_sources
    ${CMAKE_CURRENT_BINARY_DIR}/ssl.rc
  )
endif()

add_library(${libressl_ssl_dll_name} SHARED ${${libressl_ssl_dll_name}_sources})

set_property(TARGET ${libressl_ssl_dll_name} PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

set_target_properties(${libressl_ssl_dll_name}
  PROPERTIES
    VERSION "${MIKTEX_MAJOR_MINOR_STR}"
    SOVERSION "1"
)

target_include_directories(${libressl_ssl_dll_name}
  PUBLIC
    ${public_include_directories}
)

target_link_libraries(${libressl_ssl_dll_name}
  PRIVATE
    ${libressl_crypto_dll_name}
)

if (MIKTEX_NATIVE_WINDOWS)
  target_link_libraries(${libressl_ssl_dll_name}
    PRIVATE
      Ws2_32.lib)
endif()

rebase(${libressl_ssl_dll_name})

install(TARGETS ${libressl_ssl_dll_name}
  RUNTIME DESTINATION "${MIKTEX_BINARY_DESTINATION_DIR}"
  LIBRARY DESTINATION "${MIKTEX_LIBRARY_DESTINATION_DIR}"
  ARCHIVE DESTINATION "${MIKTEX_LIBRARY_DESTINATION_DIR}"
)
