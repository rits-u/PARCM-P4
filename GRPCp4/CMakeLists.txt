cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("GRPCp4")

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto/generated"
	CACHE PATH "Proto Files" FORCE)

file(GLOB_RECURSE PROTO_SRC "${PROTO_SRC_PATH}/*.cc")
file(GLOB_RECURSE PROTO_HEADERS "${PROTO_SRC_PATH}/*.h")



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
)


#add_custom_command(
#	TARGET GRPC_Client
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_if_different
#			"${CMAKE_CURRENT_SOURCE_DIR}/multi_run.bat"
#			"$<TARGET_FILE_DIR:GRPC_Client>/multi_run.bat"
#)