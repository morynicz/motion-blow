add_library(aquisition src/Device.cpp src/ImuDevice.cpp src/MeasurementToJsonWriter.cpp src/MeasurementPrinter.cpp src/MeasurementToCsvWriter.cpp)
target_include_directories(aquisition PUBLIC include)
target_link_libraries(aquisition PUBLIC RTIMULib ${Boost_LIBRARIES} messages network)
target_compile_features(aquisition PUBLIC cxx_std_20)

add_executable(aquisitionTests src/QueueTests.cpp)
target_include_directories(aquisitionTests PUBLIC include)
target_link_libraries(aquisitionTests PUBLIC gmock_main gtest gmock)
target_compile_features(aquisitionTests PUBLIC cxx_std_20)

enable_testing()
add_test(NAME aquisitionTests COMMAND aquisitionTests)