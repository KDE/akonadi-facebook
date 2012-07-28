# Find AkonadiSocialUtils
#
# This module defines
#  AKONADISOCIALUTILS_FOUND - whether the qsjon library was found
#  AKONADISOCIALUTILS_LIBRARIES - the qjson library
#  AKONADISOCIALUTILS_INCLUDE_DIR - the include path of the qjson library
#

if (AKONADISOCIALUTILS_INCLUDE_DIR AND AKONADISOCIALUTILS_LIBRARIES)

  # Already in cache
  set (AKONADISOCIALUTILS_FOUND TRUE)

else (AKONADISOCIALUTILS_INCLUDE_DIR AND AKONADISOCIALUTILS_LIBRARIES)

  # use pkg-config to get the values of AKONADISOCIALUTILS_INCLUDE_DIRS
  # and AKONADISOCIALUTILS_LIBRARY_DIRS to add as hints to the find commands.
  include (FindPkgConfig)
  pkg_check_modules (PC_AKONADISOCIALUTILS QUIET libakonadisocialutils)

  find_library (AKONADISOCIALUTILS_LIBRARIES
    NAMES
    akonadisocialutils
    PATHS
    ${PC_AKONADISOCIALUTILS_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
  )

  find_path (AKONADISOCIALUTILS_INCLUDE_DIR
    NAMES
    akonadisocialutils/socialfeeditem.h
    PATHS
    ${PC_AKONADISOCIALUTILS_INCLUDE_DIRS}
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
  )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(AkonadiSocialUtils
                                    REQUIRED_VARS AKONADISOCIALUTILS_LIBRARIES AKONADISOCIALUTILS_INCLUDE_DIR
                                    VERSION_VAR AKONADISOCIALUTILS_VERSION
  )

endif (AKONADISOCIALUTILS_INCLUDE_DIR AND AKONADISOCIALUTILS_LIBRARIES)
