/* MeshComponent is an abstract base for any component that is an instance of a renderable collection of triangles.
 *
 * @see StaticMeshComponent
 * @see SkeletalMeshComponent(还没有)
 */

#pragma once
#include "PrimitiveComponent.h"
#include "BasicShape.h"


class MeshComponent : public PrimitiveComponent {
public:
    MeshComponent();
    virtual ~MeshComponent();


	// 游戏逻辑相关
	//virtual void BeginPlay() override;
	//virtual void Tick(float dt)      override;

	// 渲染相关
	virtual void InitResource(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dDeviceContext); //初始化渲染资源	
	virtual void Draw();						//将资源绑定到pipeline
	virtual void Update(float dt);				//更新资源


	// 设置形状
	void SetShape(BasicShape* shape);


	// 设置纹理（可运行时）
	void SetTexture(ID3D11ShaderResourceView* pTexture = nullptr);
protected:
	//形状网格数据
	BasicShape* m_pShape;

};
