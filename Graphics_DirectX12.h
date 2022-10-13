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
	/// \brief Create device and swapchain
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateRenderTargetView();

	//**************************************************
	/// \brief Create device and swapchain
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
	/// \brief Create device and swapchain
	/// 
	/// \return Succcess is true
	//**************************************************
	bool CreateFence();

	//**************************************************
	/// \brief Create device and swapchain
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
	/// \brief Create device and swapchain
	/// 
	/// \return none
	//**************************************************
	void SetViewport(
		const int width,
		const int height
	);

	//**************************************************
	/// \brief Create device and swapchain
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
	D3D12_VIEWPORT										m_viewport{};
	D3D12_RECT											m_scissorRect{};
};

