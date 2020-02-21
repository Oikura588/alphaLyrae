#pragma once
#include "D3DApp.h"
#include <DirectXMath.h>
#include "LightType.h"
#include "Material.h"
#include "Geometry.h"

class GameApp :
	public D3DApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void SetRenderPipeLine();
	void UpdateScene(float dt);
	void DrawScene();


	//Shader��ʼ��
	bool InitShader();

	//��ʼ����Ⱦ��Դ
	bool InitResource();

	//��ʼ������
	bool InitPipeline();

	//  �������������
	class GameObjectPipeLine* GOPipeline;		
	//  ��պй���
	class SkyBoxPipeLine* SBPipeline;


	class Car* MyCar;												// ����Actor
	class Actor* Ground;											// ����


	bool m_bUseDfCamera;											//�Ƿ�ʹ��Ĭ�����
	class ThirdPersonCamera* DfCamera;								//Ĭ�����


	// ��պ�
	class SkyBox* MySkyBox;

	//����ģ��

	class InputManager* m_InputManager;							//�������ģ��

	class TextureLoader* m_TextureLoader;						//�����ȡģ��
};

