#pragma once
#include "DXUtil.h"
#include <string>
#include <filesystem>

//���ļ��ж�ȡ����



class TextureLoader {

public:
	TextureLoader();
	~TextureLoader() {};

	bool Init(ID3D11Device* pd3dDevice);



	void Shutdown();

	//
	std::string GetTexturePath();


	ComPtr<ID3D11ShaderResourceView> LoadTexture(std::string textureName);

	//����Ĭ������
	ComPtr<ID3D11ShaderResourceView> LoadDefaultTexture();

	//���ء����ش�������
	ComPtr<ID3D11ShaderResourceView> LoadErrorTexture();


private:
	ID3D11Device*	m_pd3dDevice;		//�������������豸
	std::string m_TexturePath;

	//������Դ��ͼ

	ComPtr<ID3D11ShaderResourceView> m_pTexture;



};