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


const D3D11_INPUT_ELEMENT_DESC VertexPosNormalTex::inputLayout[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC VertexPosNormalColor::inputLayout[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

GameApp::GameApp(HINSTANCE hInstance)
	:D3DApp(hInstance),m_ConstantBufferForLit(), m_ConstantBufferForProj(),m_ConstantBufferForScene(),m_ConstantBufferForView()
	//,Cube(nullptr)
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

	if (!m_TextureLoader->Init(m_pd3dDevice.Get()))
	{
		return false;
	}

	if (!InitShader())
	{
		return false;
	}
	if (!InitResource())
	{
		return false;
	}


	ShowCursor(false);



	return true;
}

void GameApp::SetRenderPipeLine()
{
	D3DApp::SetRenderPipeLine();
}

void GameApp::UpdateScene(float dt)
{

	m_InputManager->GetInput();  
	//Car->MoveRight(0);
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



	//��ƷTick
	MyCar->Tick(dt);
	Ground->Tick(dt);
	
	//������������Tick()�������������ɷ�װ��Tick�У���������..
	DirectX::XMFLOAT3 Pos;
	Pos.x = MyCar->RootComponent->GetWorldPosition().x;
	Pos.y = MyCar->RootComponent->GetWorldPosition().y+10.f;

	Pos.z = MyCar->RootComponent->GetWorldPosition().z;


	DfCamera->SetFocus(Pos);

	//DfCamera->UpdateViewM();
	DfCamera->Tick(dt);

}

void GameApp::DrawScene()
{
	assert(m_pd3dDeviceContext);
	assert(m_pSwapChain);
	
	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,255,255)
	m_pd3dDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), black);
	m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//m_pd3dDeviceContext->DrawIndexed(Cube->m_IndexCount, 0,0);
	MyCar->Render();
	Ground->Render();
	HR(m_pSwapChain->Present(0, 0));

}

bool GameApp::InitShader()
{
	ComPtr<ID3DBlob> blob;
	
	//create VS
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS.cso", L"HLSL\\Basic_VS.hlsl", "main", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));

	//��InputLayout
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout), blob->GetBufferPointer(), blob->GetBufferSize(),
		m_pVertexInputLayout.GetAddressOf()));


	HR(CreateShaderFromFile(L"HLSL\\Basic_PS.cso", L"HLSL\\Basic_PS.hlsl", "main", "ps_5_0", blob.ReleaseAndGetAddressOf()));

	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

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
	GroundSurface->LocalMatrix = XMMatrixTranslation(0.F, -10.F, 0.F);

	GroundSurface->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());


	//��ʼ�����

	DfCamera = new ThirdPersonCamera();
	DfCamera->InitResource(m_pd3dDevice.Get(), m_pd3dDeviceContext.Get());


	




	//m_ConstantBufferForProj.proj= XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));



	// �ƹ���������õ�CB
	m_DirLight.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_DirLight.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_DirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DirLight.Direction = XMFLOAT3(0.5f, 0.5f, 0.5f);

	m_ConstantBufferForLit.material.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_ConstantBufferForLit.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_ConstantBufferForLit.material.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	m_ConstantBufferForLit.dirLight = m_DirLight;



	if (!InitPipeline()) {
		return false;
	}


	//ͶӰ����Ҫ�ڽ������������󶨵����ߺ�Ż���ִ�У����ֲ���ÿ֡����.
	DfCamera->UpdateProjM();
	return true;
}

bool GameApp::InitPipeline()
{
	//���ó���������
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(m_ConstantBufferForScene);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �½�����VS��PS�ĳ���������
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[0].GetAddressOf()));
	cbd.ByteWidth = sizeof(m_ConstantBufferForView);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[1].GetAddressOf()));
	cbd.ByteWidth = sizeof(m_ConstantBufferForProj);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[2].GetAddressOf()));
	cbd.ByteWidth = sizeof(m_ConstantBufferForLit);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[3].GetAddressOf()));



	// �����ı�İ󶨵�pipeline
	// ���
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dDeviceContext->Map(m_pConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForScene), &m_ConstantBufferForScene, sizeof(ConstantBufferForScene));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffers[0].Get(), 0);


	HR(m_pd3dDeviceContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForView), &m_ConstantBufferForView, sizeof(ConstantBufferForView));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffers[1].Get(), 0);

	HR(m_pd3dDeviceContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForProj), &m_ConstantBufferForProj, sizeof(ConstantBufferForProj));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffers[2].Get(), 0);


	// �ƹ�
	HR(m_pd3dDeviceContext->Map(m_pConstantBuffers[3].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForLit), &m_ConstantBufferForLit, sizeof(ConstantBufferForLit));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffers[3].Get(), 0);


	// ��ʼ����դ��״̬

	 // ******************
	// ��ʼ����դ��״̬
	//
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	HR(m_pd3dDevice->CreateRasterizerState(&rasterizerDesc, m_pRSWireframe.GetAddressOf()));



	//m_pd3dDeviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);


	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->IASetInputLayout(m_pVertexInputLayout.Get());

	//VS�׶�
	m_pd3dDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dDeviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());

	//b1
	m_pd3dDeviceContext->VSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	m_pd3dDeviceContext->VSSetConstantBuffers(2, 1, m_pConstantBuffers[2].GetAddressOf());

	m_pd3dDeviceContext->PSSetConstantBuffers(3, 1, m_pConstantBuffers[3].GetAddressOf());



	//PS�׶�
	m_pd3dDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);


	return true;
}

