cmake_minimum_required(VERSION 3.5)
project(MotionBlow CXX C)

find_package(Boost REQUIRED program_options)

add_executable(motionBlow src/blow.cpp)
target_include_directories(motionBlow PUBLIC include/motion_blow)
target_link_libraries(motionBlow RTIMULib ${BOOST_LIBRARIES})

