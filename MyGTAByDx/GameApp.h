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


	//Shader初始化
	bool InitShader();

	//初始化渲染资源
	bool InitResource();

	//初始化管线
	bool InitPipeline();

	//  场景内物体管线
	class GameObjectPipeLine* GOPipeline;		
	//  天空盒管线
	class SkyBoxPipeLine* SBPipeline;


	class Car* MyCar;												// 车辆Actor
	class Actor* Ground;											// 地面


	bool m_bUseDfCamera;											//是否使用默认相机
	class ThirdPersonCamera* DfCamera;								//默认相机


	// 天空盒
	class SkyBox* MySkyBox;

	//各个模块

	class InputManager* m_InputManager;							//输入管理模块

	class TextureLoader* m_TextureLoader;						//纹理读取模块
};

