/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: Graphics_Cube11.cpp
*		Detail	:
===================================================================================*/

#include <fstream>
#include "Graphics.h"

#include "Graphics_Shader.h"


// *.cso file load
bool GraphicsShader::LoadFile(const std::string fileName, std::string& buffer)
{
	std::ifstream ifs(fileName.c_str(), std::ios::binary);
	if (ifs.fail())
	{// failed to open file
		return false;
	}

	ifs.seekg(0, std::ios::end);
	buffer.resize(size_t(ifs.tellg()));
	ifs.seekg(0, std::ios::beg);

	ifs.read(&buffer[0], buffer.size());
	ifs.close();

	return true;
}
