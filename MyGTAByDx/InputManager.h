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

	//获取输入信息
	void GetInput();

	//键盘处理
	bool IsKeyDown(int key);					//判断键盘上某键是否按下

	void Reset();								//清空输入

	bool IsAnyKeyDown();						//判断是否有键按下
	void SetIsKeyDown();						//有键按下的事件
	//鼠标处理
	bool IsMouseButtonDown(int button);



	//鼠标指针X坐标
	float MouseDX();

	//鼠标指针Y坐标
	float MouseDY();

	//滚轮值
	float MouseDZ();

private:

	//初始化DirecInput接口和设备
	ComPtr<IDirectInput8> m_pDirectInput;

	//初始化键盘
	ComPtr<IDirectInputDevice8> m_pKeyboardDevice;
	char m_keyBuffer[256];				//键盘按键状态

	//初始化鼠标

	ComPtr<IDirectInputDevice8> m_pMouseDevice;
	DIMOUSESTATE m_MouseState;			//鼠标按键状态



	//初始化DxInput以及设备
	bool InitDirectInput(HINSTANCE hInstance, HWND hMainWndHandle);

	bool m_IsAnyKeyDown;				//是否有键按下





};

