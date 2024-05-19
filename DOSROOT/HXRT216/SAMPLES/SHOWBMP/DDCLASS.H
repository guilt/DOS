
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <ddraw.h>

class DD_OBJ
{
	public:
		
        DD_OBJ():lpDD(NULL),primarySurface(NULL),backSurface(NULL) {}
		~DD_OBJ();

		bool Init(HWND hwnd, DWORD reqWidth, DWORD reqHeight);
		bool InitSurfaces();
		bool LoadBackSurface(HINSTANCE hinstance, HWND hwnd, BITMAPINFOHEADER * pBM);
		bool Draw(HWND hwnd);

	private:

		LPDIRECTDRAW2 lpDD;
		LPDIRECTDRAWSURFACE primarySurface;
		LPDIRECTDRAWSURFACE backSurface;
        HDC hdc;
        DWORD dwWidth;
        DWORD dwHeight;
		void Free();

};

