#include "pch.h"
#include "Image.h"

//������ : �޸𸮰� ���� �� �ڵ����� ����Ǵ� �Լ�
Image::Image()
	:mImageBuffer(NULL),mIsTrans(false)	//��� �̴ϼȶ����� : ������ �ȿ��� ��� ������ �����ڸ� �ҷ���
										//�ʱ�ȭ ���ִ� ����
{
	//mImageBuffer = NULL;
	//mIsTrans = false;
}

//�Ҹ��� : �޸𸮰� ������ �� �ڵ����� ����Ǵ� �Լ�
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
	//�̹� �̹��� ���۰� �����Ǿ� �ִٸ�
	if (mImageBuffer != NULL)
	{
		//���� ���� ����
		ReleaseBuffer();
	}

	//GetDC : ������ â�� HDC�� �������� �༮, BeginPaint �Ҷ� ��ȯ�ϴ� HDC�� ���� �༮�� ��ȯ��
	HDC hdc = GetDC(_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadType = LoadType::Empty;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);	//�� HDC ����
	//����ִ� ��Ʈ�� ����( CreateSolidBrush ���� �༮)
	mImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
	mImageBuffer->width = width;
	mImageBuffer->height = height;

	ReleaseDC(_hWnd, hdc);

	//���������� ������ �ȵǾ��ٸ�
	if (mImageBuffer->bitmap == NULL)
	{
		//���� ����
		ReleaseBuffer();
		return false;
	}

	return false;
}

/*
hdc : ���� �̹��� Ŭ������ �ִ� ��Ʈ���� �Ű������� ���� hdc�� �׷��ش�
x : �׸� ��ǥX
y : �׸� ��ǥY
*/
void Image::Render(HDC hdc, int x, int y)
{
	//�ٸ� HDC�� �ִ� ��Ʈ���̹����� ù��° ���ڿ� ������ HDC�� ��� ���� ���ִ� �༮
	BitBlt
	(
		hdc,					//��Ӻ����ؼ� �־��� HDC
		x,						//�׷��� ��ǥ
		y,						//�׷��� ��ǥ 
		mImageBuffer->width,	//�׷��� ���� ������
		mImageBuffer->height,	//�׷��� ���� ������
		mImageBuffer->hdc,		//������ HDC 
		0,						//������ ���� ��ġ 
		0,						//������ ���� ��ġ
		SRCCOPY					//��� ���� �ɼ�
	);
}
