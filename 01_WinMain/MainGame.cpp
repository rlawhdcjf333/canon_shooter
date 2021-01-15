#include "pch.h"
#include "MainGame.h"

#include "Image.h"

#define PI 3.141592

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	mCannon.x = WINSIZEX / 2;
	mCannon.y = WINSIZEY;
	mCannon.angle = PI / 2;
	mCannon.connonLength = 100.f;
	mCannon.radius = 50.f;

	target.x = WINSIZEX / 2;
	target.y = 50;
	target.radius = 20;
	target.dist = 100;

	mGravity = 0.98f;

	cannonPow = 20;

	mDegree = PI / 2;

	wind = -0.37f;

	frameRate = 0;

	score = 0;


	for (int i = 0; i < 10; i++) {

		windrc[i] = RectMakeCenter(WINSIZEX / 2 - 90 + 20 * i, WINSIZEY / 2 + 80, 20, 10);

	}

}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	KillTimer(_hWnd, 1);//타이머 꺼주자

	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	delete mBackBuffer;
	mBackBuffer = NULL;
}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	frameRate ++;

	if (Input::GetInstance()->GetKey(VK_UP) and cannonPow <= 40) { cannonPow += 0.25; }//canon shooting power control
	if (Input::GetInstance()->GetKey(VK_DOWN) and cannonPow >= 10) { cannonPow -= 0.25; }

	if (Input::GetInstance()->GetKey(VK_LEFT) and mDegree < PI - 0.2) { mDegree += 0.01f; }//cannon angle control
	if (Input::GetInstance()->GetKey(VK_RIGHT) and mDegree > 0.2) { mDegree -= 0.01f; }

	mCannon.cannonEndX = mCannon.x+cosf(mDegree) * mCannon.connonLength; //cannon angle movement
	mCannon.cannonEndY = mCannon.y-sinf(mDegree) * mCannon.connonLength;

	if (Input::GetInstance()->GetKeyDown(VK_SPACE)) { X.push_back({mCannon.cannonEndX, mCannon.cannonEndY, 30, mDegree, -cannonPow * sinf(mDegree),cannonPow * cosf(mDegree)}); }

	for (int i = 0; i < X.size(); i++) { //bullet physics

		X[i].x += X[i].xvector;
		X[i].xvector += wind; //trajectory moving object;s x-vector element 
		X[i].y += X[i].antiG;
		X[i].antiG += mGravity; //trajectory moving object's y-vector element

		if (X[i].x<=0 or X[i].x>=WINSIZEX or X[i].y >= WINSIZEY) { //erase out-of-window object

			X.erase(X.begin() + i);
			X.shrink_to_fit();
		}

	}

	for (int i = 0; i < 20; i++) { //trajectory curve approximation (definite integral, C=0)

		dots[i].x = mCannon.cannonEndX + cannonPow * cosf(mDegree) * 3*i+ wind * 0.5* powf(3*i,2);
		dots[i].y = mCannon.cannonEndY - cannonPow * sinf(mDegree) * 3*i+ mGravity *0.5* powf(3*i,2);
		dots[i].radius = 5;
	}

	for (int i = 0; i < X.size(); i++) { //target-bullet collision check

		target.dist = sqrtf(powf(target.x-X[i].x,2) + powf(target.y-X[i].y,2));
		X[i].dist = sqrtf(powf(target.x - X[i].x, 2) + powf(target.y - X[i].y, 2));
	}

	for (int i = 0; i < X.size(); i++) {
		if (X[i].dist < 80) {//get target trigger; wind vector change; target position change; scoring; bullet erase;

			if (wind < 0) { wind = Random::GetInstance()->RandomInt(5, 50) * 0.01; }
			else { wind = -Random::GetInstance()->RandomInt(5, 50) * 0.01; }

			target.x = Random::GetInstance()->RandomInt(50, WINSIZEX - 50);
			target.y = Random::GetInstance()->RandomInt(50, WINSIZEY-200);

			X.erase(X.begin() + i);
			X.shrink_to_fit();

			score++;
		}
	}
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		HBRUSH color;
		HBRUSH white;

		wstring scoreT = L"점수 : " + to_wstring(score);
		TextOut(backDC, WINSIZEX / 2 - 25, WINSIZEY / 2 - 250, scoreT.c_str(), scoreT.length());

		wstring exp1 = L"[포신 반시계회전 : 왼쪽 화살표]     [포신 시계회전 : 오른쪽 화살표]";
		TextOut(backDC, WINSIZEX / 2 - 225, WINSIZEY / 2 - 100, exp1.c_str(), exp1.length());

		wstring exp = L"[화력 UP : 위 화살표]     [화력 DOWN : 아래 화살표]";
		TextOut(backDC, WINSIZEX / 2 - 170, WINSIZEY / 2-50, exp.c_str(), exp.length());

		wstring cP = L"현재 캐논 화력 : " + to_wstring(cannonPow);
		TextOut(backDC, WINSIZEX / 2-100, WINSIZEY / 2, cP.c_str(), cP.length());

		wstring windT = L"현재 바람의 세기 : " + to_wstring(wind*100);
		TextOut(backDC, WINSIZEX / 2 - 100, WINSIZEY / 2+50, windT.c_str(), windT.length());

		if (wind < 0) { //wind level visulization render (plus vector)
			for (int i = 4; i > 4+wind*10; i--) {

				color = CreateSolidBrush(RGB(255, 0, 0));
				white = (HBRUSH)SelectObject(backDC, color);

				RenderRect(backDC, windrc[i]);

				SelectObject(backDC, white);
				DeleteObject(color);

			}
		}

		if (wind > 0) { //wind level visualization render (minus vector)
			for (int i = 5; i < 5+wind * 10; i++) {

				color = CreateSolidBrush(RGB(0, 255, 0));
				white = (HBRUSH)SelectObject(backDC, color);

				RenderRect(backDC, windrc[i]);

				SelectObject(backDC, white);
				DeleteObject(color);

			}
		}

		RenderLine(backDC, mCannon.x, mCannon.y, mCannon.cannonEndX, mCannon.cannonEndY);//canon body render
		RenderEllipse(backDC, mCannon.x, mCannon.y, mCannon.radius);

		color = CreateSolidBrush(RGB((int)frameRate%60+180, (int)frameRate%60+180, 100)); //target body render
		white = (HBRUSH)SelectObject(backDC, color);

		RenderEllipse(backDC, target.x, target.y, target.radius);

		SelectObject(backDC, white);
		DeleteObject(color);

		for (int i = 0; i < X.size(); i++) {
			if (X[i].dist < 90) { //target approach signal render
				color = CreateSolidBrush(RGB(255, 0, 0));
				white = (HBRUSH)SelectObject(backDC, color);

				RenderEllipse(backDC, target.x, target.y, target.radius);

				SelectObject(backDC, white);
				DeleteObject(color);

			}
		}

		for (int i = 0; i < X.size(); i++) { //bullet body render

			color = CreateSolidBrush(RGB(120, 120, 120));
			white =(HBRUSH) SelectObject(backDC, color);
			
			RenderEllipse(backDC, X[i].x, X[i].y, X[i].radius);

			SelectObject(backDC, white);
			DeleteObject(color);

		}

		for (int i = 1; i < 20; i++) { //trajectory line render

			color = CreateSolidBrush(RGB(120, 200, 120));
			white = (HBRUSH)SelectObject(backDC, color);

			RenderEllipse(backDC, dots[i].x, dots[i].y, dots[i].radius);

			SelectObject(backDC, white);
			DeleteObject(color);
		}
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}
