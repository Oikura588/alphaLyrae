#include "InputManager.h"
#include"DXTrace.h"
#include <dinput.h>


InputManager::InputManager()
{
	ZeroMemory(m_keyBuffer, sizeof(char) * 256);
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));

	m_IsAnyKeyDown = false;
}


InputManager::~InputManager()
{
}

bool InputManager::Init(HINSTANCE hInstance, HWND hMainWndHandle)
{
	if (!InitDirectInput( hInstance, hMainWndHandle)) {
		return false;
	}
	return true;
}

void InputManager::Shutdown()
{
	if (m_pKeyboardDevice != nullptr) {
		m_pKeyboardDevice->Unacquire();
	}
	if (m_pMouseDevice != nullptr) {

		m_pMouseDevice->Unacquire();
	}
}

void InputManager::GetInput()
{
	HRESULT hr = m_pKeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);

	//������ֵ���ص�������
	if (hr) {

		m_pKeyboardDevice->Acquire();

		m_pKeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (LPVOID)m_keyBuffer);


	}
	hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState);
	if (hr) {
		m_pMouseDevice->Acquire();
		m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**)&m_MouseState);

	}
}

bool InputManager::IsKeyDown(int key)
{
	if (m_keyBuffer[key] & 0x80) {
		return true;
	}
	return false;
}

void InputManager::Reset()
{
	ZeroMemory(m_keyBuffer, sizeof(char) * 256);
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
	m_IsAnyKeyDown = false;

}

bool InputManager::IsAnyKeyDown()
{
	for (size_t i = 0; i < 256; i++)
	{
		if (m_keyBuffer[i] != 0x00) {
			return true;
		}
	}
	return false;
}

void InputManager::SetIsKeyDown()
{
	m_IsAnyKeyDown = true;
}

bool InputManager::IsMouseButtonDown(int button)
{
	return (m_MouseState.rgbButtons[button] & 0x80) != 0;
}

float InputManager::MouseDX()
{
	return (float)m_MouseState.lX;
}

float InputManager::MouseDY()
{
	return (float)m_MouseState.lY;
}

float InputManager::MouseDZ()
{
	return (float)m_MouseState.lZ;
}

bool InputManager::InitDirectInput(HINSTANCE hInstance, HWND hMainWndHandle)
{

	//����Debugʱ�жϵ��ʱ�򴰿��ں�̨��ʹ��DISCL_FOREGROUND�Ļ��ͻ��ѯ�����豸..
	DWORD keyboardCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	DWORD mouseCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

	
	HR(DirectInput8Create(hInstance, 0x800, IID_IDirectInput8, (void**)(m_pDirectInput.GetAddressOf()), NULL));


	//��ʼ������

	//1.��ʼ���豸
	HR(m_pDirectInput->CreateDevice(GUID_SysKeyboard, m_pKeyboardDevice.GetAddressOf(), NULL));

	//2.�������ݸ�ʽ
	HR(m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard));

	//3.����Э������  ǰ̨ģʽ���̨ģʽ������ģʽ���ռģʽ
	HR(m_pKeyboardDevice->SetCooperativeLevel(hMainWndHandle, keyboardCoopFlags));
	//4.������������

	//5. ��ȡ����ѯ�豸 Acquire() Poll()
	HR(m_pKeyboardDevice->Acquire());
	HR(m_pKeyboardDevice->Poll());


	//6.�õ�������Ϣ  GetDeviceState

	//7.����Ϣ�洢��buffer�� Get_Input


	//��ʼ�����


	//1.��ʼ���豸
	HR(m_pDirectInput->CreateDevice(GUID_SysMouse, m_pMouseDevice.GetAddressOf(), nullptr));

	//2.�������ݸ�ʽ
	HR(m_pMouseDevice->SetDataFormat(&c_dfDIMouse));

	//3.����Э������  ǰ̨ģʽ���̨ģʽ������ģʽ���ռģʽ
	HR(m_pMouseDevice->SetCooperativeLevel(hMainWndHandle, mouseCoopFlags));
	//4.������������

	//5. ��ȡ����ѯ�豸 Acquire() Poll()
	HR(m_pMouseDevice->Acquire());
	HR(m_pMouseDevice->Poll());
	//6.�õ�������Ϣ  GetDeviceState

	//7.����Ϣ�洢��buffer�� Device_Read



	return true;
}
