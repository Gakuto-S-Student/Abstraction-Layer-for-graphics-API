/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Window_Desktop.h
*		Detail	:
===================================================================================*/
#pragma once
#include <Windows.h>
#include "Window_Interface.h"

class WindowDesktop : public WindowInterface
{
protected:
	//**************************************************
	/// \brief Window Desktop class Constructor
	/// 
	/// \param[in] width	 ->	window width
	/// \param[in] height	 ->	window height
	/// \param[in] hInstance ->	window handle instance
	/// \param[in] caption	 ->	window title
	/// \param[in] wndProc	 ->	window procedure
	/// 
	/// \return none
	//**************************************************
	WindowDesktop(
		const int width,
		const int height,
		const HINSTANCE hInstance,
		LPCWSTR caption,
		WNDPROC wndProc
		);

	//**************************************************
	/// \brief Window Desktop class Destructor
	/// 
	/// \return none
	//**************************************************
	~WindowDesktop();

public:
	//**************************************************
	/// \brief Check window status
	/// 
	/// \return if Window closed then true
	//**************************************************
	bool Close() override;

private:
	const HINSTANCE m_hInstance;	// ハンドルインスタンス
	HWND			m_windowHandle;	// ウィンドウハンドル
	LPCWSTR			m_className;	// window class name
};

