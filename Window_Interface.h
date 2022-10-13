/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Window_Interface.h
*		Detail	:
===================================================================================*/
#pragma once

class WindowInterface
{
public:
	virtual ~WindowInterface() {}
	virtual bool Close() = 0;

protected:
	//**************************************************
	/// \brief Application class constructor
	/// 
	/// \param[in] width	 ->	window width
	/// \param[in] height	 ->	window height
	/// 
	/// \return none
	//**************************************************
	WindowInterface(
		const int width,
		const int height
	)
		:m_width(width), m_height(height)
	{}


	int		m_width;		// size of window width
	int		m_height;		// size of window height
};

