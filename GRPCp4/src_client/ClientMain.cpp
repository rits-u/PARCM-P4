#include "ClientTest.h"

int main() {
	HelloClient client(grpc::CreateChannel("localhost:50051",
		grpc::InsecureChannelCredentials()));

	client.SayHello("E.Flash");
	int x;
	std::cin >> x;

	return 0;
}