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
	Actor::Tick(DeltaSeconds);

	using namespace DirectX;

	//Ðý×ª
	static float phi = 0.001f, theta = 0.0f;
	//phi += 0.0001f, theta += 0.00015f;
	XMMATRIX W = XMMatrixRotationY(phi);

	//WorldMatrix = XMMatrixTranspose(W);
	//LocalMatrix = W * LocalMatrix;

	LFWheel->LocalMatrix = W * LFWheel->LocalMatrix;
	
	RFWheel->LocalMatrix = W * RFWheel->LocalMatrix;

	
	LBWheel->LocalMatrix = W * LBWheel->LocalMatrix;

	
	RBWheel->LocalMatrix = W * RBWheel->LocalMatrix;

}

void Car::InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext)
{

	TextureLoader* m_TextureLoader = new TextureLoader();
	m_TextureLoader->Init(pd3dDevice);


	CubeShape* BodyShape = new CubeShape(3, 3, 5);
	CarBody->SetShape(BodyShape);
	CarBody->LocalMatrix = XMMatrixTranslation(0.f, 0.f, 0.f);




	CylinderShape* tmp = new CylinderShape();

	LFWheel->SetShape(tmp);
	LFWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	LFWheel->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90));;
	LFWheel->LocalMatrix = LFWheel->LocalMatrix * XMMatrixTranslation(-3.f, -3.f, 3.f);
	CylinderShape* tmp2 = new CylinderShape();

	RFWheel->SetShape(tmp2);
	RFWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	RFWheel->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	RFWheel->LocalMatrix = RFWheel->LocalMatrix* XMMatrixTranslation(3.f, -3.f, 3.f);

	CylinderShape* tmp3 = new CylinderShape();

	LBWheel->SetShape(tmp3);
	LBWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	LBWheel->LocalMatrix = XMMatrixRotationZ(XMConvertToRadians(90)) ;
	LBWheel->LocalMatrix = LBWheel->LocalMatrix* XMMatrixTranslation(-3.f, -3.f, -3.f);

	CylinderShape* tmp4 = new CylinderShape();

	RBWheel->SetShape(tmp4);
	RBWheel->SetTexture(m_TextureLoader->LoadErrorTexture().Get());
	RBWheel->LocalMatrix =  XMMatrixRotationZ(XMConvertToRadians(90));
	RBWheel->LocalMatrix = RBWheel->LocalMatrix * XMMatrixTranslation(3.f, -3.f, -3.f);


	AddComponent(CarBody);
	AddComponent(LFWheel);
	AddComponent(RFWheel);
	AddComponent(LBWheel);
	AddComponent(RBWheel);

	CarBody->InitResource(pd3dDevice, pd3dDeviceContext);
	LFWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	RFWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	LBWheel->InitResource(pd3dDevice, pd3dDeviceContext);

	RBWheel->InitResource(pd3dDevice, pd3dDeviceContext);
}

void Car::MoveForward(float v)
{
	float fSpeed = 0.01 * v;
	RootComponent->LocalMatrix = RootComponent->LocalMatrix * DirectX::XMMatrixTranslation(0.f, 0.f, fSpeed);
}

void Car::MoveRight(float v)
{
	float rSpeed = 0.01 * v;

	RootComponent->LocalMatrix = RootComponent->LocalMatrix * DirectX::XMMatrixTranslation(rSpeed, 0.f, 0.f);
}
