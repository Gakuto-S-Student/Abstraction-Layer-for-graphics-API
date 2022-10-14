/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics.h
*		Detail	: 
===================================================================================*/
#pragma once
#include <DirectXMath.h>
#include "Graphics_Interface.h"

namespace graphicsStructure
{
	struct Vertex3D
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 TexCoord;
	};
}

class Graphics
{
public:
	Graphics() = delete;
	Graphics(Graphics&) = delete;
	Graphics(Graphics*) = delete;

	//**************************************************
	/// \brief Get instance
	/// 
	/// \param[in] destroy
	/// 
	/// \return GraphicsInterface class pointer
	//**************************************************
	static GraphicsInterface* Get(bool destroy = false);

private:
	static GraphicsInterface* m_instance;	// GraphicsInterface class instance
};

