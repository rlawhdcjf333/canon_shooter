#pragma once

//클래스 전방선언 : 포인터만 가능
class Image;

#define PI 3.14159265f

/*
각도를 표현을 표현하는 단위!!!!

- 디그리 : 0도 ~ 360도
- 라디안 : 0 ~ 6.28

라디안 : 호의 길이와 반지름의 길이가 일치하면 1라디안
180 / 디그리!!!!!

디그리 -> 라디안 : 디그리 * (PI / 180.f)
라디안 -> 디그리 : 라디안 * (180.f / PI)

캐논 만들기!
1. 캐논 포신 만들어오고
2. 내가 VK_UP키를 누르면 포신이 왼쪽으로 회전
3. 내가 VK_DOWN키를 누르면 포신이 오른쪽으로 회전
4. 단, 포신은 지면을 넘어가면 안된다
*/

struct Cannon
{
	float x;
	float y;
	float angle;
	float radius;		//몸통 반지름

	float connonLength;	//포신 길이

	float cannonEndX;	//캐논 끝 X
	float cannonEndY;	//캐논 끝 Y
};

struct Bullet {

	float x;
	float y;
	float radius;

	float angle;
	float antiG;
	float xvector;

	float dist;
};

struct TrajLine {

	float x;
	float y;
	float radius;

};


struct Tcircle {

	float x;
	float y;
	float radius;
	float dist;
};

class MainGame
{
	Image* mBackBuffer;	//후면버퍼(건들지마라)
private:
	Cannon mCannon;

	Tcircle target;

	float mDegree;
	
	float mGravity;

	vector <Bullet> X;

	TrajLine dots[20];

	float cannonPow;

	float wind;
	RECT windrc[10];

	float frameRate;

	int score;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

