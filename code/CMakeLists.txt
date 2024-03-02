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

add_executable(motionBlow src/blow.cpp src/Device.cpp src/ImuDevice.cpp)
target_include_directories(motionBlow PUBLIC include)
target_link_libraries(motionBlow PUBLIC RTIMULib ${Boost_LIBRARIES} messages network)
target_compile_features(motionBlow PUBLIC cxx_std_20)

add_executable(server src/srvMain.cpp)
target_compile_features(server PUBLIC cxx_std_20)
target_link_libraries(server PUBLIC ${Boost_LIBRARIES} Threads::Threads network messages)

add_executable(client src/client.cpp)
target_compile_features(client PUBLIC cxx_std_20)
target_link_libraries(client ${Boost_LIBRARIES} Threads::Threads messages)
# add_executable(chat_client src/chat_client.cpp)
# target_include_directories(chat_client PUBLIC include)
# target_link_libraries(chat_client ${Boost_LIBRARIES} Threads::Threads)
# target_compile_features(chat_client PUBLIC cxx_std_20)

# add_executable(chat_server src/chat_server.cpp)
# target_include_directories(chat_server PUBLIC include)
# target_link_libraries(chat_server ${Boost_LIBRARIES} Threads::Threads)
# target_compile_features(chat_server PUBLIC cxx_std_20)

add_executable(ec src/EigenCheck.cpp)
target_include_directories(ec PUBLIC include)
target_link_libraries(ec PUBLIC rtimulib ${Boost_LIBRARIES} Eigen3::Eigen)
target_compile_features(ec PUBLIC cxx_std_20)

add_executable(tests src/QueueTests.cpp)
target_include_directories(tests PUBLIC include)
target_link_libraries(tests PUBLIC gmock_main gtest gmock)
target_compile_features(tests PUBLIC cxx_std_20)


enable_testing()

set(ALL_CXX_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/include/motion_blow/*.hpp
	${PROJECT_SOURCE_DIR}/src/blow.cpp
	${PROJECT_SOURCE_DIR}/src/EigenCheck.cpp
	)

include(cmake/clang-cxx-dev-tools.cmake)