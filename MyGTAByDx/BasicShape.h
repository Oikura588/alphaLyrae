#pragma once
/************************************************************************/
/* ������״,����������Ϣ�Ͷ�����Ϣ                                      */
/************************************************************************/
#include <vector>

//#include "Geometry.h"

class BasicShape
{
public:
	BasicShape();
	virtual ~BasicShape();

	
};

class CubeShape :public BasicShape {
public:
	CubeShape();
	~CubeShape();
	//
	//Geometry::MeshData<VertexPosNormalTex>	Data;


};

