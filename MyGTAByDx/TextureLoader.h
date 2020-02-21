#pragma once
#include "DXUtil.h"
#include <string>
#include <filesystem>

//���ļ��ж�ȡ����



class TextureLoader {

public:
	TextureLoader();
	~TextureLoader() {};

	bool Init(ID3D11Device* pd3dDevice,  ID3D11DeviceContext* pd3dDeviceContex);



	void Shutdown();

	//
	std::string GetTexturePath();


	ComPtr<ID3D11ShaderResourceView> LoadTexture(std::string textureName);

	//����Ĭ������
	ComPtr<ID3D11ShaderResourceView> LoadDefaultTexture();

	//���ء����ش�������
	ComPtr<ID3D11ShaderResourceView> LoadErrorTexture();

	//��������������
	ComPtr<ID3D11ShaderResourceView> LoadTextureCube(std::string textureName);

private:
	ID3D11Device*	m_pd3dDevice;		//�������������豸
	ID3D11DeviceContext* m_pd3dDeviceContext;

	std::string m_TexturePath;

	//������Դ��ͼ

	ComPtr<ID3D11ShaderResourceView> m_pTexture;



};