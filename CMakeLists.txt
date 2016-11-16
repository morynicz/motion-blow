cmake_minimum_required(VERSION 3.2)
project(MotionBlow C CXX)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system program_options REQUIRED)
include(cmake/gtest.cmake)
include(cmake/RTIMULib.cmake)
include(cmake/clang-cxx-dev-tools.cmake)
include(cmake/eigen.cmake)

add_executable(motionBlow src/blow.cpp)
target_include_directories(motionBlow PUBLIC include ${RTIMULIB_INCLUDE_DIR})
target_link_libraries(motionBlow ${RTIMULIB_LIBRARY} ${Boost_LIBRARIES})
set_property(TARGET motionBlow PROPERTY CXX_STANDARD 14)

add_executable(chat_client src/chat_client.cpp)
target_include_directories(chat_client PUBLIC include)
target_link_libraries(chat_client ${Boost_LIBRARIES} Threads::Threads)
set_property(TARGET chat_client PROPERTY CXX_STANDARD 14)

add_executable(chat_server src/chat_server.cpp)
target_include_directories(chat_server PUBLIC include)
target_link_libraries(chat_server ${Boost_LIBRARIES} Threads::Threads)
set_property(TARGET chat_server PROPERTY CXX_STANDARD 14)

enable_testing()

add_executable(matrixTest test/MatrixTest.cpp src/Matrix.cpp)
target_include_directories(matrixTest PUBLIC include ${GTEST_INCLUDE_DIR})
target_link_libraries(matrixTest ${GTEST_LIBRARY} Threads::Threads)
set_property(TARGET matrixTest PROPERTY CXX_STANDARD 14)

add_executable(rotationMatrixTest test/RotationMatrixTest.cpp src/RotationMatrix.cpp src/Matrix.cpp)
target_include_directories(rotationMatrixTest PUBLIC include ${GTEST_INCLUDE_DIR})
target_link_libraries(rotationMatrixTest ${GTEST_LIBRARY} Threads::Threads)
set_property(TARGET rotationMatrixTest PROPERTY CXX_STANDARD 14)

add_test(MatrixTest matrixTest)
add_test(RotationMatrixTest rotationMatrixTest)
