#include "GameApp.h"
#include "DXUtil.h"
#include "DXTrace.h"
#include "Geometry.h"
#include "DDSTextureLoader.h"
#include "BasicShape.h"
#include "Actor.h"
#include "MeshComponent.h"
#include "InputManager.h"
#include "TextureLoader.h"
#include "Car.h"
#include "Camera.h"
#include "PipeLine.h"
#include"SkyBox.h"


GameApp::GameApp(HINSTANCE hInstance)
	:D3DApp(hInstance)
	//,m_ConstantBufferForLit(), m_ConstantBufferForProj(),m_ConstantBufferForScene(),m_ConstantBufferForView()
	//,Cube(nullptr)
	,GOPipeline(nullptr)
	, SBPipeline(nullptr)
	, MySkyBox(nullptr)
{
	m_MainWindowCaption = L"GameApp";
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
	if (!D3DApp::Init())
	{
		return false;
	}
	//输入管理模块
	m_InputManager = new InputManager();
	if (!m_InputManager->Init(m_hAppInst, m_hMainWnd)) {
		return false;
	}

	//纹理读取模块
	m_TextureLoader = new TextureLoader();

	if (!m_TextureLoader->Init(m_pd3dDevice.Get(),m_pd3dDeviceContext.Get()))
	{
		return false;
	}

	//初始化所有管线的Shader
	if (!InitShader())
	{
		return false;
	}
	//初始化所有管线的Resource
	if (!InitResource())
	{
		return false;
	}

	//隐藏鼠标光标
	ShowCursor(false);



	return true;
}

void GameApp::SetRenderPipeLine()
{
	D3DApp::SetRenderPipeLine();
}

void GameApp::UpdateScene(float dt)
{
	//处理输入

	m_InputManager->GetInput();  
	if (m_InputManager->IsKeyDown(DIK_A))
	{
		MyCar->MoveRight(-1);
	}
	if (m_InputManager->IsKeyDown(DIK_D)) {
		MyCar->MoveRight(1);
	}
	if (m_InputManager->IsKeyDown(DIK_W))
	{
		MyCar->MoveForward(1);
	}
	if (m_InputManager->IsKeyDown(DIK_S)) {
		MyCar->MoveForward(-1);
	}
	
	if (m_InputManager->IsKeyDown(DIK_O)) {
		DfCamera->ChangeProjType();
	}


	// 处理相机的鼠标移动

	LPRECT Tmp=new RECT();
	GetWindowRect(m_hMainWnd, Tmp);
	float CenterX = Tmp->left + m_ClientWidth / 2;
	float CenterY = Tmp->top + m_ClientHeight / 2;

	DfCamera->MouseX(m_InputManager->MouseDX());
	DfCamera->MouseY(m_InputManager->MouseDY());



	//如果窗口激活,每帧计算移动后将鼠标放到中心
	if (m_bLocKMouse)
	{
		SetCursorPos(CenterX, CenterY);

	}

	//场景Tick.
	MyCar->Tick(dt);
	//Ground->Tick(dt);
	
	//设置相机与相机Tick()，设置相机这里可封装到Tick中，后续再做..
	DirectX::XMFLOAT3 Pos;
	Pos.x = MyCar->RootComponent->GetWorldPosition().x;
	Pos.y = MyCar->RootComponent->GetWorldPosition().y+10.f;

	Pos.z = MyCar->RootComponent->GetWorldPosition().z;


	DfCamera->SetFocus(Pos);

	//DfCamera->UpdateViewM();
	DfCamera->Tick(dt);


	//天空盒 Tick

	MySkyBox->Tick(dt);

}

void GameApp::DrawScene()
{
	assert(m_pd3dDeviceContext);
	assert(m_pSwapChain);
	
	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,255,255)
	m_pd3dDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), black);
	m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//m_pd3dDeviceContext->DrawIndexed(Cube->m_IndexCount, 0,0);

	//每次绘制前设置相应的PipeLine状态
	GOPipeline->SetPipeLine();
	MyCar->Render();
	Ground->Render();


	//天空盒
	SBPipeline->SetPipeLine();
	MySkyBox->Render();



	HR(m_pSwapChain->Present(0, 0));

}

bool GameApp::InitShader()
{
	GOPipeline = new GameObjectPipeLine();
	//给管线设置设备以及Shader
	if (!GOPipeline->InitResource(m_pd3dDevice.Get(),m_pd3dDeviceContext.Get()))
	{
		return false;
	}

	SBPipeline = new SkyBoxPipeLine();
	if (!SBPipeline->InitResource(m_pd3dDevice.Get(),m_pd3dDeviceContext.Get()))
	{
		return false;

	}

	return true;
}

bool GameApp::InitResource()
{
	using namespace DirectX;

	//初始化小车
	
	MyCar = new Car();
	MyCar->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());


	//初始化地面
	Ground = new Actor();
	MeshComponent* GroundSurface = new MeshComponent();
	Ground->AddComponent(GroundSurface);
	CubeShape* GroundShape = new CubeShape(10.f, 1.f, 10.f);
	GroundSurface->SetShape(GroundShape);
	GroundSurface->LocalMatrix = XMMatrixTranslation(0.F, -5.F, 0.F);

	GroundSurface->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());
	GroundSurface->Tick(0.f);

	//初始化相机

	DfCamera = new ThirdPersonCamera();
	DfCamera->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());



	//初始化场景内物体管线
	if (!GOPipeline->InitPipeLine()) {
		return false;
	}

	//投影矩阵要在将相机的常量缓冲区绑定到管线后才会能执行，但又不必每帧更新.
	DfCamera->UpdateProjM();

	//初始化天空盒,需要传入或手动一个相机进行跟随
	MySkyBox = new SkyBox();
	MySkyBox->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());
	MySkyBox->SetFollowCamera(DfCamera);

	//初始化天空盒管线
	if (!SBPipeline->InitPipeLine()) {
		return false;
	}

	return true;
}

bool GameApp::InitPipeline()
{
	//初始化各个管线的Pipeline
	GOPipeline->InitPipeLine();
	SBPipeline->InitPipeLine();

	return true;
}

