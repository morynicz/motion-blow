add_library(motionBlow src/Device.cpp src/ImuDevice.cpp src/MeasurementToJsonWriter.cpp src/MeasurementPrinter.cpp)
target_include_directories(motionBlow PUBLIC include)
target_link_libraries(motionBlow PUBLIC RTIMULib ${Boost_LIBRARIES} messages network)
target_compile_features(motionBlow PUBLIC cxx_std_20)

add_executable(motionBlowTests src/QueueTests.cpp)
target_include_directories(motionBlowTests PUBLIC include)
target_link_libraries(motionBlowTests PUBLIC gmock_main gtest gmock)
target_compile_features(motionBlowTests PUBLIC cxx_std_20)

enable_testing()
add_test(NAME MotionBlowTests COMMAND motionBlowTests)