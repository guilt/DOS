
#include <windows.h>
#include <ddraw.h>

class DD_OBJ
{
	public:
		
        DD_OBJ():lpDD(NULL),primarySurface(NULL),backSurface(NULL) {}
		~DD_OBJ();

		bool Init(HWND hwnd, DWORD reqWidth, DWORD reqHeight);
		bool InitSurfaces(char *);
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

