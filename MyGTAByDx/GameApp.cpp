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
	:D3DApp(hInstance),m_MVPMatrix()
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
	using namespace DirectX;
	static float phi = 0.0f, theta = 0.0f;
	phi += 0.0001f, theta += 0.00015f;
	m_MVPMatrix.world = XMMatrixTranspose(XMMatrixRotationX(phi) * XMMatrixRotationY(theta));
	// 更新常量缓冲区，让立方体转起来
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dDeviceContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(m_MVPMatrix), &m_MVPMatrix, sizeof(m_MVPMatrix));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffer.Get(), 0);
}

void GameApp::DrawScene()
{
	assert(m_pd3dDeviceContext);
	assert(m_pSwapChain);
	
	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,255,255)
	m_pd3dDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), black);
	m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pd3dDeviceContext->DrawIndexed(36, 0,0);
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
	// 正方体
	VertexPosColor vertices[] = {
	{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) }
	};

	//设置Vertex Buffer Desc 和 Vertex Buffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof vertices;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof InitData);
	InitData.pSysMem = vertices;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));



	// Index数组
	WORD indices[] = {
		// 正面
	0, 1, 2,
	2, 3, 0,
	// 左面
	4, 5, 1,
	1, 0, 4,
	// 顶面
	1, 5, 6,
	6, 2, 1,
	// 背面
	7, 6, 5,
	5, 4, 7,
	// 右面
	3, 2, 6,
	6, 7, 3,
	// 底面
	4, 0, 3,
	3, 7, 4
	};

	// Index Buffer Desc and create

	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof ibd);
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof indices;
	ibd.CPUAccessFlags = 0;

	InitData.pSysMem = indices;
	HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));


	// Constant Buffer
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(MVP);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffer.GetAddressOf()));

	//
	m_MVPMatrix.world = XMMatrixIdentity();
	m_MVPMatrix.view = XMMatrixTranspose(
		XMMatrixLookAtLH(
		XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))
	);

	m_MVPMatrix.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));

	//InitData.pSysMem = &m_MVPMatrix;





	//IA阶段

	UINT stride = sizeof VertexPosColor;
	UINT offset = 0;

	m_pd3dDeviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	m_pd3dDeviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);


	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->IASetInputLayout(m_pVertexInputLayout.Get());

	//VS阶段
	m_pd3dDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dDeviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

	//PS阶段
	m_pd3dDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);




	return true;
}
