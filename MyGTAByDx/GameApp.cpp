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
	//�������ģ��
	m_InputManager = new InputManager();
	if (!m_InputManager->Init(m_hAppInst, m_hMainWnd)) {
		return false;
	}

	//�����ȡģ��
	m_TextureLoader = new TextureLoader();

	if (!m_TextureLoader->Init(m_pd3dDevice.Get(),m_pd3dDeviceContext.Get()))
	{
		return false;
	}

	//��ʼ�����й��ߵ�Shader
	if (!InitShader())
	{
		return false;
	}
	//��ʼ�����й��ߵ�Resource
	if (!InitResource())
	{
		return false;
	}

	//���������
	ShowCursor(false);



	return true;
}

void GameApp::SetRenderPipeLine()
{
	D3DApp::SetRenderPipeLine();
}

void GameApp::UpdateScene(float dt)
{
	//��������

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


	// �������������ƶ�

	LPRECT Tmp=new RECT();
	GetWindowRect(m_hMainWnd, Tmp);
	float CenterX = Tmp->left + m_ClientWidth / 2;
	float CenterY = Tmp->top + m_ClientHeight / 2;

	DfCamera->MouseX(m_InputManager->MouseDX());
	DfCamera->MouseY(m_InputManager->MouseDY());



	//������ڼ���,ÿ֡�����ƶ������ŵ�����
	if (m_bLocKMouse)
	{
		SetCursorPos(CenterX, CenterY);

	}

	//����Tick.
	MyCar->Tick(dt);
	//Ground->Tick(dt);
	
	//������������Tick()�������������ɷ�װ��Tick�У���������..
	DirectX::XMFLOAT3 Pos;
	Pos.x = MyCar->RootComponent->GetWorldPosition().x;
	Pos.y = MyCar->RootComponent->GetWorldPosition().y+10.f;

	Pos.z = MyCar->RootComponent->GetWorldPosition().z;


	DfCamera->SetFocus(Pos);

	//DfCamera->UpdateViewM();
	DfCamera->Tick(dt);


	//��պ� Tick

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

	//ÿ�λ���ǰ������Ӧ��PipeLine״̬
	GOPipeline->SetPipeLine();
	MyCar->Render();
	Ground->Render();


	//��պ�
	SBPipeline->SetPipeLine();
	MySkyBox->Render();



	HR(m_pSwapChain->Present(0, 0));

}

bool GameApp::InitShader()
{
	GOPipeline = new GameObjectPipeLine();
	//�����������豸�Լ�Shader
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

	//��ʼ��С��
	
	MyCar = new Car();
	MyCar->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());


	//��ʼ������
	Ground = new Actor();
	MeshComponent* GroundSurface = new MeshComponent();
	Ground->AddComponent(GroundSurface);
	CubeShape* GroundShape = new CubeShape(10.f, 1.f, 10.f);
	GroundSurface->SetShape(GroundShape);
	GroundSurface->LocalMatrix = XMMatrixTranslation(0.F, -5.F, 0.F);

	GroundSurface->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());
	GroundSurface->Tick(0.f);

	//��ʼ�����

	DfCamera = new ThirdPersonCamera();
	DfCamera->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());



	//��ʼ���������������
	if (!GOPipeline->InitPipeLine()) {
		return false;
	}

	//ͶӰ����Ҫ�ڽ�����ĳ����������󶨵����ߺ�Ż���ִ�У����ֲ���ÿ֡����.
	DfCamera->UpdateProjM();

	//��ʼ����պ�,��Ҫ������ֶ�һ��������и���
	MySkyBox = new SkyBox();
	MySkyBox->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());
	MySkyBox->SetFollowCamera(DfCamera);

	//��ʼ����պй���
	if (!SBPipeline->InitPipeLine()) {
		return false;
	}

	return true;
}

bool GameApp::InitPipeline()
{
	//��ʼ���������ߵ�Pipeline
	GOPipeline->InitPipeLine();
	SBPipeline->InitPipeLine();

	return true;
}

