#include <windows.h>
#include "Log.h"
#include "CEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ConsoleWindow::GetInstance().Init();

	CEngine cEngine;

	if (!cEngine.Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd)) {
		// to do: 에러 처리 코드
		return -1;
	}

	return cEngine.Run();
} 
