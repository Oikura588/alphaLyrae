#pragma once

/*=============================================================================
	Object.h: Direct base class for alpha Lyrae Engine
=============================================================================*/

// ����map�м��صĶ��̳д��࣬�缸���壬�����
// ʵ���˻����ļ�������ÿ���������Ψһid
class Object {
private:
	static unsigned int g_count;				//object�ĸ���
	unsigned int m_ID;							//ÿ�������id

public:
	Object();
    virtual ~Object() {}

	static unsigned int GetCount() { return g_count; }
	unsigned int GetID() { return m_ID; }

};