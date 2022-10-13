/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics.h
*		Detail	: 
===================================================================================*/
#pragma once
#include "Graphics_Interface.h"

class Graphics
{
public:
	Graphics() = delete;
	Graphics(Graphics&) = delete;
	Graphics(Graphics*) = delete;

	//**************************************************
	/// \brief Get instance
	/// 
	/// \return GraphicsInterface class pointer
	//**************************************************
	static GraphicsInterface* Get(bool destroy = false);

private:
	static GraphicsInterface* m_instance;	// GraphicsInterface class instance
};

