add_library(network src/TcpServer.cpp)
target_include_directories(network PUBLIC include)
target_compile_features(network PUBLIC cxx_std_20)
