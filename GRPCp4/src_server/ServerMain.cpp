// GRPCp4.cpp : Defines the entry point for the application.
//

#include <grpcpp/grpcpp.h>
#include "../proto/generated/hello.grpc.pb.h"

#include "HelloServer.h"

using namespace std;

//class HelloServerImpl final : public HelloGRPC::Service {
//
//public:
//	grpc::Status SayHello(grpc::ServerContext* context,
//		const HelloRequest* request,
//		HelloReply* response) {
//
//		//print out the content from the client
//		std::cout << "Received message from " << request->name() << std::endl;
//
//		//fill out the reply
//		response->set_status(true);
//		response->set_msg("Hello from server!");
//
//		//send the reply with status flag
//		return grpc::Status::OK;
//	}
//};
//
//void RunServer() {
//	//create a server at this IP
//	std::string serverAdd("0.0.0.0:50051");
//	HelloServerImpl service;
//
//	//server builder
//	grpc::ServerBuilder builder;
//	builder.AddListeningPort(serverAdd, grpc::InsecureServerCredentials());
//	builder.RegisterService(&service);
//
//	//start the server itself
//	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
//	std::cout << "Server listening on " << serverAdd << std::endl;
//
//	//wait for clients
//	server->Wait();
//}





int main()
{
	HelloServer server;
	server.RunServer();

//	asdasd
	return 0;
}
