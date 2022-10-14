/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: Graphics_Cube11.h
*		Detail	:
===================================================================================*/
#pragma once
#include "Graphics_DirectX11.h"
#include "Graphics_Cube_Interface.h"

class GraphicsCube11 : public GraphicsCubeInterface
{
public:
	//**************************************************
	/// \brief Initialize
	/// 
	/// \return none
	//**************************************************
	void Init();

	//**************************************************
	/// \brief Uninitialize
	/// 
	/// \return none
	//**************************************************
	void Uninit();

	//**************************************************
	/// \brief Draw
	/// 
	/// \return none
	//**************************************************
	void Draw(float x, float y, float z);

private:
	ID3D11Buffer*             m_vertexBuffer;	
	// ID3D11ShaderResourceView* m_textureResource;  
	DirectX::XMFLOAT3         m_rotate;         
};

