#pragma once
#include "DXUtil.h"
#include <string>
#include <filesystem>

//从文件中读取纹理



class TextureLoader {

public:
	TextureLoader();
	~TextureLoader() {};

	bool Init(ID3D11Device* pd3dDevice);



	void Shutdown();

	//
	std::string GetTexturePath();


	ComPtr<ID3D11ShaderResourceView> LoadTexture(std::string textureName);

	//加载默认纹理
	ComPtr<ID3D11ShaderResourceView> LoadDefaultTexture();

	//加载“加载错误”纹理
	ComPtr<ID3D11ShaderResourceView> LoadErrorTexture();


private:
	ID3D11Device*	m_pd3dDevice;		//负责加载纹理的设备
	std::string m_TexturePath;

	//纹理资源视图

	ComPtr<ID3D11ShaderResourceView> m_pTexture;



};