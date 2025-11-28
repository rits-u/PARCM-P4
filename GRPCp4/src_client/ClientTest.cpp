#include "ClientTest.h"

HelloClient::HelloClient(std::shared_ptr<grpc::Channel> channel) : stub(HelloGRPC::NewStub(channel))
{
}

void HelloClient::SayHello(const std::string& name) {
	//load in the request
	HelloRequest request;
	request.set_name(name); //name to show

	//prepare the response
	HelloReply response;
	grpc::ClientContext context;

	//call the server here
	//say hello
	grpc::Status status = stub->SayHello(&context, request, &response);

	//result
	if (status.ok()) {
		std::cout << "Success: " << response.status() << std::endl;
		std::cout << "Message: " << response.msg() << std::endl;
	}
	else {
		std::cout << "Fail" << std::endl;
	}
}