#pragma once
#include <Windows.h>
#include <windowsx.h> 
#include "FVector.h" 

#include "Log.h"
enum class MouseButton
{
	Left = 0,
	Middle = 1,
	Right = 2,
};

struct Mouse
{
	Mouse();
	FVector CurPos;
	FVector PrevPos;

	bool LeftDown = false;
	bool RightDown = false;
	bool MiddelDown = false;
};

class InputManager
{
public:

	static InputManager& Get()
	{
		static InputManager  instance;
		return instance;		
	}

	inline void ProcessMessage(UINT msg,WPARAM,LPARAM lParam)
	{
		switch(msg)
		{
		case WM_MOUSEMOVE:
		{
			mouse.CurPos.X = GET_X_LPARAM(lParam);
			mouse.CurPos.Y = GET_Y_LPARAM(lParam);

			UE_LOG("%.2f %.2f",mouse.CurPos.X,mouse.CurPos.Y);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			mouse.LeftDown = true;
			UE_LOG("C");

			break;
		}
		case WM_LBUTTONUP:
		{
			mouse.LeftDown = false;
			UE_LOG("D");
			break;

		}

		case WM_RBUTTONDOWN:
		{
			mouse.RightDown = true;  
			break;
		}

		}
	}
	inline int GetX() {	return mouse.CurPos.X; 	}
	inline int GetY() {	return mouse.CurPos.Y; 	}

	bool IsDown(MouseButton button) const;

public:
	Mouse mouse;

};

