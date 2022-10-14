/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_Interface.h
*		Detail	:
===================================================================================*/
#pragma once
#include "Application.h"

class GraphicsInterface
{
public:
	virtual ~GraphicsInterface() {}
	virtual bool  Init(Application* app)							= 0;
	virtual void  Uninit()											= 0;
	virtual void  Clear()											= 0;
	virtual void  Present()											= 0;
	virtual void* Device()											= 0;
	virtual void* Context()											= 0;

	//**************************************************
	/// \brief Set world matrix for directx11
	/// 
	/// \return none
	//**************************************************
	virtual void  SetWorldMatrix(DirectX::XMMATRIX world)			{ UNREFERENCED_PARAMETER(world); }
	
	//**************************************************
	/// \brief Set view matrix for directx11
	/// 
	/// \return none
	//**************************************************
	virtual void  SetViewMatrix(DirectX::XMMATRIX view)				{ UNREFERENCED_PARAMETER(view); }
	
	//**************************************************
	/// \brief Set projection matrix for directx11
	/// 
	/// \return none
	//**************************************************
	virtual void  SetProjectionMatrix(DirectX::XMMATRIX projection) { UNREFERENCED_PARAMETER(projection); }
	
	//**************************************************
	/// \brief Set world matrix for directx12
	/// 
	/// \return none
	//**************************************************
	virtual void  SetWorldMatrix(UINT64 addressOfGpu)		{ UNREFERENCED_PARAMETER(addressOfGpu); }

	//**************************************************
	/// \brief Set view matrix for directx12
	/// 
	/// \return none
	//**************************************************
	virtual void  SetViewMatrix(UINT64 addressOfGpu)		{ UNREFERENCED_PARAMETER(addressOfGpu); }

	//**************************************************
	/// \brief Set projection matrix for directx11
	/// 
	/// \return none
	//**************************************************
	virtual void  SetProjectionMatrix(UINT64 addressOfGpu) { UNREFERENCED_PARAMETER(addressOfGpu); }
};

