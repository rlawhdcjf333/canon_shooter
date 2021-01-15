#include "pch.h"
#include "MainGame.h"

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		//�޼���ť�� WM_QUIT��� �޼����� ���� GetMessage�� false�� ��ȯ�ϰ� �����. �� ������ �����Ų��
		PostQuitMessage(0);
		break;
		//���콺 �������� �� ������ �޼���
	case WM_MOUSEMOVE:
		//lparam : ���콺 ��ǥ�� ���� �� �ش� ����(����) �ϳ��� x,y,���� ��� ������.
		//�տ� 32��Ʈ���� y��, �ڿ� 32��Ʈ���� x���� ����(<<,>> ����Ʈ �����ڷ�)
		_mousePosition.x = LOWORD(lParam);
		_mousePosition.y = HIWORD(lParam);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, false);
		Update();
		break;
	case WM_PAINT:
		//1. BeginPaint : ȭ���� �׸��� ���� ��������� �ϴ� �༮
		PAINTSTRUCT pt;	//��� ������ ���� . . .
		HDC hdc = BeginPaint(hWnd, &pt);
		// {{ ���� ���� �ȿ� �׷��� ����. . . 
		Render(hdc);
		// }}
		//2. EndPaint : �� �׸��� ������ �־�� �ϴ� �༮
		EndPaint(hWnd, &pt);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
