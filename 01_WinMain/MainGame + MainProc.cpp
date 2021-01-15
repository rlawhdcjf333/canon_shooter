#include "pch.h"
#include "MainGame.h"

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		//메세지큐에 WM_QUIT라는 메세지를 보내 GetMessage가 false를 반환하게 만든다. 즉 루프를 종료시킨다
		PostQuitMessage(0);
		break;
		//마우스 움직였을 떄 들어오는 메세지
	case WM_MOUSEMOVE:
		//lparam : 마우스 좌표가 들어올 떄 해당 변수(정수) 하나에 x,y,값을 담아 보낸다.
		//앞에 32비트에는 y값, 뒤에 32비트에는 x값을 저장(<<,>> 시프트 연산자로)
		_mousePosition.x = LOWORD(lParam);
		_mousePosition.y = HIWORD(lParam);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, false);
		Update();
		break;
	case WM_PAINT:
		//1. BeginPaint : 화면을 그리기 전에 실행해줘야 하는 녀석
		PAINTSTRUCT pt;	//얘는 쓸일이 없다 . . .
		HDC hdc = BeginPaint(hWnd, &pt);
		// {{ 제발 여기 안에 그려라 제발. . . 
		Render(hdc);
		// }}
		//2. EndPaint : 다 그리면 실행해 주어야 하는 녀석
		EndPaint(hWnd, &pt);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
