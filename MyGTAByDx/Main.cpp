#include "World.h"
#include "GameApp.h"
#include <stdio.h>
//
//// Game����ڵ㣬��ʹ��Console�ķ�ʽ
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
//	//����BeginPlay�Կ�ʼ
//	GameWorld.BeginPlay();
//
//
//}
//


// ʹ�ô�����Ⱦ��������

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	GameApp mainApp(hInstance);
	if (!mainApp.Init())
	{
		return 0;
	}
	return mainApp.Run();


}




