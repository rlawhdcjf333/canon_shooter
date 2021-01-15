#pragma once

//Ŭ���� ���漱�� : �����͸� ����
class Image;

#define PI 3.14159265f

/*
������ ǥ���� ǥ���ϴ� ����!!!!

- ��׸� : 0�� ~ 360��
- ���� : 0 ~ 6.28

���� : ȣ�� ���̿� �������� ���̰� ��ġ�ϸ� 1����
180 / ��׸�!!!!!

��׸� -> ���� : ��׸� * (PI / 180.f)
���� -> ��׸� : ���� * (180.f / PI)

ĳ�� �����!
1. ĳ�� ���� ��������
2. ���� VK_UPŰ�� ������ ������ �������� ȸ��
3. ���� VK_DOWNŰ�� ������ ������ ���������� ȸ��
4. ��, ������ ������ �Ѿ�� �ȵȴ�
*/

struct Cannon
{
	float x;
	float y;
	float angle;
	float radius;		//���� ������

	float connonLength;	//���� ����

	float cannonEndX;	//ĳ�� �� X
	float cannonEndY;	//ĳ�� �� Y
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
	Image* mBackBuffer;	//�ĸ����(�ǵ�������)
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

