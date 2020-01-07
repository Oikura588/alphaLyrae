#include "World.h"
#include "GameApp.h"
#include <stdio.h>
//
//// Game的入口点，先使用Console的方式
//
//int main(){
//    World GameWorld;
//	
//	Actor a1, a2, a3;
//
//	a1.AddChildren(a2);
//    GameWorld.AddActor(a1);
//    //GameWorld.AddActor(a2);
//    GameWorld.AddActor(a3);
//	a1.SetOwner(&a2);
//	//调用BeginPlay以开始
//	GameWorld.BeginPlay();
//
//
//}
//


// 使用窗体渲染基本界面

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	GameApp mainApp(hInstance);
	if (!mainApp.Init())
	{
		return 0;
	}
	return mainApp.Run();


}




