#include "Object.h"

unsigned Object::g_count = 0;

Object::Object()
{
	g_count++;
	m_ID = g_count;
}
