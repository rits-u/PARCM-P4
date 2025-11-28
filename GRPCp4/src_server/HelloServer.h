#pragma once
#include <grpcpp/grpcpp.h>
#include "../proto/generated/hello.grpc.pb.h"

class HelloServer final : public HelloGRPC::Service {

public:
	grpc::Status SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* response);
	void RunServer();

};