#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Leica::smt_logger" for configuration "Debug"
set_property(TARGET Leica::smt_logger APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Leica::smt_logger PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsmt_loggerd.so"
  IMPORTED_SONAME_DEBUG "libsmt_loggerd.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS Leica::smt_logger )
list(APPEND _IMPORT_CHECK_FILES_FOR_Leica::smt_logger "${_IMPORT_PREFIX}/lib/libsmt_loggerd.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
