cmake_minimum_required(VERSION 3.9)
project(ECDH)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")
option(BUILD_TESTS "Set to ON to build tests" ON)


add_compile_options(-fPIC)

# find dependencies
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake")
find_package(GMP REQUIRED)
find_package(GMPXX REQUIRED)
find_package(OpenSSL REQUIRED)

message("OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message("OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

#-I
include_directories("/usr/local/include"
        ${PROJECT_SOURCE_DIR}/ecc/include
        ${PROJECT_SOURCE_DIR}
        ${OPENSSL_INCLUDE_DIR})

# 添加需要链接的库文件路径
link_libraries(${OPENSSL_LIBRARIES})

# 添加需要链接的库文件目录 -L
#link_directories()

aux_source_directory(${PROJECT_SOURCE_DIR}/ecc/src SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/proto/src PROTO_SRC)
message("sub after2 SRC PATH is " ${PROTO_SRC})


# add pybind11
add_subdirectory(extern/pybind11)
pybind11_add_module(_ecdh_lib python/cpp/pybind.cpp)

# protobuf
# protobuf
find_package(Protobuf REQUIRED)
message("Protobuf_INCLUDE_DIRS: ${Protobuf_INCLUDE_DIRS}")
message("Protobuf_LIBRARIES: ${Protobuf_LIBRARIES}")
include_directories(${Protobuf_INCLUDE_DIRS})

add_subdirectory(proto)

# add src
add_library(_ecc_src ${SRC} ${PROTO_SRC})
target_link_libraries(_ecc_src ${LIBGMP_LIBRARIES}
        ${LIBGMPXX_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${Protobuf_LIBRARIES})

target_link_libraries(_ecdh_lib PRIVATE _ecc_src)

# add exec
add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp "${SRC}" "${PROTO_SRC}")
target_link_libraries(main
        ${LIBGMP_LIBRARIES}
        ${LIBGMPXX_LIBRARIES}
        ${Protobuf_LIBRARIES})
