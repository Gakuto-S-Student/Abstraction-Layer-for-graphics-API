/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_DirectX12.h
*		Detail	:
===================================================================================*/
#pragma once
//// directx12 include ////
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <DirectXMath.h>	// helper math library

//// Link library ////
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include "Graphics_Interface.h"

class GraphicsDirectX12 : public GraphicsInterface
{
public:
	//**************************************************
	/// \brief These are roots index for send to shader
	/// 
	/// \return none
	//**************************************************
	struct CONSTANT_BUFFER_INDEX
	{
		static const int WORLD_MATRIX		= 0;	// World buffer root index
		static const int VIEW_MATRIX		= 1;	// View buffer root index
		static const int PROJECTION_MATRIX	= 2;	// Projection buffer root index
		static const int TEXTURE_INDEX		= 3;	// Texture buffer root index
	};

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

	//**************************************************
	/// \brief Get device pointer
	/// 
	/// \return device pointer
	//**************************************************
	void* Device() override;

	//**************************************************
	/// \brief Get virtual context pointer
	/// 
	/// \return virtual context pointer
	//**************************************************
	void* Context() override;

	//**************************************************
	/// \brief Set matrix
	/// 
	/// \return none
	//**************************************************
	void SetWorldMatrix(UINT64 addressOfGpu) override;

	//**************************************************
	/// \brief Set matrix
	/// 
	/// \return none
	//**************************************************
	void SetViewMatrix(UINT64 addressOfGpu) override;

	//**************************************************
	/// \brief Set matrix
	/// 
	/// \return none
	//**************************************************
	void SetProjectionMatrix(UINT64 addressOfGpu) override;

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
	/// \brief Create depth buffer
	/// 
	/// \param[in] width	 ->	buffer size width
	/// \param[in] height	 ->	buffer size height
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateDepthBuffer(
		const int width,
		const int height
	);
	//**************************************************
	/// \brief Create fence
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateFence();

	//**************************************************
	/// \brief Create graphics pipeline
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateGraphicsPipeline();

	//**************************************************
	/// \brief Set Resource barrier
	/// 
	/// \param[in] width	 ->	buffer size width
	/// \param[in] height	 ->	buffer size height
	/// \param[in] hWnd		 ->	window handle
	/// 
	/// \return none
	//**************************************************
	void SetResourceBarrier(
		const UINT index,
		D3D12_RESOURCE_STATES before,
		D3D12_RESOURCE_STATES after
	);

	//**************************************************
	/// \brief Set viewport
	/// 
	/// \return none
	//**************************************************
	void SetViewport(
		const int width,
		const int height
	);

	//**************************************************
	/// \brief Set scissor rect
	/// 
	/// \return none
	//**************************************************
	void SetScissorRect(
		const int width,
		const int height
	);

	static const UINT									k_backBufferNum = 2;
	Microsoft::WRL::ComPtr<ID3D12Device>				m_device;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>			m_commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4>				m_swapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_renderTargetViewHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource>				m_backBuffers[k_backBufferNum];
	Microsoft::WRL::ComPtr<ID3D12Resource>				m_depthBuffer;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_depthBufferHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence>					m_fence;
	UINT												m_fenceValue = 0;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
	D3D12_VIEWPORT										m_viewport{};
	D3D12_RECT											m_scissorRect{};
};

