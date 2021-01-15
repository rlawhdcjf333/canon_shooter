#pragma once
class Image
{
	//enum class �� enum�̶� ������ �����غ���
	//���� �̹��� ����
	enum LoadType : int
	{
		Resource = 0,
		File, 
		Empty,
		End
	};
	
	struct ImageBuffer
	{
		//unsigned long
		ULONG registerID;	//�������� ID(�ٵ� �Ƹ� �ʳ� ���� ���� ��)
		HDC hdc;			//HDC
		HBITMAP bitmap;		//��Ʈ��
		HBITMAP oldBitmap;	//HDC�⺻ ��Ʈ�� ���⿡ ���� ����
		int width;			//���α���
		int height;			//���α��� 
		LoadType loadType;	//����Ÿ��
	};
private:
	ImageBuffer* mImageBuffer;	//����
	wstring mFileName;			//�����̸�
	bool	mIsTrans;			//�̹��� Ʈ���� ó��
	COLORREF mTransColor;		//Ʈ���� ó���� �÷�
public:
	Image();
	~Image();
	
	void ReleaseBuffer();		//���� ����
	
	bool CreateEmpty(int width, int height);//����ִ� ��Ʈ�� ����
		
	void Render(HDC hdc, int x, int y);	//������
	
	HDC GetHDC() { return mImageBuffer->hdc; }
};

