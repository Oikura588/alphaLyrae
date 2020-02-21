#include "PipeLine.h"
#include "DXTrace.h"

using namespace DirectX;
PipeLine::PipeLine()
	:m_pd3dDevice(nullptr)
	,m_pd3dDeviceContext(nullptr)
{
}

bool PipeLine::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pd3dDeviceContext = pd3dDeviceContext;


	InitShader();
	return true;
}

GameObjectPipeLine::GameObjectPipeLine()
	:m_ConstantBufferForLit(), m_ConstantBufferForProj(), m_ConstantBufferForScene(), m_ConstantBufferForView()
{
}

bool GameObjectPipeLine::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	PipeLine::InitResource(pd3dDevice, pd3dDeviceContext);

	// ���õƹ������
	m_DirLight.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_DirLight.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_DirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DirLight.Direction = XMFLOAT3(0.5f, 0.5f, 0.5f);


	m_ConstantBufferForLit.material.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_ConstantBufferForLit.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_ConstantBufferForLit.material.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	m_ConstantBufferForLit.dirLight = m_DirLight;


	// ���ò�����

	return true;
}

bool GameObjectPipeLine::InitPipeLine()
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

	 // ******************
	// ��ʼ����դ��״̬
	//
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	HR(m_pd3dDevice->CreateRasterizerState(&rasterizerDesc, m_pRSWireframe.GetAddressOf()));


	// ��ʼ��������
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));

	





	SetPipeLine();
	return true;
}

bool GameObjectPipeLine::InitShader()
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

void GameObjectPipeLine::SetPipeLine()
{

	// �����ı�İ󶨵�pipeline
	D3D11_MAPPED_SUBRESOURCE mappedData;

	// �ƹ�
	HR(m_pd3dDeviceContext->Map(m_pConstantBuffers[3].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ConstantBufferForLit), &m_ConstantBufferForLit, sizeof(ConstantBufferForLit));
	m_pd3dDeviceContext->Unmap(m_pConstantBuffers[3].Get(), 0);

	//���ù���״̬
	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->IASetInputLayout(m_pVertexInputLayout.Get());

	//VS�׶�
	m_pd3dDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dDeviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());

	//PS�׶�
	m_pd3dDeviceContext->VSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	m_pd3dDeviceContext->VSSetConstantBuffers(2, 1, m_pConstantBuffers[2].GetAddressOf());

	m_pd3dDeviceContext->PSSetConstantBuffers(3, 1, m_pConstantBuffers[3].GetAddressOf());
	m_pd3dDeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

	m_pd3dDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);


}

SkyBoxPipeLine::SkyBoxPipeLine()
	:PipeLine()
	,m_ConstantBufferMVP()
{
}

bool SkyBoxPipeLine::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{
	PipeLine::InitResource(pd3dDevice, pd3dDeviceContext);

	return true;
}

bool SkyBoxPipeLine::InitShader()
{
	ComPtr<ID3DBlob> blob;

	//create VS
	HR(CreateShaderFromFile(L"HLSL\\Sky_VS.cso", L"HLSL\\Sky_VS.hlsl", "main", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));

	//��InputLayout
	HR(m_pd3dDevice->CreateInputLayout(VertexPos::inputLayout, ARRAYSIZE(VertexPos::inputLayout), blob->GetBufferPointer(), blob->GetBufferSize(),
		m_pVertexInputLayout.GetAddressOf()));


	HR(CreateShaderFromFile(L"HLSL\\Sky_PS.cso", L"HLSL\\Sky_PS.hlsl", "main", "ps_5_0", blob.ReleaseAndGetAddressOf()));

	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

	return true;

}

bool SkyBoxPipeLine::InitPipeLine()
{
	//���ó���������
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(m_ConstantBufferMVP);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �½�����VS�ĳ���������
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffer.GetAddressOf()));
	

	// �ޱ����޳�ģʽ
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.DepthClipEnable = true;
	HR(m_pd3dDevice->CreateRasterizerState(&rasterizerDesc, m_pRSNoCull.GetAddressOf()));




	// ******************
	// ��ʼ�����/ģ��״̬
	//
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

	// ����ʹ�����ֵһ�µ����ؽ����滻�����/ģ��״̬
	// ��״̬���ڻ�����պУ���Ϊ���ֵΪ1.0ʱĬ���޷�ͨ����Ȳ���
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	dsDesc.StencilEnable = false;

	HR(m_pd3dDevice->CreateDepthStencilState(&dsDesc, m_pDSSLessEqual.GetAddressOf()));







	// ���ò�����

	// ��ʼ��������
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));





	SetPipeLine();
	return true;

}

void SkyBoxPipeLine::SetPipeLine()
{

	////���ù���״̬
	m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dDeviceContext->IASetInputLayout(m_pVertexInputLayout.Get());

	////VS�׶�
	m_pd3dDeviceContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	m_pd3dDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);


	m_pd3dDeviceContext->GSSetShader(nullptr, nullptr, 0);
	m_pd3dDeviceContext->RSSetState(m_pRSNoCull.Get());


	m_pd3dDeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	m_pd3dDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	m_pd3dDeviceContext->OMSetDepthStencilState(m_pDSSLessEqual.Get(), 0);
	m_pd3dDeviceContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
}
