#pragma once
class Image
{
	//enum class 랑 enum이랑 차이점 조사해보기
	//현재 이미지 상태
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
		ULONG registerID;	//레지스터 ID(근데 아마 너네 쓸일 없을 걸)
		HDC hdc;			//HDC
		HBITMAP bitmap;		//비트맵
		HBITMAP oldBitmap;	//HDC기본 비트맵 여기에 담을 예정
		int width;			//가로길이
		int height;			//세로길이 
		LoadType loadType;	//버퍼타입
	};
private:
	ImageBuffer* mImageBuffer;	//버퍼
	wstring mFileName;			//파일이름
	bool	mIsTrans;			//이미지 트랜스 처리
	COLORREF mTransColor;		//트랜스 처리할 컬러
public:
	Image();
	~Image();
	
	void ReleaseBuffer();		//버퍼 삭제
	
	bool CreateEmpty(int width, int height);//비어있는 비트맵 생성
		
	void Render(HDC hdc, int x, int y);	//렌더링
	
	HDC GetHDC() { return mImageBuffer->hdc; }
};

