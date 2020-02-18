#pragma once

/*=============================================================================
	Object.h: Direct base class for alpha Lyrae Engine
=============================================================================*/

// 可在map中加载的都继承此类，如几何体，相机等
// 实现了基本的计数，给每个对象分配唯一id
class Object {
private:
	static unsigned int g_count;				//object的个数
	unsigned int m_ID;							//每个对象的id

public:
	Object();
    virtual ~Object() {}

	static unsigned int GetCount() { return g_count; }
	unsigned int GetID() { return m_ID; }

};