/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Application.cpp
*		Detail	:
===================================================================================*/
#include "Graphics.h"

#include "Graphics_Cube12.h"
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

GraphicsCube12 cube[2];

/* Initialize */
bool Application::Init()
{
    if (!Graphics::Get()->Init(this))
        return false;

    cube[0].Init();
    cube[1].Init();

    return true;
}

/* Uninitialize */
void Application::Uninit()
{
    cube[1].Uninit();
    cube[0].Uninit();

    Graphics::Get()->Uninit();
    Graphics::Get(true);
}

/* Update */
void Application::Upadte()
{
}

/* Draw */
void Application::Draw()
{
    Graphics::Get()->Clear();

    cube[0].Draw( 2, 0, 0);
    cube[1].Draw(-2, 0, 0);

    Graphics::Get()->Present();
}
