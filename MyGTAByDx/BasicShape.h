#pragma once
/************************************************************************/
/* 基本形状,包含索引信息和顶点信息                                      */
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

