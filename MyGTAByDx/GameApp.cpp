#include "GameApp.h"
#include "DXUtil.h"
#include "DXTrace.h"

//typedef struct D3D11_INPUT_ELEMENT_DESC
//{
//	LPCSTR SemanticName;
//	UINT SemanticIndex;
//	DXGI_FORMAT Format;
//	UINT InputSlot;
//	UINT AlignedByteOffset;
//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
//	UINT InstanceDataStepRate;
//} 	D3D11_INPUT_ELEMENT_DESC;

//若有多个相同的语义名，则语义索引就是另外一种区分。相同的语义按从上到下所以分别为0,1,2...
const D3D11_INPUT_ELEMENT_DESC VertexPosColor::inputDesc[2] = {
	//format:float3，
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	// float3*4=12
	{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
};


GameApp::GameApp(HINSTANCE hInstance)
	:D3DApp(hInstance)
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

	if (!InitShader())
	{
		return false;
	}
	if (!InitResource())
	{
		return false;
	}
	return true;
}

void GameApp::SetRenderPipeLine()
{
	D3DApp::SetRenderPipeLine();
}

void GameApp::UpdateScene(float dt)
{

}

void GameApp::DrawScene()
{
	assert(m_pd3dDeviceContext);
	assert(m_pSwapChain);
	
	static float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };	// RGBA = (0,0,255,255)
	m_pd3dDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue);
	m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pd3dDeviceContext->Draw(3, 0);
	HR(m_pSwapChain->Present(0, 0));

}

bool GameApp::InitShader()
{
	ComPtr<ID3DBlob> blob;
	
	//create VS
	HR(CreateShaderFromFile(L"HLSL\\Triangle_VS.cso", L"HLSL\\Triangle_VS.hlsl", "main", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));

	//绑定InputLayout
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputDesc, ARRAYSIZE(VertexPosColor::inputDesc), blob->GetBufferPointer(), blob->GetBufferSize(),
		m_pVertexInputLayout.GetAddressOf()));



	HR(CreateShaderFromFile(L"HLSL\\Triangle_PS.cso", L"HLSL\\Triangle_PS.hlsl", "main", "ps_5_0", blob.ReleaseAndGetAddressOf()));

	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

	return true;
}

bool GameApp::InitResource()
{
	using namespace DirectX;
	// 三角形顶点
	VertexPosColor vertices[] = {
		{ XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }
	};

	//设置VertexBufferDesc
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof vbd);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.ByteWidth = sizeof vertices;				//所有顶点的size
	vbd.CPUAccessFlags = 0;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;

	//创建VertexBuffer
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof InitData);
	InitData.pSysMem = vertices;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));


	//IA阶段

	UINT stride = sizeof VertexPosColor;
	UINT offset = 0;

	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->IASetInputLayout(m_pVertexInputLayout.Get());

	m_pd3dDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);




	return true;
}
