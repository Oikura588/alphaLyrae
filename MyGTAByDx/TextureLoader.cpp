#include "TextureLoader.h"
#include "StringProcess.h"

#include "WICTextureLoader.h"



TextureLoader::TextureLoader()
{
	m_TexturePath = "Texture\\";
}

bool TextureLoader::Init(ID3D11Device* pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
	if (m_pd3dDevice == nullptr)
		return false;
	return true;
}

void TextureLoader::Shutdown()
{

}

std::string TextureLoader::GetTexturePath()
{
	return m_TexturePath;

}

ComPtr<ID3D11ShaderResourceView> TextureLoader::LoadTexture(std::string textureName)
{
	m_pTexture.Reset();
	using namespace DirectX;
	using namespace std;
	StringProcess stringProcessor;
	string fullpath = m_TexturePath + textureName;
	HRESULT hr = CreateWICTextureFromFile(m_pd3dDevice, stringProcessor.StringToWchar(fullpath), nullptr, m_pTexture.ReleaseAndGetAddressOf());
	if (hr == S_OK) {
		return m_pTexture;
	}
	//找不到指定文件，退出
	else if (hr == 0x80070002) {
		if (!(textureName == "Default.png")) {
			return LoadErrorTexture();
		}
		return LoadDefaultTexture();
	}
	else {
		return  LoadErrorTexture();
	}

}

//创建默认纹理
ComPtr<ID3D11ShaderResourceView> TextureLoader::LoadDefaultTexture()
{

	std::string filename = "Default.png";
	return LoadTexture(filename);
}

ComPtr<ID3D11ShaderResourceView> TextureLoader::LoadErrorTexture()
{
	std::string filename = "Error.png";


	return LoadTexture(filename);
}

