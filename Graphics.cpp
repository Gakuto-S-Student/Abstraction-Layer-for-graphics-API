/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics.cpp
*		Detail	:
===================================================================================*/
#include "Application.h"

#ifdef USING_API_DIRECTX11
#include "Graphics_DirectX11.h"
#endif // USING_API_DIRECTX11

#ifdef USING_API_DIRECTX12
#include "Graphics_DirectX12.h"
#endif // USING_API_DIRECTX12

#include "Graphics.h"

GraphicsInterface* Graphics::m_instance = nullptr;


/* Get instance */
GraphicsInterface* Graphics::Get(bool destroy)
{
    if (!destroy)
    {
        if (m_instance)
            return m_instance;

        /* first call */
#ifdef USING_API_DIRECTX11
        m_instance = new GraphicsDirectX11();
#endif // USING_DIRECTX11
#ifdef USING_API_DIRECTX12
        m_instance = new GraphicsDirectX12();
#endif // USING_DIRECTX12

        return m_instance;
    }
    else
    {
        delete m_instance;
        return nullptr;
    }
}
