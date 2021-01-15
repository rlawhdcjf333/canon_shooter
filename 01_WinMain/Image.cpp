#include "pch.h"
#include "Image.h"

//생성자 : 메모리가 잡힐 때 자동으로 실행되는 함수
Image::Image()
	:mImageBuffer(NULL),mIsTrans(false)	//멤버 이니셜라이즈 : 생성자 안에서 멤버 변수의 생성자를 불러서
										//초기화 해주는 문법
{
	//mImageBuffer = NULL;
	//mIsTrans = false;
}

//소멸자 : 메모리가 해제될 때 자동으로 실행되는 함수
Image::~Image()
{
	ReleaseBuffer();
}

void Image::ReleaseBuffer()
{
	if (mImageBuffer != NULL)
	{
		SelectObject(mImageBuffer->hdc, mImageBuffer->oldBitmap);
		DeleteObject(mImageBuffer->bitmap);
		DeleteDC(mImageBuffer->hdc);

		delete mImageBuffer;
		mImageBuffer = NULL;
	}
}

bool Image::CreateEmpty(int width, int height)
{
	//이미 이미지 버퍼가 생성되어 있다면
	if (mImageBuffer != NULL)
	{
		//기존 버퍼 삭제
		ReleaseBuffer();
	}

	//GetDC : 윈도우 창의 HDC를 가져오는 녀석, BeginPaint 할때 반환하는 HDC랑 같은 녀석을 반환함
	HDC hdc = GetDC(_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadType = LoadType::Empty;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);	//빈 HDC 생성
	//비어있는 비트맵 생성( CreateSolidBrush 같은 녀석)
	mImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
	mImageBuffer->width = width;
	mImageBuffer->height = height;

	ReleaseDC(_hWnd, hdc);

	//정상적으로 생성이 안되었다면
	if (mImageBuffer->bitmap == NULL)
	{
		//버퍼 삭제
		ReleaseBuffer();
		return false;
	}

	return false;
}

/*
hdc : 현재 이미지 클래스에 있는 비트맵을 매개변수로 들어온 hdc에 그려준다
x : 그릴 좌표X
y : 그릴 좌표Y
*/
void Image::Render(HDC hdc, int x, int y)
{
	//다른 HDC에 있는 비트맵이미지를 첫번째 인자에 들어오는 HDC에 고속 복사 해주는 녀석
	BitBlt
	(
		hdc,					//고속복사해서 넣어줄 HDC
		x,						//그려줄 좌표
		y,						//그려줄 좌표 
		mImageBuffer->width,	//그려줄 버퍼 사이즈
		mImageBuffer->height,	//그려줄 버퍼 사이즈
		mImageBuffer->hdc,		//복사할 HDC 
		0,						//복사할 시작 위치 
		0,						//복사할 시작 위치
		SRCCOPY					//고속 복사 옵션
	);
}
