#pragma once
#include "Renderer.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/RenderSystem/VertexBuffer.h"
#include "../GraphicsEngine/RenderSystem/IndexBuffer.h"
#include "../GraphicsEngine/RenderSystem/ConstantBuffer.h"
#include "../GraphicsEngine/RenderSystem/DeviceContext.h"
#include "../Camera/SceneCameraHandler.h"
#include "../Math/VertexMesh.h"
#include "../Mesh/Mesh.h"


class MeshRenderer : public Renderer 
{
public:
	MeshRenderer(const MeshPtr& mesh);
	~MeshRenderer();

public:
	void init() override;
	void setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list) override;
	void update(constant cc, int width, int height, int camIndex) override;
	void draw() override;
	void release() override;

private:
	MeshPtr m_mesh;

private:
	static bool isInitialized;
	static VertexShaderPtr sharedVS;
	static PixelShaderPtr sharedPS;
	VertexBufferPtr vb;
	IndexBufferPtr ib;
	ConstantBufferPtr cb;
};

