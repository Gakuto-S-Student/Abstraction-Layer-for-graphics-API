/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_DirectX12.h
*		Detail	:
===================================================================================*/
#pragma once
#include "Graphics_Interface.h"
class GraphicsDirectX12 : public GraphicsInterface
{
public:
	//**************************************************
	/// \brief Initialize DirectX12
	/// 
	/// \return Success is true
	//**************************************************
	bool Init(Application* app) override;

	//**************************************************
	/// \brief Uninitialize DirectX12
	/// 
	/// \return none
	//**************************************************
	void Uninit()	override;

	//**************************************************
	/// \brief Clear screen
	/// 
	/// \return none
	//**************************************************
	void Clear()	override;

	//**************************************************
	/// \brief Present buffer
	/// 
	/// \return none
	//**************************************************
	void Present()	override;
};

