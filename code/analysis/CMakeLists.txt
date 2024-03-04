add_library(analysis src/Integrator.cpp)
target_include_directories(analysis PUBLIC include)
target_link_libraries(analysis PUBLIC Eigen3::Eigen aquisition)
target_compile_features(analysis PUBLIC cxx_std_20)

add_executable(analysisTests src/IntegratorTests.cpp)
target_link_libraries(analysisTests PUBLIC analysis gmock_main gmock gtest)
target_compile_features(analysisTests PUBLIC cxx_std_20)

enable_testing()
add_test(NAME AnalysisTests COMMAND analysisTests)