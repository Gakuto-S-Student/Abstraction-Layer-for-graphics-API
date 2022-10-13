/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Application.cpp
*		Detail	:
===================================================================================*/
#include "Application.h"

/* Constructor */
#ifdef USING_API_DIRECTX11
#include "Window_Desktop_Procedure.h"
Application::Application(const int width, const int height, const HINSTANCE hInstance)
    : WindowDesktop(width, height, hInstance, L"DirectX11", DefMyWndProc)
{
}
#endif // USING_API_DIRECTX11

#ifdef USING_API_DIRECTX12
#include "Window_Desktop_Procedure.h"
Application::Application(const int width, const int height, const HINSTANCE hInstance)
    : WindowDesktop(width, height, hInstance, L"DirectX12", DefMyWndProc)
{
}
#endif // USING_API_DIRECTX12



/* Initialize */
bool Application::Init()
{
    return true;
}

/* Uninitialize */
void Application::Uninit()
{
}

/* Update */
void Application::Upadte()
{
}

/* Draw */
void Application::Draw()
{
}
