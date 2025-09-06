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
	FVector CurPos;
	FVector PrevPos;

	bool LeftDown = false;
	bool RightDown = false;
	bool MiddelDown = false;
};

enum class KeyButton
{
	W = 0,
	A = 1,
	S = 2,
	D = 3,
};

struct KeyState
{
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
};

class InputManager
{
public:

	static InputManager& Get()
	{
		static InputManager  instance;
		//UE_LOG("%.2f %.2f",instance.mouse.CurPos.X,instance.mouse.CurPos.Y);
		return instance;
	}

	inline void ProcessMessage(UINT msg,WPARAM wParam,LPARAM lParam)
	{
		switch(msg)
		{
		case WM_MOUSEMOVE:
		{
			mouse.CurPos.X = GET_X_LPARAM(lParam);
			mouse.CurPos.Y = GET_Y_LPARAM(lParam);

			//UE_LOG("%.2f %.2f",mouse.CurPos.X,mouse.CurPos.Y);
		}
		break;
		
		case WM_LBUTTONUP: // ← 왼쪽 버튼 뗄 때
		{
			mouse.LeftDown = false;
			break;
		}

		case WM_LBUTTONDOWN:
		{
			mouse.LeftDown = true; 
			break;
		}

		case WM_RBUTTONUP: // ← 오른쪽 버튼 뗄 때
		{
			mouse.RightDown = false;
			break;
		}

		case WM_RBUTTONDOWN:
		{
			mouse.RightDown = true;  
			break;
		}

		case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'W': keys.W = true; break;
			case 'A': keys.A = true; break;
			case 'S': keys.S = true; break;
			case 'D': keys.D = true; break;
			}
			break;
		}
		

		case WM_KEYUP:
		{
			switch(wParam)
			{
			case 'W': keys.W = false; break;
			case 'A': keys.A = false; break;
			case 'S': keys.S = false; break;
			case 'D': keys.D = false; break;
			}
			break;
		}
		}
	}
	inline float GetX() {	
		//UE_LOG("%.2f %.2f",mouse.CurPos.X,mouse.CurPos.Y);
		return mouse.CurPos.X; 
	}
	inline int GetY() {	return mouse.CurPos.Y; 	}

	inline bool IsDown(MouseButton button) const
	{
		switch(button)
		{
		case MouseButton::Right:
		{
			return mouse.RightDown;
		}
		break;
		
		case MouseButton::Left:
		{
			return mouse.LeftDown;
		}
		break;

		}
	}

	inline bool IsKeyDown(KeyButton keyButton) const
	{
		switch(keyButton)
		{
		case KeyButton::W:
		{
			return keys.W;
		}
		case KeyButton::A:
		{
			return keys.A;
		}
		case KeyButton::S:
		{
			return keys.S;
		}
		case KeyButton::D:
		{
			return keys.D;
		}
		}
	}

public:
	Mouse mouse;
	KeyState keys;

};

