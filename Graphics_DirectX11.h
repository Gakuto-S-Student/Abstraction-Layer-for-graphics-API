/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_DirectX11.h
*		Detail	:
===================================================================================*/
#pragma once
//// directx11 include ////
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>	// helper math library

//// Link library ////
#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(p)	\
	if(p) p->Release();\
	p = nullptr;\

#include "Graphics_Interface.h"

class GraphicsDirectX11 : public GraphicsInterface
{
public:
	//**************************************************
	/// \brief Initialize DirectX11
	/// 
	/// \return Success is true
	//**************************************************
	bool Init(Application* app) override;
	
	//**************************************************
	/// \brief Uninitialize DirectX11
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

	//**************************************************
	/// \brief Get device pointer
	/// 
	/// \return device pointer
	//**************************************************
	void* Device() override;

	//**************************************************
	/// \brief Get context pointer
	/// 
	/// \return context pointer
	//**************************************************
	void* Context() override;

	//**************************************************
	/// \brief Set World Matrix
	/// 
	/// \return context pointer
	//**************************************************
	void SetWorldMatrix(DirectX::XMMATRIX world) override;

	//**************************************************
	/// \brief Set View Matrix
	/// 
	/// \return context pointer
	//**************************************************
	void SetViewMatrix(DirectX::XMMATRIX view) override;

	//**************************************************
	/// \brief Set World Matrix
	/// 
	/// \return context pointer
	//**************************************************
	void SetProjectionMatrix(DirectX::XMMATRIX projection) override;

private:
	//**************************************************
	/// \brief Create device and swapchain
	/// 
	/// \param[in] width	 ->	buffer size width
	/// \param[in] height	 ->	buffer size height
	/// \param[in] hWnd		 ->	window handle
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateDeviceAndSwapChain(
		const int width,
		const int height,
		const HWND hWnd
	);

	//**************************************************
	/// \brief Create render target view
	///  
	/// \return Succcess is true
	//**************************************************
	bool CreateRenderTargetView();

	//**************************************************
	/// \brief Create depth stencil view
	///
	/// \param[in] width	 ->	buffer size width
	/// \param[in] height	 ->	buffer size height
	///   
	/// \return Succcess is true
	//**************************************************
	bool CreateDepthStencilView(
		const int width,
		const int height
	);

	//**************************************************
	/// \brief Create rasterizer state
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateRasterizerState();

	//**************************************************
	/// \brief Create blend state
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateBlendState();

	//**************************************************
	/// \brief Create depth stencil state
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateDepthStencilState();

	//**************************************************
	/// \brief Create sampler state
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateSamplerState();

	//**************************************************
	/// \brief Create constant buffers
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateConstantBuffers();

	//**************************************************
	/// \brief Create shader
	///    
	/// \return Succcess is true
	//**************************************************
	bool CreateShader();

	//**************************************************
	/// \brief Create depth stencil view
	///
	/// \param[in] width	 ->	window width
	/// \param[in] height	 ->	window height
	///   
	/// \return none
	//**************************************************
	void SetViewport(
		const int width,
		const int height
	);

private:
	ID3D11Device*			    m_device;				// Device Interface
	ID3D11DeviceContext*		m_context;				// DeviceContext Interface
	IDXGISwapChain*			    m_swapChain;			// SwapChain Interface
	ID3D11RenderTargetView*     m_renderTargetView; 	// RenderTargetView Interface
	ID3D11DepthStencilView*     m_depthStencilView; 	// DepthStencilView Interface
	ID3D11RasterizerState*      m_rasterizerState;  	// RasterizerState Interface
	ID3D11BlendState*           m_blendState;       	// BlendState Interface
	ID3D11DepthStencilState*    m_depthStencilState;	// DepthStencilState Interface
	ID3D11SamplerState*         m_samplerState;     	// SamplerState Interface
	ID3D11Buffer*               m_modelMatrix;      	// The buffer is model matrix send to vertex buffer 
	ID3D11Buffer*				m_viewMatrix;       	// The buffer is view matrix send to vertex buffer
	ID3D11Buffer*               m_projectionMatrix; 	// The buffer is projection matrix send to vertex buffer
	ID3D11InputLayout*			m_inputLayout;
	ID3D11VertexShader*			m_vertexShader;
	ID3D11PixelShader*			m_pixelShader;
};

