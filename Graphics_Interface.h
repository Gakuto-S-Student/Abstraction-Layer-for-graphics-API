/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_Interface.h
*		Detail	:
===================================================================================*/
#pragma once

class Application;

class GraphicsInterface
{
public:
	virtual ~GraphicsInterface() {}
	virtual bool Init(Application* app) = 0;
	virtual void Uninit()	= 0;
	virtual void Clear()	= 0;
	virtual void Present()	= 0;
};

