/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Application.h
*		Detail	:
===================================================================================*/
#pragma once

/* Select using Graphics API */
#define USING_API_DIRECTX12

/*  Application class  */
#ifdef USING_API_DIRECTX11
#include "Window_Desktop.h"
class Application: public WindowDesktop
#endif
#ifdef USING_API_DIRECTX12
#include "Window_Desktop.h"
class Application : public WindowDesktop
#endif
{
public:
#ifdef USING_API_DIRECTX11
	//**************************************************
	/// \brief Application class constructor
	/// 
	/// \param[in] width	 ->	window width
	/// \param[in] height	 ->	window height
	/// \param[in] hInstance ->	handle instance for windows desktop app
	/// 
	/// \return none
	//**************************************************
	Application(
		const int width,
		const int height,
		const HINSTANCE hInstance
	);
#endif
#ifdef USING_API_DIRECTX12
	//**************************************************
	/// \brief Application class constructor
	/// 
	/// \param[in] width	 ->	window width
	/// \param[in] height	 ->	window height
	/// \param[in] hInstance ->	handle instance for windows desktop app
	/// 
	/// \return none
	//**************************************************
	Application(
		const int width,
		const int height,
		const HINSTANCE hInstance
	);
#endif

	//**************************************************
	/// \brief Initialize application
	/// 
	/// \return Success is true
	//**************************************************
	bool Init();
	
	//**************************************************
	/// \brief Uninitialize application
	///  
	/// \return none
	//**************************************************
	void Uninit();

	//**************************************************
	/// \brief Update application
	///  
	/// \return none
	//**************************************************
	void Upadte();

	//**************************************************
	/// \brief Draw in application window
	///  
	/// \return none
	//**************************************************
	void Draw();
};

