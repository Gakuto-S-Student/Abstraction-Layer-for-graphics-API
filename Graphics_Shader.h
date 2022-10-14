/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_Shader.h
*		Detail	: 
===================================================================================*/
#pragma once
#include <string>

class GraphicsShader
{
public:
	//**************************************************
	/// \brief Get device pointer
	/// 
	/// \param[in]	fileName	 ->	shader file name
	/// \param[out] buffer		 -> buffer data
	/// 
	/// \return Success is true
	//**************************************************
	static bool LoadFile(
		const std::string fileName,
		std::string& buffer
	);
};

