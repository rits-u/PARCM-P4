#include "MeshRenderer.h"

//shared
static void* VSBytecode = nullptr;
static size_t VSByteSize = 0;

static void* PSBytecode = nullptr;
static size_t PSByteSize = 0;

bool MeshRenderer::isInitialized = false;
VertexShaderPtr MeshRenderer::sharedVS = nullptr;
PixelShaderPtr MeshRenderer::sharedPS = nullptr;
//VertexBufferPtr MeshRenderer::sharedVB = nullptr;
//IndexBufferPtr MeshRenderer::sharedIB = nullptr;

MeshRenderer::MeshRenderer(const MeshPtr& mesh) : Renderer()
{
	this->m_mesh = mesh;
	this->hasTexture = false;
	this->setSize(1.1f);
	this->setName("Mesh Renderer");
}

MeshRenderer::~MeshRenderer()
{
	this->release();
}

void MeshRenderer::init()
{
	RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();

	std::cout << "Vertices: " << m_mesh->getVertices().size()
		<< ", Indices: " << m_mesh->getIndices().size() << "\n";

	if (!isInitialized)
	{
		//void* bytecode = nullptr;
		//size_t sizeBytecode = 0;

		renderSystem->compileVertexShader(L"..\\..\\..\\src_client\\App\\VertexShader.hlsl", "vsmain", &VSBytecode, &VSByteSize);
	
		
		sharedVS = renderSystem->createVertexShader(VSBytecode, VSByteSize);
		//renderSystem->releaseCompiledShader();
		//vertex buffer
		//sharedVB = renderSystem->createVertexBuffer();
		//sharedVB->Load(m_mesh->getVertices().data(), sizeof(VertexMesh), (UINT)m_mesh->getVertices().size(), bytecode, (UINT)sizeBytecode, renderSystem);
		//renderSystem->releaseCompiledShader();

		//pixel shader
		renderSystem->compilePixelShader(L"..\\..\\..\\src_client\\App\\PixelShader.hlsl", "psmain", &PSBytecode, &PSByteSize);
		sharedPS = renderSystem->createPixelShader(PSBytecode, PSByteSize);


		//index buffer
		//sharedIB = renderSystem->createIndexBuffer();
		//sharedIB->Load(m_mesh->getIndices().data(), (UINT)m_mesh->getIndices().size(), renderSystem);
		isInitialized = true;
	
	}

	this->vb = renderSystem->createVertexBuffer();
	this->vb->Load(m_mesh->getVertices().data(), sizeof(VertexMesh),(UINT)m_mesh->getVertices().size(), VSBytecode, (UINT)VSByteSize, renderSystem);

	this->ib = renderSystem->createIndexBuffer();
	this->ib->Load(m_mesh->getIndices().data(),(UINT)m_mesh->getIndices().size(), renderSystem);

	constant cc;
	this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
	this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);


	//std::cout << "mesh renderer init ok" << std::endl;

	renderSystem->releaseCompiledShader();
	
}

//void MeshRenderer::init()
//{
//    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
//
//    // Debug info
//    std::cout << "Initializing MeshRenderer: Vertices="
//        << m_mesh->getVertices().size()
//        << ", Indices=" << m_mesh->getIndices().size()
//        << std::endl;
//
//    // ---------------- Compile shared shaders once ----------------
//    if (!isInitialized)
//    {
//        // Vertex Shader
//        HRESULT hr = renderSystem->compileVertexShader(
//            L"..\\..\\..\\src_client\\App\\VertexShader.hlsl",
//            "vsmain",
//            &VSBytecode,
//            &VSByteSize
//        );
//        if (FAILED(hr) || !VSBytecode)
//            throw std::runtime_error("Vertex shader compilation failed!");
//        sharedVS = renderSystem->createVertexShader(VSBytecode, VSByteSize);
//      //  renderSystem->releaseCompiledShader();
//
//        // Pixel Shader
//        hr = renderSystem->compilePixelShader(
//            L"..\\..\\..\\src_client\\App\\PixelShader.hlsl",
//            "psmain",
//            &PSBytecode,
//            &PSByteSize
//        );
//        if (FAILED(hr) || !PSBytecode)
//            throw std::runtime_error("Pixel shader compilation failed!");
//        sharedPS = renderSystem->createPixelShader(PSBytecode, PSByteSize);
//    
//
//        isInitialized = true;
//    }
//
//    // ---------------- Per-mesh vertex buffer ----------------
//    if (!m_mesh->getVertices().empty())
//    {
//        this->vb = renderSystem->createVertexBuffer();
//        this->vb->Load(
//            m_mesh->getVertices().data(),
//            sizeof(VertexMesh),
//            static_cast<UINT>(m_mesh->getVertices().size()),
//            VSBytecode,      // Use vertex shader bytecode for input layout
//            static_cast<UINT>(VSByteSize),
//            renderSystem
//        );
//    }
//    else
//    {
//        std::cout << "Warning: Mesh has no vertices!" << std::endl;
//    }
//
//    //// ---------------- Per-mesh index buffer ----------------
//    //if (!m_mesh->getIndices().empty())
//    //{
//    //    this->ib = renderSystem->createIndexBuffer();
//    //    this->ib->Load(
//    //        m_mesh->getIndices().data(),
//    //        static_cast<UINT>(m_mesh->getIndices().size()),
//    //        renderSystem
//    //    );
//    //}
//    //else
//    //{
//    //    std::cout << "Warning: Mesh has no indices!" << std::endl;
//    //}
//
//    //// ---------------- Constant buffer ----------------
//    //constant cc{};
//    //this->cb = renderSystem->createConstantBuffer(&cc, sizeof(constant));
//
//    //// ---------------- Set debug layer ----------------
//    //if (this->getOwner())
//    //    this->getOwner()->setLayer(this->getOwner()->getLayer() | Layer::DEBUG);
//
//    //std::cout << "MeshRenderer initialized successfully." << std::endl;
//
//    renderSystem->releaseCompiledShader();
//}



void MeshRenderer::setUpVerticesAndIndices(vertex* vertex_list, unsigned int* index_list)
{
}

void MeshRenderer::update(constant cc, int width, int height, int camIndex)
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	cc.m_world = this->getOwner()->getWorldMatrix();

	Camera* cam = SceneCameraHandler::get()->getCameraByIndex(camIndex);
	if (cam->cullingMask & Layer::DEBUG)
	{
		cc.useWireColor = 1.0f;
	}
	else {
		cc.useWireColor = 0.0f;
	}

	if (cam->cullingMask & Layer::UI)
	{
		cc.m_view.setIdentity();
		cc.m_proj.setOrthoLH((float)width / 2.0f, (float)height / 2.0f, -1.0f, 1.0f);
	}
	else
	{
		cc.m_view = cam->getViewMatrix();
		cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(width / (float)height)), 0.1f, 100.0f);
	}

	cc.useTexture = hasTexture;

	this->cb->update(deviceContext, &cc);
}

void MeshRenderer::draw()
{
	DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();

	deviceContext->setConstantBuffer(sharedVS, this->cb);
	deviceContext->setConstantBuffer(sharedPS, this->cb);

	deviceContext->setVertexShader(sharedVS);
	deviceContext->setPixelShader(sharedPS);

	if (hasTexture)
		deviceContext->setTexture(sharedPS, this->getTexture());

	deviceContext->setIndexBuffer(ib);
	deviceContext->setVertexBuffer(vb);

//	std::cout << "draw model" << std::endl;

	deviceContext->drawIndexedTriangleList(ib->getSizeIndexList(), 0, 0);
}

void MeshRenderer::release()
{
	sharedVS.reset();
	sharedPS.reset();
}
