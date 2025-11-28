#include <grpcpp/grpcpp.h>
#include "../proto/generated/hello.grpc.pb.h"

using namespace std;

class HelloClient {
private:
	std::unique_ptr<HelloGRPC::Stub> stub;


public:
	HelloClient(std::shared_ptr<grpc::Channel> channel);
	void SayHello(const std::string& name);
};