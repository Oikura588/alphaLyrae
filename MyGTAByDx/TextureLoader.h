#pragma once
#include "DXUtil.h"
#include <string>
#include <filesystem>

//从文件中读取纹理



class TextureLoader {

public:
	TextureLoader();
	~TextureLoader() {};

	bool Init(ID3D11Device* pd3dDevice,  ID3D11DeviceContext* pd3dDeviceContex);



	void Shutdown();

	//
	std::string GetTexturePath();


	ComPtr<ID3D11ShaderResourceView> LoadTexture(std::string textureName);

	//加载默认纹理
	ComPtr<ID3D11ShaderResourceView> LoadDefaultTexture();

	//加载“加载错误”纹理
	ComPtr<ID3D11ShaderResourceView> LoadErrorTexture();

	//加载立方体纹理
	ComPtr<ID3D11ShaderResourceView> LoadTextureCube(std::string textureName);

private:
	ID3D11Device*	m_pd3dDevice;		//负责加载纹理的设备
	ID3D11DeviceContext* m_pd3dDeviceContext;

	std::string m_TexturePath;

	//纹理资源视图

	ComPtr<ID3D11ShaderResourceView> m_pTexture;



};