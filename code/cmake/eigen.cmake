########################### GTEST
# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(
    eigen
    HG_REPOSITORY "https://bitbucket.org/eigen/eigen/"
    HG_TAG "3.2.10"
    # Disable install step
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

# Specify include dir
ExternalProject_Get_Property(eigen source_dir)
set(EIGEN_INCLUDE_DIR ${source_dir})

#Library
#ExternalProject_Get_Property(rtimulib binary_dir)
#set(RTIMULIB_LIBRARY RTIMULib)
#set(RTIMULIB_LIBRARY_PATH ${binary_dir}/RTIMULib/${CMAKE_FIND_LIBRARY_PREFIXES}${RTIMULIB_LIBRARY}.so)

#add_library(${RTIMULIB_LIBRARY} UNKNOWN IMPORTED)
#set_property(TARGET ${RTIMULIB_LIBRARY} PROPERTY IMPORTED_LOCATION ${RTIMULIB_LIBRARY_PATH})

# ExternalProject_Add_Step(rtimulib GenerateCMakeLists
#   WORKING_DIRECTORY ${source_dir}
#   COMMAND echo "add_subdirectory(RTIMULib)" > CMakeLists.txt
#   COMMENT creating ${binary_dir}/CMakeLists.txt
#   BYPRODUCTS ${binary_dir}/CMakeLists.txt
#   DEPENDEES update 
#   DEPENDERS configure
#   ALWAYS 1
# )
