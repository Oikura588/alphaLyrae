#include "Car.h"
#include "DXUtil.h"
#include "TextureLoader.h"
using namespace DirectX;
Car::Car():Actor()
{
	CarBody = new MeshComponent();
	LFWheel = new MeshComponent();
	RFWheel = new MeshComponent();
	LBWheel = new MeshComponent();
	RBWheel = new MeshComponent();

	LFWheelAxis = new SceneComponent();
	RFWheelAxis = new SceneComponent();
	LBWheelAxis = new SceneComponent();
	RBWheelAxis = new SceneComponent();





}

Car::~Car()
{
}

void Car::BeginPlay()
{
	Actor::BeginPlay();
}

void Car::Tick(float DeltaSeconds)
{
	using namespace DirectX;

	Actor::Tick(DeltaSeconds);


	////旋转
	//static float phi = 0.001f, theta = 0.0f;
	////phi += 0.0001f, theta += 0.00015f;
	//XMMATRIX W = XMMatrixRotationY(phi);

	////WorldMatrix = XMMatrixTranspose(W);
	////LocalMatrix = W * LocalMatrix;

	//LFWheel->LocalMatrix = W * LFWheel->LocalMatrix;
	//
	//RFWheel->LocalMatrix = W * RFWheel->LocalMatrix;

	//
	//LBWheel->LocalMatrix = W * LBWheel->LocalMatrix;

	//
	//RBWheel->LocalMatrix = W * RBWheel->LocalMatrix;

}

void Car::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{

	TextureLoader* m_TextureLoader = new TextureLoader();
	m_TextureLoader->Init(pd3dDevice,pd3dDeviceContext);


	CubeShape* BodyShape = new CubeShape(3, 3, 5);
	CarBody->SetShape(BodyShape);
	CarBody->LocalMatrix = XMMatrixTranslation(0.f, 0.f, 0.f);



	
	CylinderShape* tmp = new CylinderShape();

	LFWheel->SetShape(tmp);
	LFWheel->SetTexture(m_TextureLoader->LoadDefaultTexture().Get());


	//LFWheel->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90));;
	//LFWheel->LocalMatrix = LFWheel->LocalMatrix * XMMatrixTranslation(-3.f, -3.f, 3.f);

	LFWheelAxis->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90));;
	LFWheelAxis->LocalMatrix = LFWheelAxis->LocalMatrix * XMMatrixTranslation(-3.f, -3.f, 3.f);
	CylinderShape* tmp2 = new CylinderShape();

	RFWheel->SetShape(tmp2);
	RFWheel->SetTexture(m_TextureLoader->LoadDefaultTexture().Get());
	//RFWheel->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	//RFWheel->LocalMatrix = RFWheel->LocalMatrix* XMMatrixTranslation(3.f, -3.f, 3.f);

	RFWheelAxis->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	RFWheelAxis->LocalMatrix = RFWheelAxis->LocalMatrix* XMMatrixTranslation(3.f, -3.f, 3.f);



	CylinderShape* tmp3 = new CylinderShape();

	LBWheel->SetShape(tmp3);
	LBWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	//LBWheel->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90)) ;
	//LBWheel->LocalMatrix = LBWheel->LocalMatrix* XMMatrixTranslation(-3.f, -3.f, -3.f);
	LBWheelAxis->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90)) ;
	LBWheelAxis->LocalMatrix = LBWheelAxis->LocalMatrix* XMMatrixTranslation(-3.f, -3.f, -3.f);


	CylinderShape* tmp4 = new CylinderShape();

	RBWheel->SetShape(tmp4);
	RBWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	//RBWheel->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	//RBWheel->LocalMatrix = RBWheel->LocalMatrix * XMMatrixTranslation(3.f, -3.f, -3.f);
	RBWheelAxis->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	RBWheelAxis->LocalMatrix = RBWheelAxis->LocalMatrix * XMMatrixTranslation(3.f, -3.f, -3.f);


	AddComponent(CarBody);
	LFWheelAxis->AddChildren(LFWheel);
	AddComponent(LFWheelAxis);
	RFWheelAxis->AddChildren(RFWheel);
	AddComponent(RFWheelAxis);
	LBWheelAxis->AddChildren(LBWheel);
	AddComponent(LBWheelAxis);
	RBWheelAxis->AddChildren(RBWheel);
	AddComponent(RBWheelAxis);

	CarBody->InitResource(pd3dDevice, pd3dDeviceContext);
	LFWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	RFWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	LBWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	RBWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	delete(m_TextureLoader);
	m_TextureLoader = nullptr;
}

void Car::MoveForward(float v)
{
	float fSpeed = 0.01 * v;
	RootComponent->LocalMatrix = RootComponent->LocalMatrix * DirectX::XMMatrixTranslation(0.f, 0.f, fSpeed);
	WheelMoveForwardRotate(fSpeed);
}

void Car::MoveRight(float v)
{
	float rSpeed = 0.01 * v;

	//RootComponent->LocalMatrix = RootComponent->LocalMatrix * DirectX::XMMatrixTranslation(rSpeed, 0.f, 0.f);
	WheelMoveRightRotate(rSpeed);
}

void Car::WheelMoveForwardRotate(float v)
{
	/*static float phi = 0.f;
	phi -= v*0.01;*/

	float phi = -v;

	
	//LFWheel->LocalMatrix = W * LFWheel->LocalMatrix;
	//
	//RFWheel->LocalMatrix = W * RFWheel->LocalMatrix;

	//
	//LBWheel->LocalMatrix = W * LBWheel->LocalMatrix;

	//
	//RBWheel->LocalMatrix = W * RBWheel->LocalMatrix;

	// 轮子因为自身没有旋转而是轴旋转，所以绕Y轴（UP）旋转
	XMMATRIX W = XMMatrixRotationY(phi);
	LFWheel->LocalMatrix =  LFWheel->LocalMatrix*W;
	
	RFWheel->LocalMatrix =  RFWheel->LocalMatrix * W;


	LBWheel->LocalMatrix =  LBWheel->LocalMatrix * W;

	
	RBWheel->LocalMatrix =  RBWheel->LocalMatrix * W;
}





void Car::WheelMoveRightRotate(float v)
{
	static float theta=0.f;
	theta += v * 0.1;

	//限制转动角度
	if (theta< -XMConvertToRadians(30))
	{
		theta = -XMConvertToRadians(30);
	}
	if (theta> XMConvertToRadians(30))
	{
		theta = XMConvertToRadians(30);

	}


	//float theta = v;
	// 因为一开始设置时已经绕Z轴旋转90度，所以现在左右转就是绕X轴
	XMMATRIX W = XMMatrixRotationX(theta);

	//LFWheelAxis->LocalMatrix = LFWheelAxis->LocalMatrix*W;
	LFWheelAxis->LocalMatrix = W* XMMatrixRotationZ(XMConvertToRadians(90))* XMMatrixTranslation(-3.f, -3.f, 3.f);

	RFWheelAxis->LocalMatrix = W* XMMatrixRotationZ(XMConvertToRadians(90)) * XMMatrixTranslation(3.f, -3.f, 3.f);
}
