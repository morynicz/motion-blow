cmake_minimum_required(VERSION 3.2)
project(MotionBlow C CXX)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system program_options REQUIRED)
include(cmake/gtest.cmake)
include(cmake/RTIMULib.cmake)
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

add_executable(ec src/EigenCheck.cpp)
target_include_directories(ec PUBLIC include ${RTIMULIB_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_link_libraries(ec ${RTIMULIB_LIBRARY} ${Boost_LIBRARIES})
set_property(TARGET ec PROPERTY CXX_STANDARD 14)

enable_testing()

set(ALL_CXX_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/include/motion_blow/*.hpp
	${PROJECT_SOURCE_DIR}/src/blow.cpp
	${PROJECT_SOURCE_DIR}/src/EigenCheck.cpp
	)

include(cmake/clang-cxx-dev-tools.cmake)