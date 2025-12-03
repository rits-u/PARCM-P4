#include <grpcpp/grpcpp.h>
#include "../../../proto/generated/scene.pb.h"
#include "../../../proto/generated/scene.grpc.pb.h"

using namespace std;

class SceneLoader {
private:
	std::unique_ptr<SceneGRPC::Stub> stub;


public:
	SceneLoader(std::shared_ptr<grpc::Channel> channel);
	void GetScene(const int& SceneID); 
	std::string StreamObjFile(const int& ModelID);
};