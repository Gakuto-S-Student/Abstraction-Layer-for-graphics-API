/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: main.cpp
*		Detail	:
===================================================================================*/
#include "Application.h"

/* main */
#ifdef USING_API_DIRECTX11
int __stdcall WinMain(
	_In_		HINSTANCE hInstance,
	_In_opt_	HINSTANCE hPrevInstance,
	_In_		LPSTR lpCmdLine,
	_In_		int nCmdShow
)
#endif // USING_API_DIRECTX11
#ifdef USING_API_DIRECTX12
int __stdcall WinMain(
	_In_		HINSTANCE hInstance,
	_In_opt_	HINSTANCE hPrevInstance,
	_In_		LPSTR lpCmdLine,
	_In_		int nCmdShow
)
#endif // USING_API_DIRECTX12
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	Application app(1280, 780, hInstance);

	if (app.Init())
	{
		while (!app.Close())
		{
			app.Upadte();
			app.Draw();
		}
	}

	app.Uninit();

	return 0;
}