add_library(protos OBJECT protos/Measurement.proto)
target_link_libraries(protos PUBLIC protobuf::libprotobuf)
set(PROTO_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_include_directories(protos PUBLIC $<BUILD_INTERFACE:${PROTO_GENERATED_DIR}>)

protobuf_generate(
    TARGET protos
    LANGUAGE cpp
    IMPORT_DIR ${CMAKE_CURRENT_LIST_DIR}/protos
    PROTOC_OUT_DIR ${PROTO_GENERATED_DIR}
    )

add_library(messages src/Measurement.cpp)
target_include_directories(messages PUBLIC include)
target_link_libraries(messages PRIVATE protos)

enable_testing()

add_executable(messageTests src/MeasurementTests.cpp)
target_link_libraries(messageTests PUBLIC gmock_main gtest gmock messages)