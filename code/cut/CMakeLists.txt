add_library(cut src/Integrator.cpp)
target_include_directories(cut PUBLIC include)
target_link_libraries(cut PUBLIC Eigen3::Eigen aquisition)
target_compile_features(cut PUBLIC cxx_std_20)

add_executable(cutTests src/IntegratorTests.cpp)
target_link_libraries(cutTests PUBLIC cut gmock_main gmock gtest)
target_compile_features(cutTests PUBLIC cxx_std_20)

enable_testing()
add_test(NAME CutTests COMMAND cutTests)