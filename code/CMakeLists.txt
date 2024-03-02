cmake_minimum_required(VERSION 3.22)
project(MotionBlow C CXX)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system program_options REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include(FetchContent)
FetchContent_Declare(
        rtimulib
        GIT_REPOSITORY https://github.com/morynicz/RTIMULib2.git
        GIT_TAG master
        SOURCE_SUBDIR RTIMULib
)


FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(rtimulib googletest)

add_subdirectory(messages)
add_subdirectory(network)
add_subdirectory(motion_blow)

# add_executable(motionBlow src/blow.cpp src/Device.cpp src/ImuDevice.cpp)
# target_include_directories(motionBlow PUBLIC include)
# target_link_libraries(motionBlow PUBLIC RTIMULib ${Boost_LIBRARIES} messages network)
# target_compile_features(motionBlow PUBLIC cxx_std_20)

add_executable(blow src/blow.cpp)
target_link_libraries(blow PUBLIC ${Boost_LIBRARIES} messages network motionBlow)
target_compile_features(blow PUBLIC cxx_std_20)

add_executable(server src/srvMain.cpp)
target_compile_features(server PUBLIC cxx_std_20)
target_link_libraries(server PUBLIC ${Boost_LIBRARIES} Threads::Threads network messages)

add_executable(client src/client.cpp )
target_compile_features(client PUBLIC cxx_std_20)
target_link_libraries(client ${Boost_LIBRARIES} Threads::Threads messages motionBlow)

add_executable(ec src/EigenCheck.cpp)
target_include_directories(ec PUBLIC include)
target_link_libraries(ec PUBLIC RTIMULib ${Boost_LIBRARIES} Eigen3::Eigen)
target_compile_features(ec PUBLIC cxx_std_20)

# add_executable(tests src/QueueTests.cpp)
# target_include_directories(tests PUBLIC include)
# target_link_libraries(tests PUBLIC gmock_main gtest gmock)
# target_compile_features(tests PUBLIC cxx_std_20)


enable_testing()

# add_test(NAME MotionBlowTests COMMAND motionBlowTests)