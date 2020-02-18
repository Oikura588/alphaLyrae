#pragma once
#include "DXUtil.h"

#include <dinput.h>
#pragma  comment(lib,"dinput8.lib")	
#pragma  comment(lib,"dxguid.lib")


class InputManager
{
public:
	InputManager();
	~InputManager();

	bool Init(HINSTANCE hInstance, HWND hMainWndHandle);
	void Shutdown();

	//��ȡ������Ϣ
	void GetInput();

	//���̴���
	bool IsKeyDown(int key);					//�жϼ�����ĳ���Ƿ���

	void Reset();								//�������

	bool IsAnyKeyDown();						//�ж��Ƿ��м�����
	void SetIsKeyDown();						//�м����µ��¼�
	//��괦��
	bool IsMouseButtonDown(int button);



	//���ָ��X����
	float MouseDX();

	//���ָ��Y����
	float MouseDY();

	//����ֵ
	float MouseDZ();

private:

	//��ʼ��DirecInput�ӿں��豸
	ComPtr<IDirectInput8> m_pDirectInput;

	//��ʼ������
	ComPtr<IDirectInputDevice8> m_pKeyboardDevice;
	char m_keyBuffer[256];				//���̰���״̬

	//��ʼ�����

	ComPtr<IDirectInputDevice8> m_pMouseDevice;
	DIMOUSESTATE m_MouseState;			//��갴��״̬



	//��ʼ��DxInput�Լ��豸
	bool InitDirectInput(HINSTANCE hInstance, HWND hMainWndHandle);

	bool m_IsAnyKeyDown;				//�Ƿ��м�����





};

