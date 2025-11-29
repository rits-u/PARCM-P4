cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("GRPCp4")

#set(CMAKE_TOOLCHAIN_FILE "E:/Programs/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
#set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "" FORCE)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(DirectXTex CONFIG REQUIRED)

set(PROTO_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto/generated"
	CACHE PATH "Proto Files" FORCE)

file(GLOB_RECURSE PROTO_SRC "${PROTO_SRC_PATH}/*.cc")
file(GLOB_RECURSE PROTO_HEADERS "${PROTO_SRC_PATH}/*.h")

#add_library(DirectXTexLib STATIC IMPORTED)
##set_target_properties(DirectXTexLib PROPERTIES
 ##   IMPORTED_LOCATION "${VCPKG_ROOT}/installed/x64-windows/lib/DirectXTex.lib"
  #  INTERFACE_INCLUDE_DIRECTORIES "${VCPKG_ROOT}/installed/x64-windows/include"
#)




add_library(DirectXTexLib STATIC IMPORTED)
set_target_properties(DirectXTexLib PROPERTIES
    IMPORTED_LOCATION "E:/Programs/vcpkg/vcpkg/installed/x64-windows/lib/DirectXTex.lib"
    INTERFACE_INCLUDE_DIRECTORIES "E:/Programs/vcpkg/vcpkg/installed/x64-windows/include"
)


#add_library(proto
#    hello.pb.cc
#    hello.grpc.pb.cc
#)

# setup the exe of the server
set (SERVER_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_server
	CACHE PATH "Project Server SRC" FORCE)

file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS
	"${SERVER_SRC_PATH}/*.[ch]pp")

#add_executable (GRPC_Server "${SERVER_SRC_PATH}/GRPCp4.cpp" "${SERVER_SRC_PATH}/GRPCp4.h"
#	${PROTO_SRC} ${PROTO_HEADERS} ${SERVER_SRC})

add_executable (GRPC_Server ${PROTO_SRC} ${PROTO_HEADERS} ${SERVER_SRC})

target_compile_definitions(GRPC_Server PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries(GRPC_Server PUBLIC
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
	tinyobjloader::tinyobjloader
	DirectXTexLib
    d3d11
    dxgi
    dxguid
)



# setup the exe of the client
set (CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_client
	CACHE PATH "Project Client SRC" FORCE)

file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS
	"${CLIENT_SRC_PATH}/*.[ch]pp")

#add_executable (GRPC_Client "${CLIENT_SRC_PATH}/ClientTest.cpp" "${CLIENT_SRC_PATH}/ClientTest.h"
#	${PROTO_SRC} ${PROTO_HEADERS} ${CLIENT_SRC})

add_executable (GRPC_Client ${PROTO_SRC} ${PROTO_HEADERS} ${CLIENT_SRC})

target_compile_definitions(GRPC_Client PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries(GRPC_Client PUBLIC
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
	tinyobjloader::tinyobjloader
	DirectXTexLib
    d3d11
    dxgi
    dxguid
)


#add_custom_command(
#	TARGET GRPC_Client
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_if_different
#			"${CMAKE_CURRENT_SOURCE_DIR}/multi_run.bat"
#			"$<TARGET_FILE_DIR:GRPC_Client>/multi_run.bat"
#)


#include_directories("${CLIENT_SRC_PATH}/Libs/tinyobjloader/include/tiny_obj_loader.h")