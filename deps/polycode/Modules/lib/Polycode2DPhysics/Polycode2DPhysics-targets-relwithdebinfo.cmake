#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Polycode2DPhysics" for configuration "RelWithDebInfo"
set_property(TARGET Polycode2DPhysics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Polycode2DPhysics PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/Modules/lib/libPolycode2DPhysics.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Polycode2DPhysics )
list(APPEND _IMPORT_CHECK_FILES_FOR_Polycode2DPhysics "${_IMPORT_PREFIX}/Modules/lib/libPolycode2DPhysics.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
